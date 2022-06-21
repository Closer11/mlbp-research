#ifndef __PROBLEMS_H__
#define __PROBLEMS_H__

#include <string_view>

/**
 * Defines for each problem an own problem type.
 * This problem type is used in generic algorithms.
 */

/* Bin Packing Problem */
struct BP
{
	constexpr static const std::string_view name = "Bin Packing Problem";
};

/* Multi-Level Bin Packing Problem */
struct MLBP
{
	constexpr static const std::string_view name = "Multi-Level Bin Packing Problem";
};

/* Multi-Level Bin Packing Problem with Fragmentation Constraints */
struct MLBPFC
{
	constexpr static const std::string_view name = "Multi-Level Bin Packing Problem with Fragmentation Constraints";
};


#endif // __PROBLEMS_H__
