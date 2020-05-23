/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#include "EntityManager.h"
#include "GameContext.h"

#include "Entity.h"
#include "../components/RenderCmp.h"
#include "../components/PhysicsCmp.h"
#include "../components/CollisionCmp.h"
#include "../components/InputCmp.h"
#include "../components/HPCmp.h"
#include "../components/AICmp.h"
#include "Entity.h"

namespace tinyECS
{
	// Create player.
	std::size_t EntityManager_t::createPlayer()
	{
		const Entity_t e;
		const auto playerEid{ e.getEntityID() };
		auto* cmpStor{ tinyECS::GameContext_t::getCmpStorage() };
		cmpStor->addComponent(RenderCmp_t{ playerEid, RenderCmp_t::types::R_Player });
		const auto& phyPlayer = cmpStor->addComponent(PhysicsCmp_t{ playerEid, 320, 400, kSpaceShipSize, kSpaceShipSize });
		auto& collCmp = cmpStor->addComponent(CollisionCmp_t{ playerEid, phyPlayer.getRect() });
		collCmp.m_properties = CollisionCmp_t::P_isPlayer ^ CollisionCmp_t::P_isMovable ^ CollisionCmp_t::P_damages;
		// collCmp.m_mask ^= CollisionCmp_t::L_three;
		collCmp.m_mask ^= (CollisionCmp_t::L_one | CollisionCmp_t::L_four);
		cmpStor->addComponent(InputCmp_t{ playerEid });
		cmpStor->addComponent(HPCmp_t{ playerEid, 3 });

		return playerEid;
	}

	// Create wall
	void EntityManager_t::createWall(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
	{
		const Entity_t wall;
		const auto wallEID{ wall.getEntityID() };

		auto* cmpStor{ tinyECS::GameContext_t::getCmpStorage() };

		cmpStor->addComponent(RenderCmp_t{ wallEID, RenderCmp_t::types::R_Wall });
		const auto& lwPhy = cmpStor->addComponent(PhysicsCmp_t{ wallEID, x, y, w, h });
		auto& collCmp = cmpStor->addComponent(CollisionCmp_t{ wallEID, lwPhy.getRect() });
		collCmp.m_properties = CollisionCmp_t::P_isSolid;
	}

	// Create an enemy.
	std::size_t EntityManager_t::createEnemy(uint32_t x, uint32_t y)
	{
		const Entity_t e;
		const auto eEid{ e.getEntityID() };
		auto* cmpStor{ tinyECS::GameContext_t::getCmpStorage() };
		
		cmpStor->addComponent(RenderCmp_t{ eEid, RenderCmp_t::types::R_Enemy});
		const auto& phyEne = cmpStor->addComponent(PhysicsCmp_t{ eEid, static_cast<uint32_t>(x), static_cast<uint32_t>(y), kSpaceShipSize, kSpaceShipSize });
		auto& collCmp = cmpStor->addComponent(CollisionCmp_t{ eEid, phyEne.getRect() });
		collCmp.m_properties = CollisionCmp_t::P_isMovable ^ CollisionCmp_t::P_isEnemy ^ CollisionCmp_t::P_damages;
		collCmp.m_mask = CollisionCmp_t::L_three | CollisionCmp_t::L_four;
		cmpStor->addComponent(AICmp_t{ eEid });
		cmpStor->addComponent(HPCmp_t{ eEid });

		return eEid;
	}

	// Create player bullet.
	void EntityManager_t::createPlayerBullet(uint32_t x, uint32_t y)
	{
		createBullet(x, y, RenderCmp_t::types::R_PlayerBullet, -kBulletSpeed, CollisionCmp_t::L_one | CollisionCmp_t::L_four);
	}

	// Create enemy bullet.
	void EntityManager_t::createEnemyBullet(uint32_t x, uint32_t y)
	{
		createBullet(x, y, RenderCmp_t::types::R_EnemyBullet, kBulletSpeed, CollisionCmp_t::L_two);
	}

	void EntityManager_t::createObstacle(uint32_t x, uint32_t y)
	{
		const Entity_t e;
		const auto eid{ e.getEntityID() };
		auto* cmpStor{ tinyECS::GameContext_t::getCmpStorage() };
		cmpStor->addComponent(RenderCmp_t{ eid, RenderCmp_t::types::R_Rock });
		const auto& phyPlayer = cmpStor->addComponent(PhysicsCmp_t{ eid, x, y, kAesteroidSize, kAesteroidSize });
		auto& collCmp = cmpStor->addComponent(CollisionCmp_t{ eid, phyPlayer.getRect() });
		collCmp.m_properties = CollisionCmp_t::P_isSolid;
		collCmp.m_mask = CollisionCmp_t::L_one;
		cmpStor->addComponent(HPCmp_t{ eid, 4 });
	}

	// CreateBullet.
	void EntityManager_t::createBullet(uint32_t x, uint32_t y, RenderCmp_t::types type, int8_t speed, uint8_t mask)
	{
		x -= kBulletSize / 2; // To spawn on the middle.
		const Entity_t e;
		const auto bullEid{ e.getEntityID() };
   		auto* cmpStor{ tinyECS::GameContext_t::getCmpStorage() };
		cmpStor->addComponent(RenderCmp_t{ bullEid, type });
		auto& phyPlayer = cmpStor->addComponent(PhysicsCmp_t{ bullEid, x, y, kBulletSize, kBulletSize });
		phyPlayer.m_vy = speed;
		auto& collCmp = cmpStor->addComponent(CollisionCmp_t{ bullEid, phyPlayer.getRect() });
		collCmp.m_properties = CollisionCmp_t::P_isMovable ^ CollisionCmp_t::P_damages;
		collCmp.m_mask = mask;
		cmpStor->addComponent(HPCmp_t{ bullEid, 1 });
	}
}
