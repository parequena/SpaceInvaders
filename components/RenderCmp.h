/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#pragma once
#include <tinyECS/Component.h>

// Fordward declarations.
// class SDL_Renderer;
// class SDL_Surface;
// class SDL_Texture;

struct RenderCmp_t final : tinyECS::Component_t
{
	enum struct types : uint8_t
	{
		R_Wall,
		R_Background,
		R_Player,
		R_Enemy,
		R_PlayerBullet,
		R_EnemyBullet,
		R_Rock,
		R_TOTALRENDERS
	};
	
	// Ctor.
	RenderCmp_t(std::size_t eid, types renType);

	// Operator=
	RenderCmp_t& operator=(const RenderCmp_t& rh);

	// Update;
	void update() override;

	// Which render.
	types m_type{ types::R_TOTALRENDERS };
};

