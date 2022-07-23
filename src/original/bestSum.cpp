#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <ostream>

/*
Time complexity: O(n^m*m)
Space complexity: O(m^2)
*/
std::vector<int32_t> bestSum(int32_t target, const std::unordered_set<int32_t>& values)
{  
	if (target < 0)
    {
        return {-1};
    }
    
    if (target == 0)
    {
        return {};
    }
    
	std::vector<int32_t> bestCombination {-1};
	
    for (auto value: values)
    {
        auto remainder = target - value;
        
        auto result = bestSum(remainder, values);
		
		if (result.empty() || result.back() != -1)
		{
			result.emplace_back(value);
			
			if (bestCombination.back() == -1 || result.size() < bestCombination.size())
			{
				bestCombination = result;
			}
		}
    }
    
    return bestCombination;
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

TEST_CASE("Best sum")
{
    SUBCASE("0, []")
	{ REQUIRE(bestSum(0, {}) == std::vector<int32_t>{}); }
	
	SUBCASE("0, [0]")
	{ REQUIRE(bestSum(0, {0}) == std::vector<int32_t>{}); }
	
	SUBCASE("0, [1]")
	{ REQUIRE(bestSum(0, {1}) == std::vector<int32_t>{}); }
	
	SUBCASE("2, [2]")
	{ REQUIRE(bestSum(2, {2}) == std::vector<int32_t>{2}); }
	
	SUBCASE("2, [3]")
	{ REQUIRE(bestSum(2, {3}) == std::vector<int32_t>{-1}); }
	
	SUBCASE("7, [2, 3]")
	{ REQUIRE(bestSum(7, {2, 3}) == std::vector<int32_t>{2, 2, 3}); }
	
	SUBCASE("7, [2, 4]")
	{ REQUIRE(bestSum(7, {2, 4}) == std::vector<int32_t>{-1}); }
	
	SUBCASE("50, [12, 3, 20]")
	{ REQUIRE(bestSum(50, {12, 3, 20}) == std::vector<int32_t>{12, 12, 3, 3, 20}); }
	
	SUBCASE("50, [12, 3, 21]")
	{ REQUIRE(bestSum(50, {12, 3, 21}) == std::vector<int32_t>{-1}); }
}