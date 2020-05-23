/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#pragma once
#include "utils.h"
#include "ComponentStorage.h"
#include "EntityManager.h"
#include "StateManager.h"

namespace tinyECS
{

	struct GameContext_t
	{
		// Getters.
		static ComponentStorage_t* getCmpStorage() noexcept { return inst().m_cmpStr.get(); }
		static EntityManager_t* getEntMan() noexcept { return inst().m_entMan.get(); }
		static StateManager_t* StateMan() noexcept { return inst().m_stateMan.get(); }

	private:
		// Get the instance.
		static GameContext_t& inst() noexcept
		{
			static uptr_t<GameContext_t> instance{ new GameContext_t };
			return *instance;
		}

		// ComponentStorage
		uptr_t<ComponentStorage_t> m_cmpStr{ std::make_unique<ComponentStorage_t>() };

		// EntityManager
		uptr_t<EntityManager_t> m_entMan{ std::make_unique<EntityManager_t>() };

		// State manager
		uptr_t<StateManager_t> m_stateMan{ std::make_unique<StateManager_t>() };
	};
}
