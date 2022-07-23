#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

/*
Time complexity: O(n*m^2)
Space complexity: O(m)
*/
bool canConstructTabulated(std::string_view target, const std::vector<std::string_view>& values)
{
	std::vector<bool> table(target.size() + 1, false);
	
	table.at(0) = true;
	
	for (auto i = 0u; i < table.size(); ++i)
	{
		if (table.at(i) == false)
		{
			continue;
		}
		
		for (auto& value: values)
		{
			auto offsetIterator = std::next(target.cbegin(), i);
			auto positions = std::mismatch(offsetIterator, target.cend(), value.cbegin(), value.cend());
		
			if (std::get<0>(positions) == offsetIterator || std::get<1>(positions) != value.cend())
			{
				continue;
			}
			
			table.at(i + value.size()) = true;
		}
	}
	
	return table.back();
}

TEST_CASE("Can construct tabulated")
{
	SUBCASE("Target: \"abcdef\", values available: [\"ab\", \"abc\", \"cd\", \"def\", \"abcd\"]")
	{ REQUIRE(canConstructTabulated("abcdef", {"ab", "abc", "cd", "def", "abcd"}) == true); }
	
	SUBCASE("Target: \"skateboard\", values available: [\"bo\", \"rd\", \"ate\", \"t\", \"ska\", \"sk\", \"boar\"]")
	{ REQUIRE(canConstructTabulated("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}) == false); }
	
	SUBCASE("Target: \"enterapotentpot\", values available: [\"a\", \"p\", \"ent\", \"enter\", \"ot\", \"o\", \"t\"]")
	{ REQUIRE(canConstructTabulated("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}) == true); }
	
	SUBCASE("Target: \"eeeeeeeeeeeeeeeeeeeeeef\", values available: [\"e\", \"ee\", \"eee\", \"eeee\", \"eeeee\", \"eeeeee\"]")
	{ REQUIRE(canConstructTabulated("eeeeeeeeeeeeeeeeeeeeeef", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}) == false); }
}