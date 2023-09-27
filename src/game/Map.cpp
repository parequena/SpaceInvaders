/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#include "Map.h"
#include <SDL_image.h>
#include <tinyECS/GameContext.h>
#include <components/HPCmp.h>
#include <components/RenderCmp.h>
#include <components/CollisionCmp.h>
#include <components/PhysicsCmp.h>
#include <components/AICmp.h>
#include <systems/InputSys.h>
#include <tinyECS/Entity.h>
#include <systems/RenderSys.h>

Map_t::Map_t(RenderSys_t& renderSys, std::uint8_t columnsEnemies, std::uint8_t rowsEnemies, std::uint8_t numCovers)
    : m_rendSys(renderSys)
    , m_columnsEnemies(columnsEnemies)
    , m_rowsEnemies(rowsEnemies)
    , m_numCovers(numCovers)
    , m_totalEnemies{ static_cast<std::uint32_t>(columnsEnemies * rowsEnemies) }
{
   // Reserve all the entities space on the map.
   std::size_t const totalEnities = std::size_t(m_columnsEnemies) * std::size_t(m_rowsEnemies)
     + std::size_t(m_numPlayers) + std::size_t(m_numCovers) + 1U; // +1 'Cause map it's treated as entity.
   m_cmpStor->setVectSize(totalEnities * 2);                      // Reserve for all components // *2 Due bullets.
   const tinyECS::Entity_t e{};
   const auto eid = e.getEntityID();
   m_cmpStor->addComponent(RenderCmp_t{ eid, RenderCmp_t::types::R_Background }); // Adds the map render component.

   const auto w{ kWindWidht };
   const auto h{ kWindHeight };

   m_cmpStor->addComponent(PhysicsCmp_t{
     eid, 0, 0, static_cast<std::uint32_t>(w), static_cast<std::uint32_t>(h) }); // Add the map physics component

   // Create player.
   m_playerEid = tinyECS::EntityManager_t::createPlayer();

   // Create walls.
   tinyECS::EntityManager_t::createWall(0, 0, 5, h);         // Create left wall.
   tinyECS::EntityManager_t::createWall(w - 5, 0, 5, h);     // Right wall.
   tinyECS::EntityManager_t::createWall(5, 0, w - 6, 5);     // Up wall.
   tinyECS::EntityManager_t::createWall(5, h - 5, w - 6, 5); // Down Wall.

   // Create obstacles
   auto x{ kXAesteroidInit };
   auto y{ kYAesteroidInit };
   for (auto i = 0; i < m_numCovers; ++i)
   {
      tinyECS::EntityManager_t::createObstacle(std::uint32_t(x), std::uint32_t(y));
      x += kAesteroidPadding;
   }

   // Create enemies.
   x = kXEnemiesInit;
   y = kYEnemiesInit;
   for (auto i = 0U; i < m_totalEnemies; ++i)
   {
      m_lastEnemy = tinyECS::EntityManager_t::createEnemy(x, y); // Save lastEnemyID.
      x += kSpaceShipSize + kEnemiesPadding;                     // Update the enemy on column

      if ((i + 1) % m_columnsEnemies == 0)
      {
         x = kXEnemiesInit;
         y += kSpaceShipSize + kEnemiesPadding;
      }
   }
}

// Dtor.
Map_t::~Map_t()
{
   m_cmpStor->clearAll();
   m_playerEid = 0;
   m_lastEnemy = 0;
}

// run the map.
bool Map_t::run()
{
   // Update values
   m_rendSys.m_currScore = m_enemiesKilled;
   m_rendSys.m_bestScore = m_enemiesKilled >= m_rendSys.m_bestScore ? m_enemiesKilled : m_rendSys.m_bestScore;
   m_rendSys.m_playerHP = getPlayerHP();

   // If we killed all enemies
   if (m_enemiesKilled == m_totalEnemies)
      return false;

   if (!InputSys_t::update())
      return false;

   update(); // Update all components.
   // If we died.
   if (!m_cmpStor->getComponentFromID<HPCmp_t>(m_playerEid))
      return false;
   m_rendSys.update(); // Update the render.

   return checkEnemyPosition();
}

// Get playerHP
std::uint32_t Map_t::getPlayerHP() const
{
   auto hp = m_cmpStor->getComponentFromID<HPCmp_t>(m_playerEid);
   if (!hp)
      return 0;

   return hp->get().m_hp;
}

