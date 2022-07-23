#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <string_view>

/*
Time complexity: O(n^m)
Space complexity: O(n^m)
*/
std::vector<std::vector<std::string_view>> allConstructTabulated(std::string_view target, const std::vector<std::string_view>& values)
{
	std::vector<std::vector<std::vector<std::string_view>>> table(target.size() + 1);
	
	table.at(0).push_back({});
	
	for (auto i = 0u; i < table.size(); ++i)
	{
		if (table.at(i).empty())
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
			
			auto lookAheadIndex = i + value.size();
			
			auto indexEndOfPosition = table.at(lookAheadIndex).size();
			
			table.at(lookAheadIndex).insert(table.at(lookAheadIndex).end(), table.at(i).cbegin(), table.at(i).cend());
			
			for (auto index = indexEndOfPosition; index < table.at(lookAheadIndex).size(); ++index)
			{
				table.at(lookAheadIndex).at(index).push_back(value);
			}
		}
	}
	
	return table.back();
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

TEST_CASE("All construct tabulated")
{
	SUBCASE("Target: \"abcdef\", values available: [\"ab\", \"abc\", \"cd\", \"def\", \"abcd\"]")
	{ REQUIRE(allConstructTabulated("abcdef", {"ab", "abc", "cd", "def", "abcd"}) == std::vector<std::vector<std::string_view>>{{ "abc", "def" }}); }
	
	SUBCASE("Target: \"skateboard\", values available: [\"bo\", \"rd\", \"ate\", \"t\", \"ska\", \"sk\", \"boar\"]")
	{ REQUIRE(allConstructTabulated("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}) == std::vector<std::vector<std::string_view>>{}); }
	
	SUBCASE("Target: \"enterapotentpot\", values available: [\"a\", \"p\", \"ent\", \"enter\", \"ot\", \"o\", \"t\"]")
	{ 
		REQUIRE(allConstructTabulated("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}) == std::vector<std::vector<std::string_view>>{
		{ "enter", "a", "p", "ot", "ent", "p", "ot" }, 
		{ "enter", "a", "p", "o", "t", "ent", "p", "ot" },
		{ "enter", "a", "p", "ot", "ent", "p", "o", "t" },  
		{ "enter", "a", "p", "o", "t", "ent", "p", "o", "t" } });
	}
	
	SUBCASE("Target: \"abcdefg\", values available: [\"a\", \"b\", \"c\", \"d\", \"abcd\", \"efg\"]")
	{ REQUIRE(allConstructTabulated("abcdefg", {"a", "b", "c", "d", "abcd", "efg"}) == std::vector<std::vector<std::string_view>>{{ "abcd", "efg" }, { "a", "b", "c", "d", "efg" }}); }
	
	SUBCASE("Target: \"purple\", values available: [\"purp\", \"p\", \"ur\", \"le\", \"purpl\"]")
	{ REQUIRE(allConstructTabulated("purple", {"purp", "p", "ur", "le", "purpl"}) == std::vector<std::vector<std::string_view>>{{ "purp", "le" }, { "p", "ur", "p", "le" }}); }
	
	SUBCASE("Target: \"eeeeeeeeeeeeeeeeeeeef\", values available: [\"e\", \"ee\", \"eee\", \"eeee\", \"eeeee\", \"eeeeee\"]")
	{ REQUIRE(allConstructTabulated("eeeeeeeeeeeeeeeeeeeef", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}) == std::vector<std::vector<std::string_view>>{}); };
	
	SUBCASE("Target: \"eeeeee\", values available: [\"e\", \"ee\", \"eee\", \"eeee\", \"eeeee\", \"eeeeee\"]")
	{
		REQUIRE(allConstructTabulated("eeeeee", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}) == std::vector<std::vector<std::string_view>>{
			{"eeeeee"}, 
			{"e", "eeeee"}, 
			{"ee", "eeee"}, 
			{"e", "e", "eeee"}, 
			{"eee", "eee"}, 
			{"e", "ee", "eee"}, 
			{"ee", "e", "eee"}, 
			{"e", "e", "e", "eee"}, 
			{"eeee", "ee"}, 
			{"e", "eee", "ee"}, 
			{"ee", "ee", "ee"}, 
			{"e", "e", "ee", "ee"}, 
			{"eee", "e", "ee"}, 
			{"e", "ee", "e", "ee"}, 
			{"ee", "e", "e", "ee"}, 
			{"e", "e", "e", "e", "ee"}, 
			{"eeeee", "e"}, 
			{"e", "eeee", "e"}, 
			{"ee", "eee", "e"}, 
			{"e", "e", "eee", "e"}, 
			{"eee", "ee", "e"}, 
			{"e", "ee", "ee", "e"}, 
			{"ee", "e", "ee", "e"}, 
			{"e", "e", "e", "ee", "e"}, 
			{"eeee", "e", "e"}, 
			{"e", "eee", "e", "e"}, 
			{"ee", "ee", "e", "e"}, 
			{"e", "e", "ee", "e", "e"}, 
			{"eee", "e", "e", "e"}, 
			{"e", "ee", "e", "e", "e"}, 
			{"ee", "e", "e", "e", "e"}, 
			{"e", "e", "e", "e", "e", "e"}
		});
	}
}