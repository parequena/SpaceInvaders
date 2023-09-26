/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#pragma once

#include <stack>
#include "utils.h"

namespace tinyECS
{
struct State_t
{
   virtual bool run() = 0;
   virtual ~State_t() = default;
};

struct StateManager_t
{
   // Ctor.
   explicit StateManager_t() noexcept = default;

   // push
   template <typename stt_t, typename... ts> void pushState(ts&&... args)
   {
      static_assert(std::is_base_of<State_t, stt_t>::value, "StateManager_t::pushState ERROR : Unknown state!");
      m_status.push(std::make_unique<stt_t>(std::forward<decltype(args)>(args)...));
   }

   // run
   bool run();

private:
   // States stack
   std::stack<uptr_t<State_t>> m_status{};
};
}
