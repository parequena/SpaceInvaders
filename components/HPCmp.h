/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#pragma once
#include <tinyECS/Component.h>

struct HPCmp_t : tinyECS::Component_t
{
	// Ctor.
	explicit HPCmp_t(std::size_t eid);

	// Ctor.
	explicit HPCmp_t(std::size_t eid, uint8_t hp);

	// Update.
	void update() override;

	// operator=
	HPCmp_t& operator=(const HPCmp_t& rh);

	// HP
	uint8_t m_hp{ 1 };
};

