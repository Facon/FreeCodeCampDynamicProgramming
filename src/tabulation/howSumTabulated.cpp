#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <ostream>

/*
Time complexity: O(n*m^2)
Space complexity: O(m*m)
*/
std::vector<int32_t> howSumTabulated(int32_t targetSum, const std::vector<int32_t>& values)
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
			
			table.at(index) = table.at(i);
			table.at(index).push_back(value);
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

TEST_CASE("How sum tabulated")
{
    SUBCASE("0, []")
	{ REQUIRE(howSumTabulated(0, {}) == std::vector<int32_t>{}); }
	
	SUBCASE("0, [0]")
	{ REQUIRE(howSumTabulated(0, {0}) == std::vector<int32_t>{}); }
	
	SUBCASE("0, [1]")
	{ REQUIRE(howSumTabulated(0, {1}) == std::vector<int32_t>{}); }
	
	SUBCASE("2, [2]")
	{ REQUIRE(howSumTabulated(2, {2}) == std::vector<int32_t>{2}); }
	
	SUBCASE("2, [3]")
	{ REQUIRE(howSumTabulated(2, {3}) == std::vector<int32_t>{-1}); }
	
	SUBCASE("7, [2, 3]")
	{ REQUIRE(howSumTabulated(7, {2, 3}) == std::vector<int32_t>{ 3, 2, 2 }); }
	
	SUBCASE("7, [2, 4]")
	{ REQUIRE(howSumTabulated(7, {2, 4}) == std::vector<int32_t>{-1}); }
	
	SUBCASE("50, [12, 3, 20]")
	{ REQUIRE(howSumTabulated(50, {12, 3, 20}) == std::vector<int32_t>{ 20, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 }); }
	
	SUBCASE("50, [12, 3, 21]")
	{ REQUIRE(howSumTabulated(50, {12, 3, 21}) == std::vector<int32_t>{-1}); }
	
	SUBCASE("300, [7, 14]")
	{ REQUIRE(howSumTabulated(300, {7, 14}) == std::vector<int32_t>{-1}); }
	
	SUBCASE("1002, [7, 14, 30]")
	{ REQUIRE(howSumTabulated(1002, {7, 14, 30}) == std::vector<int32_t>{ 30, 30, 30, 30, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 }); }
}