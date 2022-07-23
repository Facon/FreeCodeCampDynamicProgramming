#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

/*
Time complexity: O(n^m*m)
Space complexity: O(m^2)
*/
bool canConstruct(std::string_view target, const std::vector<std::string_view>& values)
{
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
		
		auto result = canConstruct(suffix, values);
		
		if (result)
		{			
			return true;
		}
	}
	
	return false;
}

TEST_CASE("Can construct")
{
	SUBCASE("Target: \"abcdef\", values available: [\"ab\", \"abc\", \"cd\", \"def\", \"abcd\"]")
	{ REQUIRE(canConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd"}) == true); }
	
	SUBCASE("Target: \"skateboard\", values available: [\"bo\", \"rd\", \"ate\", \"t\", \"ska\", \"sk\", \"boar\"]")
	{ REQUIRE(canConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}) == false); }
	
	SUBCASE("Target: \"enterapotentpot\", values available: [\"a\", \"p\", \"ent\", \"enter\", \"ot\", \"o\", \"t\"]")
	{ REQUIRE(canConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}) == true); }
	
	SUBCASE("Target: \"eeeeeeeeeeeeeef\", values available: [\"e\", \"ee\", \"eee\", \"eeee\", \"eeeee\", \"eeeeee\"]")
	{ REQUIRE(canConstruct("eeeeeeeeeeeeeef", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}) == false); }
}