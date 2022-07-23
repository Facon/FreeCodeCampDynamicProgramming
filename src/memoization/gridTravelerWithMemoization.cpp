#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <unordered_map>

/*
Time complexity: O(n*m)
Space complexity: O(n*m)
*/
uint64_t gridTravelerWithMemoization(uint64_t x, uint64_t y, std::unordered_map<std::string, uint64_t>& memoization)
{
    std::string key(std::to_string(x) + ", " + std::to_string(y));
    
    if (memoization.contains(key))
    {
        return memoization.at(key);
    }
    
    if (x == 1 && y == 1)
    {
        return 1;
    }
    
    if (x < 1 || y < 1)
    {
        return 0;
    }
    
    auto value = gridTravelerWithMemoization(x - 1, y, memoization) + gridTravelerWithMemoization(x, y - 1, memoization);
    memoization.emplace(key, value);
    
    return value;
}

uint64_t gridTravelerWithMemoization(uint64_t x, uint64_t y)
{
	std::unordered_map<std::string, uint64_t> memoization;
	
	return gridTravelerWithMemoization(x, y, memoization);
}

TEST_CASE("Grid traveler with memoization")
{
    SUBCASE("0, 0")
	{ REQUIRE(gridTravelerWithMemoization(0, 0) == 0); }
	
	SUBCASE("1, 0")
	{ REQUIRE(gridTravelerWithMemoization(1, 0) == 0); }
	
	SUBCASE("0, 1")
	{ REQUIRE(gridTravelerWithMemoization(0, 1) == 0); }
	
	SUBCASE("1, 1")
	{ REQUIRE(gridTravelerWithMemoization(1, 1) == 1); }
	
	SUBCASE("1, 2")
	{ REQUIRE(gridTravelerWithMemoization(1, 2) == 1); }
	
	SUBCASE("2, 1")
	{ REQUIRE(gridTravelerWithMemoization(2, 1) == 1); }
	
	SUBCASE("2, 2")
	{ REQUIRE(gridTravelerWithMemoization(2, 2) == 2); }
	
	SUBCASE("2, 3")
	{ REQUIRE(gridTravelerWithMemoization(2, 3) == 3); }
	
	SUBCASE("3, 2")
	{ REQUIRE(gridTravelerWithMemoization(3, 2) == 3); }
	
	SUBCASE("3, 3")
	{ REQUIRE(gridTravelerWithMemoization(3, 3) == 6); }
	
	SUBCASE("4, 4")
	{ REQUIRE(gridTravelerWithMemoization(4, 4) == 20); }
	
	SUBCASE("14, 14")
	{ REQUIRE(gridTravelerWithMemoization(14, 14) == 10400600); }
	
	SUBCASE("18, 18")
	{ REQUIRE(gridTravelerWithMemoization(18, 18) == 2333606220); }
}