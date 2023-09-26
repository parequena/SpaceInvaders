/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#pragma once
#include <tinyECS/Component.h>
#include <SDL.h>

struct PhysicsCmp_t final : tinyECS::Component_t
{
   // Ctor.
   PhysicsCmp_t(std::size_t eid, std::uint32_t x, std::uint32_t y, std::uint32_t w, std::uint32_t h);

   // Update;
   void update() override;

   // Velocity
   int32_t m_vx{ 0 }, m_vy{ 0 };

   // Speed
   std::uint8_t m_speed{ 8 };

   // Getter.
   [[nodiscard]] SDL_FRect getRect() const noexcept { return {float(m_x), float(m_y), float(m_w), float(m_h) }; }

   // Set position
   constexpr void setPos(SDL_FRect const pos) noexcept
   {
      m_x = std::uint32_t(pos.x);
      m_y = std::uint32_t(pos.y);
   }

   // Getters.
   [[nodiscard]] constexpr std::uint32_t getX() const noexcept { return m_x; }
   [[nodiscard]] constexpr std::uint32_t getY() const noexcept { return m_y; }
   [[nodiscard]] constexpr std::uint32_t getW() const noexcept { return m_w; }
   [[nodiscard]] constexpr std::uint32_t getH() const noexcept { return m_h; }

private:
   // Position.
   std::uint32_t m_x{ 0 }, m_y{ 0 };

   // Dimensions
   std::uint32_t m_w{ 0 }, m_h{ 0 };
};
