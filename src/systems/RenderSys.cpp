/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#include "RenderSys.h"
#include <algorithm>
#include "../components/PhysicsCmp.h"
#include "../tinyECS/GameContext.h"
#include <SDL_image.h>
#include <string>
#include <array>

// Ctor.
RenderSys_t::RenderSys_t()
	: m_window(SDL_CreateWindow("Space Invaders", kWindWidht, kWindHeight, 0))
	, m_renderer(SDL_CreateRenderer(m_window, nullptr, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))
{
	auto size{ static_cast<std::size_t>(RenderCmp_t::types::R_TOTALRENDERS) };
	m_surfaces.reserve(size);
	m_textures.reserve(size);
	
	for (auto i = 0UL; i < size; ++i)
	{
		auto* sur = m_surfaces.emplace_back(IMG_Load(kAssets[i])); // Load all images.
		if (!sur)
		{
			std::cerr << "ERROR: " << kAssets[i] << " not found.\n";
			exit(-1);
		}
		m_textures.emplace_back(SDL_CreateTextureFromSurface(m_renderer, sur));
	}
	
	if (!m_window)
	{
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
		SDL_Quit();
		exit(-1);
	}

	if (!m_renderer)
	{
		SDL_DestroyWindow(m_window);
		std::cerr << "ERROR: Can't create renderer.";
		exit(-1);
	}
}

// Dtor.
RenderSys_t::~RenderSys_t()
{

	for (auto* txt : m_textures) SDL_DestroyTexture(txt);
	m_textures.clear();
	for (auto* srf : m_surfaces) SDL_DestroySurface(srf);
	m_surfaces.clear();

	if(m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
	
	if(m_window)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}
}

// Update.
bool RenderSys_t::update()
{
	SDL_RenderClear(m_renderer); // Clear the screen.

	// Draw all entities.
	auto& renderCmps = tinyECS::GameContext_t::getCmpStorage()->getComponents<RenderCmp_t>();
	
	std::for_each(renderCmps.begin(), renderCmps.end(), [&](const RenderCmp_t& rCmp)
		{
			auto phycmp = tinyECS::GameContext_t::getCmpStorage()->getComponentFromID<PhysicsCmp_t>(rCmp.getEntityID());
			if (!phycmp) return;
			auto render = phycmp->get().getRect();
			SDL_RenderTexture(m_renderer, m_textures[static_cast<int>(rCmp.m_type)], nullptr, &render);
		});

	auto textToTexture = [&](const std::string_view& str, const SDL_FRect& rect)
	{
		SDL_Surface* srf = TTF_RenderText_Solid(m_font, str.data(), { 255, 255, 255, 255 });
		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, srf);
		SDL_RenderTexture(m_renderer, texture, nullptr, &rect);
		SDL_DestroySurface(srf);
		SDL_DestroyTexture(texture);
	};

	const auto currScore{ "Actual Score: " + std::to_string(m_currScore) };
	const auto playerHP{ "HP: " + std::to_string(m_playerHP) };

	textToTexture(currScore, m_actualRect);
	textToTexture(playerHP, m_playerHpRect);

	SDL_RenderPresent(m_renderer);

	return true;
}
