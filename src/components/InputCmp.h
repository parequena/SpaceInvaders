/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#include <tinyECS/Component.h>
#include <SDL.h>

struct InputCmp_t final : tinyECS::Component_t
{
   // Ctor.
   explicit InputCmp_t(std::size_t eid);

   // Update;
   void update() override;

   // Left arrow.
   SDL_Keycode m_leftKey{ SDLK_LEFT };

   // Right arrow.
   SDL_Keycode m_rightKey{ SDLK_RIGHT };

   // Space to shoot.
   SDL_Keycode m_shootKey{ SDLK_SPACE };
};