// Check alive entities
void Map_t::checkAliveEntites()
{
   auto& hpCmps = m_cmpStor->getComponents<HPCmp_t>();
   std::size_t lastAlive{ 0 };

   auto hpSize = hpCmps.size();

   for (auto i = 0UL; i < hpSize; ++i)
   {
      auto& h = hpCmps[i];

      if (h.m_hp > 0)
      {
         lastAlive = h.getEntityID();
         continue;
      }

      const auto eid = h.getEntityID();
      const auto properties = m_cmpStor->getComponentFromID<CollisionCmp_t>(eid)->get().m_properties;
      m_cmpStor->eraseAllCmpsFromID(eid); // Erase the component.
      --hpSize;
      if (eid == m_lastEnemy)
         m_lastEnemy = lastAlive;
      if (properties & CollisionCmp_t::P_isEnemy)
         ++m_enemiesKilled;
   }
}

// React to collisions.
void Map_t::react2Collisions(CollisionCmp_t& lh, CollisionCmp_t& rh) const
{
   using cp = CollisionCmp_t;
   cp *player{ &lh }, *other{ &rh }; // Lets asume one is the player.

   if (rh.m_properties & cp::P_isPlayer)
      std::swap(player, other); // If right is player, swap.

   if (other->m_properties & cp::P_damages) // Other does damage
   {
      auto damage = [&](const cp* cmp)
      {
         auto hp = m_cmpStor->getComponentFromID<HPCmp_t>(cmp->getEntityID());
         if (!hp)
            return;
         --hp->get().m_hp;
      };

      // Damage both.
      damage(player);
      damage(other);

      return;
   }

   if (player->m_properties & cp::P_isPlayer) // Player on left.
   {
      if (other->m_properties & cp::P_isSolid) // Other is solid.
      {
         auto phyCmp = m_cmpStor->getComponentFromID<PhysicsCmp_t>(player->getEntityID());
         if (!phyCmp)
            return;
         phyCmp->get().m_vx = 0;
         phyCmp->get().m_vy = 0;
         phyCmp->get().setPos(player->m_prevPos);
         player->restorePosition();
      }
   }

   // if(player->m_properties & cp::p_)
   // Bullet + Enemy
   // Bullet + Solid
   // No players.
}

// React to collisions.
void Map_t::checkCollisions() const
{
   auto& collComps{ m_cmpStor->getComponents<CollisionCmp_t>() };
   const auto size = collComps.size();

   // We could do better. -> Collision system.
   auto checkInterval = [](std::uint32_t l1, std::uint32_t r1, std::uint32_t l2, std::uint32_t r2)
   {
      if (l2 > r1)
         return false;
      if (l1 > r2)
         return false;
      return true;
   };

   auto getBbox = [](const SDL_FRect& rect) -> auto
   {
      const auto xLeft = std::uint32_t(rect.x);
      const auto xRight = xLeft + std::uint32_t(rect.w);

      const auto yUp = std::uint32_t(rect.y);
      const auto yDown = yUp + std::uint32_t(rect.h);

      return std::tuple{ xLeft, xRight, yUp, yDown };
   };

   for (auto i = 0UL; i < size - 1; ++i)
   {
      auto& col1{ collComps[i] };
      for (auto j = i + 1; j < size; ++j)
      {
         if ((col1.m_mask & collComps[j].m_mask) == 0)
            continue;

         auto& col2{ collComps[j] };

         const auto myID = col1.getCmpID();
         const auto himID = col2.getCmpID();
         if (col1.m_properties & col2.m_properties & CollisionCmp_t::P_isSolid)
            continue; // If both solid.
         if (myID == himID)
            continue;
         auto [meXLeft, meXRight, meYUp, meYDown] = getBbox(col1.m_boundingBox);
         auto [himXLeft, himXRight, himYUp, himYDown] = getBbox(col2.m_boundingBox);

         if (checkInterval(meXLeft, meXRight, himXLeft, himXRight) && checkInterval(meYUp, meYDown, himYUp, himYDown))
         {
            react2Collisions(collComps[i], collComps[j]);
         }
      }
   }
}

// Check enemy position.
bool Map_t::checkEnemyPosition() const
{
   const auto lastEnemy = m_cmpStor->getComponentFromID<PhysicsCmp_t>(m_lastEnemy);
   const auto playerPos = m_cmpStor->getComponentFromID<PhysicsCmp_t>(m_playerEid);

   if (!lastEnemy)
      return false;
   if (!playerPos)
      return false;

   return lastEnemy->get().getY() <= playerPos->get().getY();
}

void Map_t::update()
{
   updateSystem<AICmp_t>();
   updateSystem<CollisionCmp_t>();
   checkCollisions();
   checkAliveEntites();
   updateSystem<PhysicsCmp_t>();
}
