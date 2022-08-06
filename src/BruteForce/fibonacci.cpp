#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

/*
Time complexity: O(2^n)
Space complexity: O(n)
*/
uint64_t fibonacci(uint16_t number)
{
	if (number == 0)
	{
		return 0;
	}
	else if (number == 1)
	{
		return 1;
	}
	
	return fibonacci(number - 1) + fibonacci(number - 2);
}

TEST_CASE("Fibonacci")
{
    SUBCASE("0")
	{ REQUIRE(fibonacci(0) == 0); }
	
	SUBCASE("1")
	{ REQUIRE(fibonacci(1) == 1); }
	
	SUBCASE("2")
	{ REQUIRE(fibonacci(2) == 1); }
	
	SUBCASE("3")
	{ REQUIRE(fibonacci(3) == 2); }
	
	SUBCASE("20")
	{ REQUIRE(fibonacci(20) == 6765); }
	
	SUBCASE("30")
	{ REQUIRE(fibonacci(30) == 832040); }
}
