#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

/*
Time complexity: O(n*m^2)
Space complexity: O(m)
*/
int64_t countConstructTabulated(std::string_view target, const std::vector<std::string_view>& values)
{
	std::vector<int64_t> table(target.size() + 1, 0);
	
	table.at(0) = 1;
	
	for (auto i = 0u; i < table.size(); ++i)
	{
		if (table.at(i) == 0)
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
			
			table.at(i + value.size()) += table.at(i);
		}
	}
	
	return table.back();
}

TEST_CASE("Count construct tabulated")
{
	SUBCASE("Target: \"abcdef\", values available: [\"ab\", \"abc\", \"cd\", \"def\", \"abcd\"]")
	{ REQUIRE(countConstructTabulated("abcdef", {"ab", "abc", "cd", "def", "abcd"}) == 1); }
	
	SUBCASE("Target: \"skateboard\", values available: [\"bo\", \"rd\", \"ate\", \"t\", \"ska\", \"sk\", \"boar\"]")
	{ REQUIRE(countConstructTabulated("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}) == 0); }
	
	SUBCASE("Target: \"enterapotentpot\", values available: [\"a\", \"p\", \"ent\", \"enter\", \"ot\", \"o\", \"t\"]")
	{ REQUIRE(countConstructTabulated("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}) == 4); }
	
	SUBCASE("Target: \"abcdefg\", values available: [\"a\", \"b\", \"c\", \"d\", \"abcd\", \"efg\"]")
	{ REQUIRE(countConstructTabulated("abcdefg", {"a", "b", "c", "d", "abcd", "efg"}) == 2); }
	
	SUBCASE("Target: \"purple\", values available: [\"purp\", \"p\", \"ur\", \"le\", \"purpl\"]")
	{ REQUIRE(countConstructTabulated("purple", {"purp", "p", "ur", "le", "purpl"}) == 2); }
	
	SUBCASE("Target: \"eeeeeeeeeeeeeeeeef\", values available: [\"e\", \"ee\", \"eee\", \"eeee\", \"eeeee\", \"eeeeee\"]")
	{ REQUIRE(countConstructTabulated("eeeeeeeeeeeeeeeeef", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}) == 0); }
	
	SUBCASE("Target: \"eeeeeeeeeeeeeeeee\", values available: [\"e\", \"ee\", \"eee\", \"eeee\", \"eeeee\", \"eeeeee\"]")
	{ REQUIRE(countConstructTabulated("eeeeeeeeeeeeeeeee", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}) == 59448); }
}