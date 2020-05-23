/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#include "HPCmp.h"
#include <tinyECS/ComponentStorage.h>

HPCmp_t::HPCmp_t(std::size_t eid)
	: HPCmp_t(eid, 1)
{}

HPCmp_t::HPCmp_t(std::size_t eid, uint8_t hp)
	: Component_t(eid)
	, m_hp(hp)
{ }

void HPCmp_t::update()
{
}

HPCmp_t& HPCmp_t::operator=(const HPCmp_t& rh)
{
	if (this == &rh) return *this;
	Component_t::operator = (rh);
	m_hp = rh.m_hp;
	return *this;
}
