#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

/*
Time complexity: O(n*m)
Space complexity: O(m)
*/
bool canSumTabulated(int32_t targetSum, const std::vector<int32_t>& values)
{
	std::vector<bool> table(targetSum + 1, false);
	
	table.at(0) = true;
	
	for (auto i = 0; i < targetSum; ++i)
	{
		for(auto value: values)
		{
			if (i + value >= std::ssize(table))
			{
				continue;
			}
		
			table.at(i + value) = table.at(i + value) | table.at(i);
		}
	}
	
	return table.at(targetSum);
}

TEST_CASE("Can sum tabulated")
{
	SUBCASE("Target: 0, values available: [1, 2]")
	{ REQUIRE(canSumTabulated(0, {1, 2}) == true); }
	
	SUBCASE("Target: 7, values available: []")
	{ REQUIRE(canSumTabulated(7, {}) == false); }
	
    SUBCASE("Target: 7, values available: [2, 3]")
	{ REQUIRE(canSumTabulated(7, {2, 3}) == true); }
	
	SUBCASE("Target: 7, values available: [5, 3, 4, 7]")
	{ REQUIRE(canSumTabulated(7, {5, 3, 4, 7}) == true); }
	
	SUBCASE("Target: 7, values available: [2, 4]")
	{ REQUIRE(canSumTabulated(7, {2, 4}) == false); }
	
	SUBCASE("Target: 8, values available: [2, 3, 5]")
	{ REQUIRE(canSumTabulated(8, {2, 3, 5}) == true); }
	
	SUBCASE("Target: 150, values available: [7, 21]")
	{ REQUIRE(canSumTabulated(150, {7, 21}) == false); }
	
	SUBCASE("Target: 300, values available: [7, 14]")
	{ REQUIRE(canSumTabulated(300, {7, 14}) == false); }
}