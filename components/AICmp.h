/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#pragma once
#include <tinyECS/Component.h>

struct AICmp_t : tinyECS::Component_t
{
	// Ctor.
	explicit AICmp_t(std::size_t eid);

	// Operator=
	AICmp_t& operator=(const AICmp_t& rh);

	// Update.
	void update() override;

private:
	// Wait X executions.
	const uint16_t m_wait{ 8 };

	// Curret execution.
	uint16_t m_current{ 0 };
	
	// Original Steps to do.
	const uint16_t m_originalSteps{ 16 };
	
	// Steps to do.
	uint16_t m_steps{ 0 };

	// Direction.
	bool m_direction{ true };
};

