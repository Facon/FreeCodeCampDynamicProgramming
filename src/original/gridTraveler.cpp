#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

/*
Time complexity: O(2^(n+m))
Space complexity: O(n+m)
*/
uint64_t gridTraveler(uint64_t x, uint64_t y)
{  
    if (x == 1 && y == 1)
    {
        return 1;
    }
    
    if (x < 1 || y < 1)
    {
        return 0;
    }
    
    return gridTraveler(x - 1, y) + gridTraveler(x, y - 1);
}

TEST_CASE("Grid traveler")
{
    SUBCASE("0, 0")
	{ REQUIRE(gridTraveler(0, 0) == 0); }
	
	SUBCASE("1, 0")
	{ REQUIRE(gridTraveler(1, 0) == 0); }
	
	SUBCASE("0, 1")
	{ REQUIRE(gridTraveler(0, 1) == 0); }
	
	SUBCASE("1, 1")
	{ REQUIRE(gridTraveler(1, 1) == 1); }
	
	SUBCASE("1, 2")
	{ REQUIRE(gridTraveler(1, 2) == 1); }
	
	SUBCASE("2, 1")
	{ REQUIRE(gridTraveler(2, 1) == 1); }
	
	SUBCASE("2, 2")
	{ REQUIRE(gridTraveler(2, 2) == 2); }
	
	SUBCASE("2, 3")
	{ REQUIRE(gridTraveler(2, 3) == 3); }
	
	SUBCASE("3, 2")
	{ REQUIRE(gridTraveler(3, 2) == 3); }
	
	SUBCASE("3, 3")
	{ REQUIRE(gridTraveler(3, 3) == 6); }
	
	SUBCASE("4, 4")
	{ REQUIRE(gridTraveler(4, 4) == 20); }
	
	SUBCASE("14, 14")
	{ REQUIRE(gridTraveler(14, 14) == 10400600); }
}