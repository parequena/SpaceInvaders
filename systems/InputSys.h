/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#pragma once

struct InputSys_t
{
	// Ctor.
	explicit InputSys_t() = default;

	// update
	[[nodiscard]] static bool update();
};