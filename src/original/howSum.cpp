#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <ostream>

/*
Time complexity: O(n^m*m)
Space complexity: O(m)
*/
std::vector<int32_t> howSum(int32_t target, const std::unordered_set<int32_t>& values)
{
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
        
        auto howSumResult = howSum(remainder, values);
		
		if (howSumResult.empty() || howSumResult.back() != -1)
		{
			howSumResult.emplace_back(value);
			
			return howSumResult;
		}
    }
    
    return {-1};
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
	{ REQUIRE(howSum(0, {}) == std::vector<int32_t>{}); }
	
	SUBCASE("0, [0]")
	{ REQUIRE(howSum(0, {0}) == std::vector<int32_t>{}); }
	
	SUBCASE("0, [1]")
	{ REQUIRE(howSum(0, {1}) == std::vector<int32_t>{}); }
	
	SUBCASE("2, [2]")
	{ REQUIRE(howSum(2, {2}) == std::vector<int32_t>{2}); }
	
	SUBCASE("2, [3]")
	{ REQUIRE(howSum(2, {3}) == std::vector<int32_t>{-1}); }
	
	SUBCASE("7, [2, 3]")
	{ REQUIRE(howSum(7, {2, 3}) == std::vector<int32_t>{2, 2, 3}); }
	
	SUBCASE("7, [2, 4]")
	{ REQUIRE(howSum(7, {2, 4}) == std::vector<int32_t>{-1}); }
	
	SUBCASE("50, [12, 3, 20]")
	{ REQUIRE(howSum(50, {12, 3, 20}) == std::vector<int32_t>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 20}); }
	
	SUBCASE("50, [12, 3, 21]")
	{ REQUIRE(howSum(50, {12, 3, 21}) == std::vector<int32_t>{-1}); }
}