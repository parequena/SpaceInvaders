/*
	Project: Space Invaders
	Author : Pablo Requena (Twitter: @conPdePABLO)
	GitHub : https://github.com/parequena/
	Date   : May 2020
*/

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <SDL.h>
#include <SDL_ttf.h> // To print text.
#elif defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif

#include <iostream>
#include <chrono>
#include <systems/RenderSys.h>
#include <tinyECS/StateManager.h>
#include <game/MenuState.h>
#include <tinyECS/GameContext.h>
#include <thread>

int main(int, char**)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
		return -1;
	}

	if (TTF_Init() != 0)
	{
		std::cerr << "TTF_Init Error.\n";
		return -1;
	}

	const auto columEnemies{ 9 }; // { 9 };
	const auto rowEnemies{ 5 }; // { 5 };
	const auto numCovers{ 4 };

	RenderSys_t* renderSys{ new RenderSys_t }; // Render system.

	// Push the menu.
	tinyECS::GameContext_t::StateMan()->pushState<tinyECS::MenuState_t>(*renderSys);

	using clk = std::chrono::steady_clock;
	auto lastTime = clk::now();
	while (tinyECS::GameContext_t::StateMan()->run())
	{
		auto interval = clk::now() - lastTime;
		if (interval < kFRAMERATE)
		{
			std::this_thread::sleep_for(kFRAMERATE - interval);
			lastTime = clk::now();
		}
	}

	// Free memory
	delete renderSys;
	renderSys = nullptr;
	SDL_Quit();

	return 0;
}
