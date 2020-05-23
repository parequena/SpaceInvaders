/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#include "StateManager.h"

namespace tinyECS
{
	// run
	bool StateManager_t::run()
	{
		if (m_status.empty()) return false;

		auto& state{ m_status.top() };
		if (!state) return false;

		const auto childAlive{ state->run() };
		if(!childAlive) m_status.pop(); // If not alive, pop.
		
		return !m_status.empty(); // Check for more states.
	}
}
