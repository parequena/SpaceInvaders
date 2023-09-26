/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "../tinyECS/utils.h"

struct RenderSys_t
{
   // Ctor.
   explicit RenderSys_t();
   inline constexpr RenderSys_t(RenderSys_t const&) = delete;
   inline constexpr RenderSys_t operator=(RenderSys_t const&) = delete;

   // Dtor.
   ~RenderSys_t();

   // Update.
   bool update();

   // Score to print.
   std::uint32_t m_currScore{ 0 };

   // Best score to print.
   std::uint32_t m_bestScore{ 0 };

   // Player hp.
   std::uint32_t m_playerHP{ 0 };

   // Getters.
   [[nodiscard]] constexpr SDL_Window* getWindow() const noexcept { return m_window; }
   [[nodiscard]] constexpr SDL_Renderer* getRenderer() const noexcept { return m_renderer; }

   // Font
   TTF_Font* m_font{ TTF_OpenFont("Assets/MenuScreen/PkmnXandY.ttf", 24) };

   // Best score rect
   SDL_FRect m_bestRect{ 10.f, kWindHeight - 45.f, 100.f, 40.f };

   // Textures
   vect_t<SDL_Texture*> m_textures{};

private:
   // Surfaces
   vect_t<SDL_Surface*> m_surfaces{};

   // Actual texture
   SDL_Texture* m_actScore{ nullptr };

   // Window.
   SDL_Window* m_window{ nullptr };

   // Renderer
   SDL_Renderer* m_renderer{ nullptr };

   // Rects
   SDL_FRect m_actualRect{ kWindWidht / 2 - 50, kWindHeight - 45, 100, 40 };
   SDL_FRect m_playerHpRect{ kWindWidht - 80, kWindHeight - 45, 60, 40 };
};
