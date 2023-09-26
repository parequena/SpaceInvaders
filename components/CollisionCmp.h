/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#pragma once
#include <tinyECS/Component.h>

struct SDL_Rect;

struct CollisionCmp_t : tinyECS::Component_t
{
   // Ctor.
   explicit CollisionCmp_t(std::size_t eid, const SDL_FRect& rect);

   // Update.
   void update() override;

   // Set position
   constexpr void restorePosition() noexcept { m_boundingBox = m_prevPos; }

   // Previous collision position.
   SDL_FRect m_prevPos{};

   // Bouding box.
   SDL_FRect m_boundingBox{};

   // Collision layers.
   enum
   {
      L_zero = 0x0,
      L_one = 0x1,
      L_two = 0x2,
      L_three = 0x4,
      L_four = 0x8,
      L_all = 0xFF
   };

   // Collision propierties
   enum
   {
      P_none = 0x0,
      P_isPlayer = 0x1,
      P_isSolid = 0x2,
      P_damages = 0x4,
      P_isMovable = 0x8,
      P_isEnemy = 0x10
   };

   std::uint8_t m_properties{ 0 }; // Collision propierties.
   std::uint8_t m_mask{ L_all };   // Initial mask, to colide.
};
