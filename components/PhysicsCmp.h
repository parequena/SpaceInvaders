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
	PhysicsCmp_t(std::size_t eid, uint32_t x, uint32_t y, uint32_t w, uint32_t h);

	// Operator=
	PhysicsCmp_t& operator=(const PhysicsCmp_t& rh);

	// Update;
	void update() override;

	// Velocity
	int32_t m_vx{ 0 }, m_vy{ 0 };

	// Speed
	uint8_t m_speed{ 8 };

	// Getter.
	[[nodiscard]] SDL_Rect getRect() const noexcept { return { static_cast<int>(m_x), static_cast<int>(m_y), static_cast<int>(m_w), static_cast<int>(m_h) }; }

	// Set position
	constexpr void setPos(SDL_Rect pos) noexcept { m_x = pos.x; m_y = pos.y; };

	// Getters.
	[[nodiscard]] constexpr uint32_t getX() const noexcept { return m_x; };
	[[nodiscard]] constexpr uint32_t getY() const noexcept { return m_y; };
	[[nodiscard]] constexpr uint32_t getW() const noexcept { return m_w; };
	[[nodiscard]] constexpr uint32_t getH() const noexcept { return m_h; };
	
private:
	// Position.
	uint32_t m_x{ 0 }, m_y{ 0 };

	// Dimensions
	uint32_t m_w{ 0 }, m_h{ 0 };
};

