#pragma once

#include <array>
#include <string>

#include <gtest/gtest.h>

#include <stf/ds/indexed_list.hpp>

namespace stf::scaffolding::ds::indexed_list
{

	using list_t = stf::ds::indexed_list<std::string, int>;

	using element_t = list_t::element_t;

	inline std::vector<element_t> elements()
	{
		return
		{
			{ "zero", 0 },
			{ "one", 1 },
			{ "two", 2 },
			{ "three", 3 },
			{ "four", 4 },
		};
	}

	inline list_t construct()
	{
		list_t list;
		for (element_t const& element : elements())
		{
			list.push_back(element.key, element.entry);
		}
		return list;
	}

	inline void verify(std::vector<element_t> const& elements, list_t const& list)
	{
		ASSERT_EQ(elements.size(), list.size()) << "Failed size check";
		size_t i = 0;
		for (element_t const& element : list)
		{
			ASSERT_EQ(elements[i].key, element.key) << "Failed key comparison for element with index '" << i << "'";
			ASSERT_EQ(elements[i].entry, element.entry) << "Failed entry comparison for element with index '" << i << "'";
			++i;
		}
	}

} // stf::scaffolding::ds::indexed_list