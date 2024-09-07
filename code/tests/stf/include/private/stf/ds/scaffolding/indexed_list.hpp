#pragma once

#include <array>
#include <string>

#include <gtest/gtest.h>

#include <stf/ds/indexed_list.hpp>

namespace stf::ds::scaffolding::indexed_list
{

	using list_t = stf::ds::indexed_list<std::string, int>;

	using pair_t = list_t::pair_t;

	inline std::vector<pair_t> pairs()
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
		for (pair_t const& pair : pairs())
		{
			list.push_back(pair.key, pair.entry);
		}
		return list;
	}

	inline void verify(std::vector<pair_t> const& pairs, list_t const& list)
	{
		ASSERT_EQ(pairs.size(), list.size()) << "Failed size check";
		size_t i = 0;
		for (pair_t const& pair : list)
		{
			ASSERT_EQ(pairs[i].key, pair.key) << "Failed key comparison for pair with index '" << i << "'";
			ASSERT_EQ(pairs[i].entry, pair.entry) << "Failed entry comparison for pair with index '" << i << "'";
			++i;
		}
	}

} // stf::ds::scaffolding::indexed_list