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
PhysicsCmp_t::PhysicsCmp_t(std::size_t eid, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
	: tinyECS::Component_t(eid)
	, m_x(x)
	, m_y(y)
	, m_w(w)
	, m_h(h)
{ }

PhysicsCmp_t& PhysicsCmp_t::operator=(const PhysicsCmp_t& rh)
{
	if (this == &rh) return *this;
	Component_t::operator = (rh);
	m_x = rh.m_x;
	m_y = rh.m_y;
	m_w = rh.m_w;
	m_h = rh.m_h;
	m_vx = rh.m_vx;
	m_vy = rh.m_vy;
	m_speed = rh.m_speed;

	return *this;
}

void PhysicsCmp_t::update()
{
	// Update local position.
	m_x += m_vx;
	m_y += m_vy;
}
