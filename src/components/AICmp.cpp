/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#include "AICmp.h"
#include "PhysicsCmp.h"
#include <tinyECS/GameContext.h>

AICmp_t::AICmp_t(std::size_t eid)
	: Component_t(eid)
{ }

void AICmp_t::update()
{
	auto phy = tinyECS::GameContext_t::getCmpStorage()->getComponentFromID<PhysicsCmp_t>(getEntityID());
	phy->get().m_vx = 0;
	phy->get().m_vy = 0;
	
	if(++m_current <= m_wait) return;
	m_current = 0;
	
	if (!phy) return;
	const auto movement = m_direction ? phy->get().m_speed : - phy->get().m_speed;
	phy->get().m_vx = movement;

	const auto x{ phy->get().getX() + phy->get().getW() / 2 };

	constexpr auto pShoot{ 1 };
	if(rand() % 200 < pShoot) tinyECS::EntityManager_t::createEnemyBullet(x, phy->get().getY()); // Shoots randomly.
	
	if(++m_steps == m_originalSteps)
	{
		m_steps = 0; // re-start.
		phy->get().m_vx = 0;
		phy->get().m_vy = 2*phy->get().m_speed;
		m_direction = !m_direction; // Change direction.
	}
}
