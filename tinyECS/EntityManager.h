/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#pragma once

#include <SDL.h>
#include <iostream>
#include "../components/RenderCmp.h"

namespace tinyECS
{

struct EntityManager_t
{
   // Ctor.
   explicit EntityManager_t() = default;

   // Create the player.
   [[nodiscard]] static std::size_t createPlayer();

   // Create wall
   static void createWall(std::uint32_t x, std::uint32_t y, std::uint32_t w, std::uint32_t h);

   // Create an enemy.
   [[nodiscard]] static std::size_t createEnemy(std::uint32_t x, std::uint32_t y);

   // Create player bullet.
   static void createPlayerBullet(std::uint32_t x, std::uint32_t y);

   // Create enemy bullet.
   static void createEnemyBullet(std::uint32_t x, std::uint32_t y);

   // Create obstacle
   static void createObstacle(std::uint32_t x, std::uint32_t y);

private:
   // CreateBullet.
   static void createBullet(std::uint32_t x, std::uint32_t y, RenderCmp_t::types type, int8_t speed, std::uint8_t mask);
};
}
