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
		static void createWall(uint32_t x, uint32_t y, uint32_t w, uint32_t h);

		// Create an enemy.
		[[nodiscard]] static std::size_t createEnemy(uint32_t x, uint32_t y);

		// Create player bullet.
		static void createPlayerBullet(uint32_t x, uint32_t y);

		// Create enemy bullet.
		static void createEnemyBullet(uint32_t x, uint32_t y);

		// Create obstacle
		static void createObstacle(uint32_t x, uint32_t y);

	private:
		// CreateBullet.
		static void createBullet(uint32_t x, uint32_t y, RenderCmp_t::types type, int8_t speed, uint8_t mask);
	};
}
