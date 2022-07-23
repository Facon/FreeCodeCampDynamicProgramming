#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <unordered_map>

/*
Time complexity: O(n*m^2)
Space complexity: O(m^2)
*/
bool canConstructWithMemoization(std::string_view target, const std::vector<std::string_view>& values, std::unordered_map<std::string_view, bool>& memoization)
{
	if (memoization.contains(target))
	{
		return memoization.at(target);
	}

	if (target.empty())
	{
		return true;
	}
	
	for (auto& value: values)
	{
		auto positions = std::mismatch(target.cbegin(), target.cend(), value.cbegin(), value.cend());
		
		if (std::get<0>(positions) == target.cbegin() || std::get<1>(positions) != value.cend())
		{
			continue;
		}
		
		std::string_view suffix(std::get<0>(positions), target.cend());
		
		auto result = canConstructWithMemoization(suffix, values, memoization);
		
		if (result)
		{
			memoization.emplace(target, true);
			
			return true;
		}
	}
	
	memoization.emplace(target, false);
	
	return false;
}

bool canConstructWithMemoization(std::string_view target, const std::vector<std::string_view>& values)
{
	std::unordered_map<std::string_view, bool> memoization;
	
	return canConstructWithMemoization(target, values, memoization);
}

TEST_CASE("Can construct with memoization")
{
	SUBCASE("Target: \"abcdef\", values available: [\"ab\", \"abc\", \"cd\", \"def\", \"abcd\"]")
	{ REQUIRE(canConstructWithMemoization("abcdef", {"ab", "abc", "cd", "def", "abcd"}) == true); }
	
	SUBCASE("Target: \"skateboard\", values available: [\"bo\", \"rd\", \"ate\", \"t\", \"ska\", \"sk\", \"boar\"]")
	{ REQUIRE(canConstructWithMemoization("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}) == false); }
	
	SUBCASE("Target: \"enterapotentpot\", values available: [\"a\", \"p\", \"ent\", \"enter\", \"ot\", \"o\", \"t\"]")
	{ REQUIRE(canConstructWithMemoization("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}) == true); }
	
	SUBCASE("Target: \"eeeeeeeeeeeeeeeeeeeeeef\", values available: [\"e\", \"ee\", \"eee\", \"eeee\", \"eeeee\", \"eeeeee\"]")
	{ REQUIRE(canConstructWithMemoization("eeeeeeeeeeeeeeeeeeeeeef", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}) == false); }
}