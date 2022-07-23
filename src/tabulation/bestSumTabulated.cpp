#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <ostream>

/*
Time complexity: O(n*m^2)
Space complexity: O(m^2)
*/
std::vector<int32_t> bestSumTabulated(int32_t targetSum, const std::vector<int32_t>& values)
{
	std::vector<std::vector<int32_t>> table(targetSum + 1, {-1});
	
	table.at(0).pop_back();
	
	for (auto i = 0; i < targetSum; ++i)
	{
		if (table.at(i).back() == -1)
		{
			continue;
		}
	
		for(auto value: values)
		{
			auto index = i + value;
			
			if (index > targetSum)
			{
				continue;
			}
			
			if (!table.at(index).empty() && table.at(index).at(0) == -1)
			{
				table.at(index).pop_back();
			}
			
			if (table.at(index).empty() || table.at(index).size() > table.at(i).size() + 1)
			{
				table.at(index) = table.at(i);
				table.at(index).push_back(value);
			}
		}
	}
	
	return table.at(targetSum);
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

TEST_CASE("Best sum tabulated")
{
    SUBCASE("0, []")
	{ REQUIRE(bestSumTabulated(0, {}) == std::vector<int32_t>{}); }
	
	SUBCASE("0, [0]")
	{ REQUIRE(bestSumTabulated(0, {0}) == std::vector<int32_t>{}); }
	
	SUBCASE("0, [1]")
	{ REQUIRE(bestSumTabulated(0, {1}) == std::vector<int32_t>{}); }
	
	SUBCASE("2, [2]")
	{ REQUIRE(bestSumTabulated(2, {2}) == std::vector<int32_t>{2}); }
	
	SUBCASE("2, [3]")
	{ REQUIRE(bestSumTabulated(2, {3}) == std::vector<int32_t>{-1}); }
	
	SUBCASE("7, [2, 3]")
	{ REQUIRE(bestSumTabulated(7, {2, 3}) == std::vector<int32_t>{ 2, 2, 3 }); }
	
	SUBCASE("7, [2, 4]")
	{ REQUIRE(bestSumTabulated(7, {2, 4}) == std::vector<int32_t>{-1}); }
	
	SUBCASE("50, [12, 3, 20]")
	{ REQUIRE(bestSumTabulated(50, {12, 3, 20}) == std::vector<int32_t>{ 3, 3, 12, 12, 20 }); }
	
	SUBCASE("50, [12, 3, 21]")
	{ REQUIRE(bestSumTabulated(50, {12, 3, 21}) == std::vector<int32_t>{-1}); }
	
	SUBCASE("300, [7, 14]")
	{ REQUIRE(bestSumTabulated(300, {7, 14}) == std::vector<int32_t>{-1}); }
	
	SUBCASE("1002, [7, 14, 30]")
	{ REQUIRE(bestSumTabulated(1002, {7, 14, 30}) == std::vector<int32_t>{14, 14, 14, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30}); } 
}