#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <deque>
#include <string_view>

/*
Time complexity: O(n^m)
Space complexity: O(m)
*/
std::vector<std::deque<std::string_view>> allConstruct(std::string_view target, const std::vector<std::string_view>& values)
{
	if (target.empty())
	{
		return {{}};
	}
	
	std::vector<std::deque<std::string_view>> allCombinations;
	
	for (auto& value: values)
	{
		auto positions = std::mismatch(target.cbegin(), target.cend(), value.cbegin(), value.cend());
		
		if (std::get<0>(positions) == target.cbegin() || std::get<1>(positions) != value.cend())
		{
			continue;
		}
		
		std::string_view suffix(std::get<0>(positions), target.cend());
		
		auto allChildCombinations = allConstruct(suffix, values);
		
		for (auto& combination : allChildCombinations)
		{
			combination.push_front(value);
		}
		
		allCombinations.insert(allCombinations.end(), allChildCombinations.cbegin(), allChildCombinations.cend());
	}
	
	return allCombinations;
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

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::deque<T>& in) {
    stream << "[";
    for (size_t i = 0; i < in.size(); ++i) {
        if (i != 0) { stream << ", "; }
        stream << in[i];
    }
    stream << "]";
    return stream;
}
}

TEST_CASE("All construct")
{
	SUBCASE("Target: \"abcdef\", values available: [\"ab\", \"abc\", \"cd\", \"def\", \"abcd\"]")
	{ REQUIRE(allConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd"}) == std::vector<std::deque<std::string_view>>{{ "abc", "def" }}); }
	
	SUBCASE("Target: \"skateboard\", values available: [\"bo\", \"rd\", \"ate\", \"t\", \"ska\", \"sk\", \"boar\"]")
	{ REQUIRE(allConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}) == std::vector<std::deque<std::string_view>>{}); }
	
	SUBCASE("Target: \"enterapotentpot\", values available: [\"a\", \"p\", \"ent\", \"enter\", \"ot\", \"o\", \"t\"]")
	{ 
		REQUIRE(allConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}) == std::vector<std::deque<std::string_view>>{
		{ "enter", "a", "p", "ot", "ent", "p", "ot" }, 
		{ "enter", "a", "p", "ot", "ent", "p", "o", "t" }, 
		{ "enter", "a", "p", "o", "t", "ent", "p", "ot" }, 
		{ "enter", "a", "p", "o", "t", "ent", "p", "o", "t" } });
	}
	
	SUBCASE("Target: \"abcdefg\", values available: [\"a\", \"b\", \"c\", \"d\", \"abcd\", \"efg\"]")
	{ REQUIRE(allConstruct("abcdefg", {"a", "b", "c", "d", "abcd", "efg"}) == std::vector<std::deque<std::string_view>>{{ "a", "b", "c", "d", "efg" }, { "abcd", "efg" }}); }
	
	SUBCASE("Target: \"purple\", values available: [\"purp\", \"p\", \"ur\", \"le\", \"purpl\"]")
	{ REQUIRE(allConstruct("purple", {"purp", "p", "ur", "le", "purpl"}) == std::vector<std::deque<std::string_view>>{{ "purp", "le" }, { "p", "ur", "p", "le" }}); }
	
	SUBCASE("Target: \"eeeeeeeeeeeeeeeeeeeef\", values available: [\"e\", \"ee\", \"eee\", \"eeee\", \"eeeee\", \"eeeeee\"]")
	{ REQUIRE(allConstruct("eeeeeeeeeeeeeeeeeeeef", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}) == std::vector<std::deque<std::string_view>>{}); };
	
	SUBCASE("Target: \"eeeeee\", values available: [\"e\", \"ee\", \"eee\", \"eeee\", \"eeeee\", \"eeeeee\"]")
	{
		REQUIRE(allConstruct("eeeeee", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}) == std::vector<std::deque<std::string_view>>{
			{"e", "e", "e", "e", "e", "e"}, 
			{"e", "e", "e", "e", "ee"}, 
			{"e", "e", "e", "ee", "e"}, 
			{"e", "e", "e", "eee"}, 
			{"e", "e", "ee", "e", "e"}, 
			{"e", "e", "ee", "ee"}, 
			{"e", "e", "eee", "e"}, 
			{"e", "e", "eeee"}, 
			{"e", "ee", "e", "e", "e"}, 
			{"e", "ee", "e", "ee"}, 
			{"e", "ee", "ee", "e"}, 
			{"e", "ee", "eee"}, 
			{"e", "eee", "e", "e"}, 
			{"e", "eee", "ee"}, 
			{"e", "eeee", "e"}, 
			{"e", "eeeee"}, 
			{"ee", "e", "e", "e", "e"}, 
			{"ee", "e", "e", "ee"}, 
			{"ee", "e", "ee", "e"}, 
			{"ee", "e", "eee"}, 
			{"ee", "ee", "e", "e"}, 
			{"ee", "ee", "ee"}, 
			{"ee", "eee", "e"}, 
			{"ee", "eeee"}, 
			{"eee", "e", "e", "e"}, 
			{"eee", "e", "ee"}, 
			{"eee", "ee", "e"}, 
			{"eee", "eee"}, 
			{"eeee", "e", "e"}, 
			{"eeee", "ee"}, 
			{"eeeee", "e"}, 
			{"eeeeee"}
		});
	}
}