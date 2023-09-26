/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#pragma once

#include <tinyECS/StateManager.h>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;

struct RenderSys_t;

namespace tinyECS
{
struct MenuState_t : tinyECS::State_t
{
   // Ctor.
   explicit MenuState_t(RenderSys_t& renderSys) noexcept;

   // Dtor.
   ~MenuState_t() = default;

   // run
   bool run() override;

private:
   // Surfaces.
   vect_t<SDL_Surface*> m_surfaces{};

   // Texture on.
   vect_t<SDL_Texture*> m_texturesON{};

   // Textures off.
   vect_t<SDL_Texture*> m_texturesOFF{};

   // Num entities
   std::uint8_t m_nColsEnemies{ 9 };
   std::uint8_t m_nRowsEnemies{ 5 };
   std::uint8_t m_nColsCovers{ 4 };

   // Window.
   RenderSys_t& m_renderSys;

   // Min index
   const std::uint8_t m_minIdx{ 0 };

   // Max index
   const std::uint8_t m_maxIdx{ 1 };

   // Current index
   std::uint8_t m_idx{ m_minIdx };

   // Draw
   void draw();
};
}
