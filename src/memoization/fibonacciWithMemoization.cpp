#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <unordered_map>

/*
Time complexity: O(n)
Space complexity: O(n)
*/
uint64_t fibonacciWithMemoization(uint16_t number, std::unordered_map<uint16_t, uint64_t>& lookupTable)
{
	if (lookupTable.contains(number))
	{
		return lookupTable.at(number);
	}
	
	if (number == 0)
	{
		return 0;
	}
	else if (number == 1)
	{
		return 1;
	}
	
	auto fibonacciNumber = fibonacciWithMemoization(number - 1, lookupTable) + fibonacciWithMemoization(number - 2, lookupTable);
	lookupTable.emplace(number, fibonacciNumber);
	
	return fibonacciNumber;
}

uint64_t fibonacciWithMemoization(uint16_t number)
{
	std::unordered_map<uint16_t, uint64_t> lookupTable;
	
	return fibonacciWithMemoization(number, lookupTable);
}

TEST_CASE("Fibonacci with memoization")
{
    SUBCASE("0")
	{ REQUIRE(fibonacciWithMemoization(0) == 0); }
	
	SUBCASE("1")
	{ REQUIRE(fibonacciWithMemoization(1) == 1); }
	
	SUBCASE("2")
	{ REQUIRE(fibonacciWithMemoization(2) == 1); }
	
	SUBCASE("3")
	{ REQUIRE(fibonacciWithMemoization(3) == 2); }
	
	SUBCASE("20")
	{ REQUIRE(fibonacciWithMemoization(20) == 6765); }
	
	SUBCASE("40")
	{ REQUIRE(fibonacciWithMemoization(40) == 102334155); }
}