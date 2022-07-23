#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

/*
Time complexity: O(n)
Space complexity: O(n)
*/
uint64_t fibonacciTabulated(uint64_t number)
{
	std::vector<uint64_t> table(std::max(2ull, number + 1), 0);
	
	table.at(1) = 1;
	
	for (auto i = 2u; i < table.size(); ++i)
	{
		table.at(i) = table.at(i - 1) + table.at(i - 2);
	}
	
	return table.at(number);
}

TEST_CASE("Fibonacci tabulated")
{
    SUBCASE("0")
	{ REQUIRE(fibonacciTabulated(0) == 0); }
	
	SUBCASE("1")
	{ REQUIRE(fibonacciTabulated(1) == 1); }
	
	SUBCASE("2")
	{ REQUIRE(fibonacciTabulated(2) == 1); }
	
	SUBCASE("3")
	{ REQUIRE(fibonacciTabulated(3) == 2); }
	
	SUBCASE("20")
	{ REQUIRE(fibonacciTabulated(20) == 6765); }
	
	SUBCASE("40")
	{ REQUIRE(fibonacciTabulated(40) == 102334155); }
}
