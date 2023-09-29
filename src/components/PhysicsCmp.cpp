/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#include "PhysicsCmp.h"
#include "RenderCmp.h"
#include <tinyECS/ComponentStorage.h>

// Ctor.
PhysicsCmp_t::PhysicsCmp_t(std::size_t eid, std::uint32_t x, std::uint32_t y, std::uint32_t w, std::uint32_t h)
	: tinyECS::Component_t(eid)
	, m_x(x)
	, m_y(y)
	, m_w(w)
	, m_h(h)
{ }

void PhysicsCmp_t::update()
{
	// Update local position.
	m_x += std::uint32_t(m_vx);
	m_y += std::uint32_t(m_vy);
}
