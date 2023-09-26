/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#pragma once

namespace tinyECS
{
struct Entity_t
{
   explicit Entity_t() noexcept
       : m_entityId(++kNextEntityID)
   {
   }

   [[nodiscard]] constexpr std::size_t getEntityID() const noexcept { return m_entityId; }

protected:
   // Next entity ID.
   static inline std::size_t kNextEntityID{ 0 };

   // My entity id.
   const std::size_t m_entityId{ 0 };
};
} // namespace tinyECS
