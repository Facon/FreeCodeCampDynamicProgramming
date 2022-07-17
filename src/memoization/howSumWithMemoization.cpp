#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <unordered_map>
#include <ostream>

/*
Time complexity: O(n*m^2)
Space complexity: O()
*/
std::vector<int32_t> howSumWithMemoization(int32_t target, const std::unordered_set<int32_t>& values, std::unordered_map<int32_t, std::vector<int32_t>>& memoization)
{
    if (memoization.contains(target))
	{
		return memoization.at(target);
	}
	
	if (target < 0)
    {
        return {-1};
    }
    
    if (target == 0)
    {
        return {};
    }
    
    for (auto value: values)
    {
        auto remainder = target - value;
        
        auto howSumResult = howSumWithMemoization(remainder, values, memoization);
		
		if (howSumResult.empty() || howSumResult.back() != -1)
		{
			howSumResult.emplace_back(value);
			memoization.emplace(remainder, howSumResult);
			
			return howSumResult;
		}
    }
	
	memoization.emplace(target, std::vector<int32_t>{-1});
    
    return {-1};
}

std::vector<int32_t> howSumWithMemoization(int32_t target, const std::unordered_set<int32_t>& values)
{
    std::unordered_map<int32_t, std::vector<int32_t>> memoization;
    
    return howSumWithMemoization(target, values, memoization);
}

namespace std // NOLINT(cert-dcl58-cpp)
{
template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& in) {
    stream << "[";
    for (size_t i = 0; i < in.size(); ++i) {
        if (i != 0) { stream << ", "; }
        stream << in[i];
    }
    stream << "]";
    return stream;
}
}

TEST_CASE("How sum with memoization")
{
    SUBCASE("0, []")
	{ REQUIRE(howSumWithMemoization(0, {}) == std::vector<int32_t>{}); }
	
	SUBCASE("0, [0]")
	{ REQUIRE(howSumWithMemoization(0, {0}) == std::vector<int32_t>{}); }
	
	SUBCASE("0, [1]")
	{ REQUIRE(howSumWithMemoization(0, {1}) == std::vector<int32_t>{}); }
	
	SUBCASE("2, [2]")
	{ REQUIRE(howSumWithMemoization(2, {2}) == std::vector<int32_t>{2}); }
	
	SUBCASE("2, [3]")
	{ REQUIRE(howSumWithMemoization(2, {3}) == std::vector<int32_t>{-1}); }
	
	SUBCASE("7, [2, 3]")
	{ REQUIRE(howSumWithMemoization(7, {2, 3}) == std::vector<int32_t>{2, 2, 3}); }
	
	SUBCASE("7, [2, 4]")
	{ REQUIRE(howSumWithMemoization(7, {2, 4}) == std::vector<int32_t>{-1}); }
	
	SUBCASE("50, [12, 3, 20]")
	{ REQUIRE(howSumWithMemoization(50, {12, 3, 20}) == std::vector<int32_t>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 20}); }
	
	SUBCASE("50, [12, 3, 21]")
	{ REQUIRE(howSumWithMemoization(50, {12, 3, 21}) == std::vector<int32_t>{-1}); }
	
	SUBCASE("300, [7, 14]")
	{ REQUIRE(howSumWithMemoization(300, {7, 14}) == std::vector<int32_t>{-1}); }
	
	SUBCASE("1002, [7, 14, 30]")
	{ REQUIRE(howSumWithMemoization(1002, {7, 14, 30}) == std::vector<int32_t>{14, 14, 14, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30}); }
}