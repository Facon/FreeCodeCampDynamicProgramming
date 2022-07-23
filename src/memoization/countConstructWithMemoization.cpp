#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <unordered_map>

/*
Time complexity: O(n*m2)
Space complexity: O(m^2)
*/
uint32_t countConstructWithMemoization(std::string_view target, const std::vector<std::string_view>& values, std::unordered_map<std::string_view, uint32_t>& memoization)
{
	if (memoization.contains(target))
	{
		return memoization.at(target);
	}
	
	if (target.empty())
	{
		return 1;
	}
	
	uint32_t count = 0;
	
	for (auto& value: values)
	{
		auto positions = std::mismatch(target.cbegin(), target.cend(), value.cbegin(), value.cend());
		
		if (std::get<0>(positions) == target.cbegin() || std::get<1>(positions) != value.cend())
		{
			continue;
		}
		
		std::string_view suffix(std::get<0>(positions), target.cend());
		
		auto result = countConstructWithMemoization(suffix, values, memoization);
		
		count += result;
	}
	
	memoization.emplace(target, count);
	
	return count;
}

uint32_t countConstructWithMemoization(std::string_view target, const std::vector<std::string_view>& values)
{
	std::unordered_map<std::string_view, uint32_t> memoization;
	return countConstructWithMemoization(target, values, memoization);
}

TEST_CASE("Count construct with memoization")
{
	SUBCASE("Target: \"abcdef\", values available: [\"ab\", \"abc\", \"cd\", \"def\", \"abcd\"]")
	{ REQUIRE(countConstructWithMemoization("abcdef", {"ab", "abc", "cd", "def", "abcd"}) == 1); }
	
	SUBCASE("Target: \"skateboard\", values available: [\"bo\", \"rd\", \"ate\", \"t\", \"ska\", \"sk\", \"boar\"]")
	{ REQUIRE(countConstructWithMemoization("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}) == 0); }
	
	SUBCASE("Target: \"enterapotentpot\", values available: [\"a\", \"p\", \"ent\", \"enter\", \"ot\", \"o\", \"t\"]")
	{ REQUIRE(countConstructWithMemoization("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}) == 4); }
	
	SUBCASE("Target: \"abcdefg\", values available: [\"a\", \"b\", \"c\", \"d\", \"abcd\", \"efg\"]")
	{ REQUIRE(countConstructWithMemoization("abcdefg", {"a", "b", "c", "d", "abcd", "efg"}) == 2); }
	
	SUBCASE("Target: \"purple\", values available: [\"purp\", \"p\", \"ur\", \"le\", \"purpl\"]")
	{ REQUIRE(countConstructWithMemoization("purple", {"purp", "p", "ur", "le", "purpl"}) == 2); }
	
	SUBCASE("Target: \"eeeeeeeeeeeeeeeeef\", values available: [\"e\", \"ee\", \"eee\", \"eeee\", \"eeeee\", \"eeeeee\"]")
	{ REQUIRE(countConstructWithMemoization("eeeeeeeeeeeeeeeeef", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}) == 0); }
	
	SUBCASE("Target: \"eeeeeeeeeeeeeeeee\", values available: [\"e\", \"ee\", \"eee\", \"eeee\", \"eeeee\", \"eeeeee\"]")
	{ REQUIRE(countConstructWithMemoization("eeeeeeeeeeeeeeeee", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}) == 59448); }
}