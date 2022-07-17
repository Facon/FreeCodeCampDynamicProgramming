#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <unordered_map>

/*
Time complexity: O(n*m)
Space complexity: O(m)
*/
bool canSumWithMemoization(int32_t target, const std::unordered_set<int32_t>& values, std::unordered_map<int32_t, bool>& memoization)
{
    if (memoization.contains(target))
    {
        return memoization.at(target);
    }
    
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
        
        if (canSumWithMemoization(remainder, values, memoization))
        {
            memoization.emplace(remainder, true);
            
            return true;
        }
        
        memoization.emplace(remainder, false);
    }
    
    return false;
}

bool canSumWithMemoization(int32_t target, const std::unordered_set<int32_t>& values)
{
    std::unordered_map<int32_t, bool> memoization;
    
    return canSumWithMemoization(target, values, memoization);
}

TEST_CASE("Can sum with memoization")
{
	SUBCASE("Target: 0, values available: [1, 2]")
	{ REQUIRE(canSumWithMemoization(0, {1, 2}) == true); }
	
	SUBCASE("Target: 7, values available: []")
	{ REQUIRE(canSumWithMemoization(7, {}) == false); }
	
    SUBCASE("Target: 7, values available: [2, 3]")
	{ REQUIRE(canSumWithMemoization(7, {2, 3}) == true); }
	
	SUBCASE("Target: 7, values available: [5, 3, 4, 7]")
	{ REQUIRE(canSumWithMemoization(7, {5, 3, 4, 7}) == true); }
	
	SUBCASE("Target: 7, values available: [2, 4]")
	{ REQUIRE(canSumWithMemoization(7, {2, 4}) == false); }
	
	SUBCASE("Target: 8, values available: [2, 3, 5]")
	{ REQUIRE(canSumWithMemoization(8, {2, 3, 5}) == true); }
	
	SUBCASE("Target: 150, values available: [7, 21]")
	{ REQUIRE(canSumWithMemoization(150, {7, 21}) == false); }
	
	SUBCASE("Target: 300, values available: [7, 14]")
	{ REQUIRE(canSumWithMemoization(300, {7, 14}) == false); }
}