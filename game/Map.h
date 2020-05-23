/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#pragma once
#include <SDL.h>
#include <algorithm>
#include <tinyECS/ComponentStorage.h>
#include <tinyECS/GameContext.h>
#include <tinyECS/StateManager.h>

struct RenderSys_t;
struct CollisionCmp_t;

struct Map_t : tinyECS::State_t

{
	// Ctor.
	explicit Map_t(RenderSys_t& renderSys, uint8_t columnsEnemies, uint8_t rowsEnemies, uint8_t numCovers);

	// Dtor.
	~Map_t();
	
	// run the map.
    bool run();

	// Get playerHP
	[[nodiscard]] uint32_t getPlayerHP() const;

private:
    // Update system.
	template <typename cmp_t>
    void updateSystem() const
	{
		// Update all collisions.
		auto& cmps = m_cmpStor->getComponents<cmp_t>();
		std::for_each(cmps.begin(), cmps.end(), [](cmp_t& pCmp) { pCmp.update(); });
	}

	// Check alive entities
	void checkAliveEntites();

	// React to collisions.
	void react2Collisions(CollisionCmp_t& lh, CollisionCmp_t& rh) const;

	// check collisions.
	void checkCollisions() const;

	// Check enemy position.
	[[nodiscard]] bool checkEnemyPosition() const;
	
    // Update.
    void update();

    // ----------------------------------------------------------------
	// ComponentStor
	tinyECS::ComponentStorage_t* m_cmpStor{ tinyECS::GameContext_t::getCmpStorage() };

	// Render system
	RenderSys_t& m_rendSys;

	// Player EID to simplify code.
	std::size_t m_playerEid{ 0 };
	std::size_t m_lastEnemy{ 0 };
	
    const uint8_t m_columnsEnemies{ 10 }; // Enemies on a column.
    const uint8_t m_rowsEnemies{ 5 }; // Enemies on a row.
    const uint8_t m_numPlayers{ 1 }; // Number of players.
    const uint8_t m_numCovers{ 4 }; // Number of covers.

	// Enemies left.
	const uint32_t m_totalEnemies{ 0 };
	uint32_t m_enemiesKilled{ 0 };
};

