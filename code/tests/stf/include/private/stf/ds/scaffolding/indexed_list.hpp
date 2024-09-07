#pragma once

#include <array>
#include <string>

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

} // stf::ds::scaffolding::indexed_list