/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#include <SDL.h>
#include <tuple>
#include "CollisionCmp.h"
#include "PhysicsCmp.h"
#include <tinyECS/GameContext.h>

struct PhysicsCmp_t;

CollisionCmp_t::CollisionCmp_t(std::size_t eid, const SDL_Rect& rect)
	: Component_t(eid)
	, m_prevPos()
	, m_boundingBox(rect)
{
}

CollisionCmp_t& CollisionCmp_t::operator=(const CollisionCmp_t& rh)
{
	if (this == &rh) return *this;
	Component_t::operator = (rh);
	m_prevPos = rh.m_prevPos;
	m_boundingBox = rh.m_boundingBox;
	m_properties = rh.m_properties;
	m_mask = rh.m_mask;

	return *this;
}

void CollisionCmp_t::update()
{
	auto phyCmp = tinyECS::GameContext_t::getCmpStorage()->getComponentFromID<PhysicsCmp_t>(getEntityID());
	if (!phyCmp) return;
	const auto newColl = phyCmp->get().getRect();

	m_prevPos = m_boundingBox; // Save previous position;
	m_boundingBox = newColl;
}
