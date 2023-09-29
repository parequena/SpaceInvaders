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

void RenderCmp_t::update()
{
}
