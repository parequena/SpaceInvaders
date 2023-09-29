/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#include "MenuState.h"
#include <SDL.h>
#include <iostream>
#include "Map.h"
#include <systems/RenderSys.h>
#include <string>
#include <SDL_image.h>

// Assets
constexpr std::array kMenuAssetsON
{
	"Assets/MenuScreen/play_buttons.png",
	// "Assets/MenuScreen/optionst_buttons.png",
	"Assets/MenuScreen/exit_buttons.png"
};

// Assets
constexpr std::array kMenuAssetsOFF
{
	"Assets/MenuScreen/play_buttons_pressed_blue.png",
	// "Assets/MenuScreen/optionst_buttons_pressed.png",
	"Assets/MenuScreen/exit_buttons_pressed.png"
};

namespace tinyECS
{
	// Ctor.
	MenuState_t::MenuState_t(RenderSys_t& renderSys) noexcept
		: m_renderSys(renderSys)
	{
		const auto size{ kMenuAssetsON.size() };
		m_surfaces.reserve(size * 2);
		m_texturesON.reserve(size);
		m_texturesOFF.reserve(size);

		auto emplaceOnVector = [&](vect_t<SDL_Texture*>& vect, const std::string_view& str)
		{
			auto* sur = m_surfaces.emplace_back(IMG_Load(str.data())); // Load all images.
			if (!sur)
			{
				std::cerr << "ERROR: " << str.data() << " not found.\n";
				exit(-1);
			}
			vect.emplace_back(SDL_CreateTextureFromSurface(m_renderSys.getRenderer(), sur));
		};
		
		for (auto i = 0UL; i < size; ++i)
		{
			emplaceOnVector(m_texturesON, kMenuAssetsON[i]);
			emplaceOnVector(m_texturesOFF, kMenuAssetsOFF[i]);
		}
	}

	// Run
	bool MenuState_t::run()
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		const auto keySym{ event.key.keysym.sym };

		if (event.type == SDL_EVENT_QUIT) return false;
		
		// std::cout << "MenuKey : " << static_cast<int>(m_idx) << "\n";
		
		if (event.type == SDL_EVENT_KEY_UP) // Push any button.
		{
			if (m_idx > m_minIdx && keySym == SDLK_UP)
			{
				--m_idx;
			}
			if (m_idx < m_maxIdx && keySym == SDLK_DOWN)
			{
				++m_idx;
			}
		}

		draw();

		// If we didnt interact with return key.
		if (keySym != SDLK_RETURN) return true;

		// Play
 		if(m_idx == 0)
			tinyECS::GameContext_t::StateMan()->pushState<Map_t>(m_renderSys, m_nColsEnemies, m_nRowsEnemies, m_nColsCovers);
		// else if(m_idx == 1) // Options
		// {
		// 	
		// }
		else return false; // Exit

		return true;
	}

	// Draw.
	void MenuState_t::draw()
	{
		const auto bestScore{ "Best Score: " + std::to_string(m_renderSys.m_bestScore) };
		const auto help{"UP/DOWN arrows to select. ENTER (RETURN) to pick"};
		auto* renderer{ m_renderSys.getRenderer() };
		
		const SDL_FRect rect{ 0, 0, kWindWidht, kWindHeight };
		const SDL_FRect titleRect{ kTitleXInit, kTitleYInit, kTitleWidth, kTitleHeight };
		const SDL_FRect helpRect{ 15.f, 350.f, 430.f, 40.f };

		SDL_RenderClear(renderer); // Clear the screen.
		SDL_RenderTexture(renderer, m_renderSys.m_textures[static_cast<int>(RenderCmp_t::types::R_Background)], nullptr, &rect);

		float y{ kMenuYInit };
		for(auto i = 0UL; i < kMenuAssetsON.size(); ++i)
		{
			SDL_FRect const rectMenu{ kMenuXInit, float(y), kMenuWidth, kMenuHeight };
			auto* texture = i == m_idx ? m_texturesON[i] : m_texturesOFF[i];
			SDL_RenderTexture(renderer, texture, nullptr, &rectMenu);
			y += 80;
		}

		auto textToTexture = [&](const std::string_view& str, const SDL_FRect& local_rect)
		{
			SDL_Surface* srf = TTF_RenderText_Solid(m_renderSys.m_font, str.data(), { 255, 255, 255, 255 });
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, srf);
			SDL_RenderTexture(renderer, texture, nullptr, &local_rect);
			SDL_DestroySurface(srf);
			SDL_DestroyTexture(texture);		
		};

		textToTexture(kTitle, titleRect);
		textToTexture(help, helpRect);
		textToTexture(bestScore, m_renderSys.m_bestRect);

		SDL_RenderPresent(renderer);
	}
}
