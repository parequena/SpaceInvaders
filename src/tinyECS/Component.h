/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#pragma once

#include <cstdint>
#include <functional>

namespace tinyECS
{
struct Component_t
{
   // Ctor.
   explicit Component_t(std::size_t eid)
       : m_cmpID(++kNextCmpID)
       , m_entityID(eid)
   {
   }

   // Dtor.
   virtual ~Component_t() = default;

   // Get component ID.
   template <typename cmp_t> static inline std::size_t getComponentTypeID() noexcept
   {
      static std::size_t cmpType{ ++kNextCmpTypeID };
      return cmpType;
   }

   // Getters
   [[nodiscard]] constexpr std::size_t getEntityID() const noexcept { return m_entityID; }
   [[nodiscard]] constexpr std::size_t getCmpID() const noexcept { return m_entityID; }

   // Update.
   virtual void update() = 0;

private:
   // Next component ID.
   static inline std::size_t kNextCmpTypeID{ 0 };

   // Next component ID.
   static inline std::size_t kNextCmpID{ 0 };

   // Component ID.
   std::size_t m_cmpID{ 0 };

   // Enityt ID.
   std::size_t m_entityID{ 0 };
};
} // namespace tinyECS