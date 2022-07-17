#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

/*
Time complexity: O(n^m)
Space complexity: O(m)
*/
bool canSum(int32_t target, const std::unordered_set<int32_t>& values)
{
    if (target < 0)
    {
        return false;
    }
    
    if (target == 0)
    {
        return true;
    }
       
    for (auto value: values)
    {
        auto remainder = target - value;
        
        if (canSum(remainder, values))
        {            
            return true;
        }
    }
    
    return false;
}

TEST_CASE("Can sum")
{
	SUBCASE("Target: 0, values available: [1, 2]")
	{ REQUIRE(canSum(0, {1, 2}) == true); }
	
	SUBCASE("Target: 7, values available: []")
	{ REQUIRE(canSum(7, {}) == false); }
	
    SUBCASE("Target: 7, values available: [2, 3]")
	{ REQUIRE(canSum(7, {2, 3}) == true); }
	
	SUBCASE("Target: 7, values available: [5, 3, 4, 7]")
	{ REQUIRE(canSum(7, {5, 3, 4, 7}) == true); }
	
	SUBCASE("Target: 7, values available: [2, 4]")
	{ REQUIRE(canSum(7, {2, 4}) == false); }
	
	SUBCASE("Target: 8, values available: [2, 3, 5]")
	{ REQUIRE(canSum(8, {2, 3, 5}) == true); }
	
	SUBCASE("Target: 150, values available: [7, 21]")
	{ REQUIRE(canSum(150, {7, 21}) == false); }
}