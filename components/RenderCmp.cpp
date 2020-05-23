/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#include "RenderCmp.h"

RenderCmp_t::RenderCmp_t(std::size_t eid, types renType)
	: Component_t(eid)
	, m_type(renType)
{ }

RenderCmp_t& RenderCmp_t::operator=(const RenderCmp_t& rh)
{
	if (this == &rh) return *this;

	Component_t::operator = (rh);
	m_type = rh.m_type;
	
	return *this;
}

void RenderCmp_t::update()
{
}
