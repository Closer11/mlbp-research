#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include <string_view>

/**
 * Defines for each approximation algorithm its own algorithm type.
 * This algorithm type is used in generic algorithms.
 */

 /* Best Fit */
struct BF
{
	constexpr static const std::string_view name = "Best Fit";
};

/* First Fit */
struct FF
{
	constexpr static const std::string_view name = "First Fit";
};


#endif // __ALGORITHMS_H__
