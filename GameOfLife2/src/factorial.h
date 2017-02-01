#pragma once
#include <cstdint>

// Compute the factorial of a number.
// Throws std::out_of_range if the result doesn't fit in a uint64_t.
uint64_t factorial(uint64_t n);
