#include "create_map_from_vector.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <utility>

std::map<uint64_t, Foo*> create_map_from_vector(std::vector<Foo>& foos) {
	std::map<uint64_t, Foo*> result;
	std::transform(foos.begin(), foos.end(), std::inserter(result, result.begin()),
		       [](Foo& f) { return std::make_pair<uint64_t, Foo*>(f.getId(), &f); });
	return result;
}

