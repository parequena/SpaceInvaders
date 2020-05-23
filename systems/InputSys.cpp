/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#include "InputSys.h"
#include <SDL.h>
#include "../tinyECS/GameContext.h"
#include "../components/InputCmp.h"
#include "../components/PhysicsCmp.h"

bool InputSys_t::update()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	// If we pressed quit.
	if (event.type == SDL_QUIT) return false;
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) return false;

	auto& inCmps = tinyECS::GameContext_t::getCmpStorage()->getComponents<InputCmp_t>();

	for(auto& in : inCmps)
	{
		auto phyCmp = tinyECS::GameContext_t::getCmpStorage()->getComponentFromID<PhysicsCmp_t>(in.getEntityID());
		if (!phyCmp) return false;

		const auto keySym{ event.key.keysym.sym };
		
		if(event.type == SDL_KEYDOWN) // Push any button.
		{
			if (keySym == in.m_leftKey)  phyCmp->get().m_vx = -phyCmp->get().m_speed; // Move left.
			if (keySym == in.m_rightKey) phyCmp->get().m_vx = phyCmp->get().m_speed; // Move left.
		}

		if(event.type == SDL_KEYUP) // Released any button.
		{
			if (keySym == in.m_shootKey)
			{
				const auto x{ phyCmp->get().getX() + phyCmp->get().getW() / 2 };
 				tinyECS::EntityManager_t::createPlayerBullet(x, phyCmp->get().getY());
			}

			if( keySym == in.m_leftKey || keySym == in.m_rightKey) phyCmp->get().m_vx = 0; // Stop velocity. // Frictionless to keep it simple.
		}
	}
	
	return true;
}
