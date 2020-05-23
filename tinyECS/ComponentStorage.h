/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#pragma once

#include "utils.h"
#include "Component.h"
#include "../components/RenderCmp.h"

namespace tinyECS
{
	struct ComponentStorage_t;

	
	struct CmpVectrBase_t
	{
		virtual ~CmpVectrBase_t() = default;
		virtual void deleteCmpByEntityID(std::size_t eid) = 0;
		virtual void clear() = 0;
	};

	template <typename cmp_t> struct CmpVector_t : CmpVectrBase_t
	{
		std::vector<cmp_t> cmps{};
		void deleteCmpByEntityID(std::size_t eid) override final
		{
			auto idx{ 0 };
			for(auto& c : cmps)
			{
				if(c.getEntityID() == eid) break;
				++idx;
			}

			if (idx == cmps.size()) return;

			auto iter = cmps.begin() + idx;
			// std::cerr << "Erase: CP:" << iter->template getComponentTypeID<cmp_t>() << "\tEID: " << iter->getEntityID() << "\n";
			cmps.erase(iter);
		}
		void clear() { cmps.clear(); }
	};

	struct ComponentStorage_t
	{
		// Ctor.
		ComponentStorage_t() = default;
		
		// Creates a component vector.
		template <typename cmp_t> vect_t<cmp_t>& createCmpVect()
		{
			const auto cmpID = Component_t::getComponentTypeID<cmp_t>();
			auto v = std::make_unique<CmpVector_t<cmp_t>>();
			v->cmps.reserve(m_cmpVectSize);
			auto* vptr = v.get();
			m_components[cmpID] = std::move(v);

			return vptr->cmps;
		}

		// Get all components. If we dind't find it, it will create one!
		template <typename cmp_t> vect_t<cmp_t>& getComponents()
		{
			vect_t<cmp_t>* cmpVect{ nullptr };

			const auto cmpID = Component_t::getComponentTypeID<cmp_t>();
			const auto vIt = m_components.find(cmpID);

			if (vIt != m_components.end())
			{
				auto* v = dynamic_cast<CmpVector_t<cmp_t>*>(vIt->second.get());
				cmpVect = &v->cmps;
			}
			else cmpVect = &createCmpVect<cmp_t>();

			return *cmpVect;
		}

		// Gets an optional reference wrapper of an component.
		template <typename cmp_t> optRef_t<cmp_t> getComponentFromID(std::size_t eid)
		{
			auto& v = getComponents<cmp_t>();
			for (auto& c : v)
			{
				if (c.getEntityID() == eid)
					return c;
			}

			// std::cerr << "ComponentStorage_t::getComponentFromID: CP: " << Component_t::getComponentTypeID<cmp_t>() << "\tEID: " << eid << " COMPONENT NOT FOUND.\n";

			return {};
		}

		// Add a component.
		// template <typename cmp_t> void addComponent(cmp_t& c)
		// {
		// 	auto& v = getComponents<cmp_t>();
		// 	v.emplace_back(c);
		// }

		// Add a component.
		template <typename cmp_t> cmp_t& addComponent(cmp_t&& c)
		{
			auto& v = getComponents<cmp_t>();
			return v.emplace_back(c);
		}

		// Set size.
		constexpr void setVectSize(std::size_t size) noexcept { m_cmpVectSize = size; }

		// Erase all components of eid
		void eraseAllCmpsFromID(std::size_t eid)
		{
			for(auto& cmps: m_components)
			{
				cmps.second->deleteCmpByEntityID(eid);
			}
		}

		// Clear all
		void clearAll()
		{
			for (auto& cmps : m_components)
			{
				cmps.second->clear();
			}
		}
		
	private:		
		// Num of components on a vector.
		std::size_t m_cmpVectSize{100};

		// Hash table with all components by type.
		hash_t<std::size_t, uptr_t<CmpVectrBase_t>> m_components;
	};

} // namespace tinyECS