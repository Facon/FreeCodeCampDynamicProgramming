#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

/*
Time complexity: O(n*m)
Space complexity: O(n*m)
*/
uint64_t gridTravelerTabulated(uint64_t x, uint64_t y)
{
	std::vector<std::vector<uint64_t>> table(y + 1, std::vector<uint64_t>(x + 1, 0));
	
	if (x == 0 || y == 0)
	{
		return 0;
	}
	
	table.at(1).at(1) = 1;
	
	for (auto j = 1u; j < y + 1; ++j)
	{
		for (auto i = 1u; i < x + 1; ++i)
		{
			table.at(j).at(i) += table.at(j - 1).at(i) + table.at(j).at(i - 1);
		}
	}
	
	return table.at(y).at(x);
}

TEST_CASE("Grid traveler tabulated")
{
    SUBCASE("0, 0")
	{ REQUIRE(gridTravelerTabulated(0, 0) == 0); }
	
	SUBCASE("1, 0")
	{ REQUIRE(gridTravelerTabulated(1, 0) == 0); }
	
	SUBCASE("0, 1")
	{ REQUIRE(gridTravelerTabulated(0, 1) == 0); }
	
	SUBCASE("1, 1")
	{ REQUIRE(gridTravelerTabulated(1, 1) == 1); }
	
	SUBCASE("1, 2")
	{ REQUIRE(gridTravelerTabulated(1, 2) == 1); }
	
	SUBCASE("2, 1")
	{ REQUIRE(gridTravelerTabulated(2, 1) == 1); }
	
	SUBCASE("2, 2")
	{ REQUIRE(gridTravelerTabulated(2, 2) == 2); }
	
	SUBCASE("2, 3")
	{ REQUIRE(gridTravelerTabulated(2, 3) == 3); }
	
	SUBCASE("3, 2")
	{ REQUIRE(gridTravelerTabulated(3, 2) == 3); }
	
	SUBCASE("3, 3")
	{ REQUIRE(gridTravelerTabulated(3, 3) == 6); }
	
	SUBCASE("4, 4")
	{ REQUIRE(gridTravelerTabulated(4, 4) == 20); }
	
	SUBCASE("14, 14")
	{ REQUIRE(gridTravelerTabulated(14, 14) == 10400600); }
	
	SUBCASE("18, 18")
	{ REQUIRE(gridTravelerTabulated(18, 18) == 2333606220); }
}