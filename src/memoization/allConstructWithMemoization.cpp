#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <unordered_map>
#include <deque>
#include <string_view>

/*
Time complexity: O(n^m) <-- Only a little better that brute force, but same complexity
Space complexity: O(n^m) <-- Actually way worse that brute force, we need to store all the possible combinations for all the subproblems
*/
std::vector<std::deque<std::string_view>> allConstructWithMemoization(std::string_view target, const std::vector<std::string_view>& values, std::unordered_map<std::string_view, std::vector<std::deque<std::string_view>>>& memoization)
{
	if (memoization.contains(target))
	{
		return memoization.at(target);
	}

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
		
		auto allChildCombinations = allConstructWithMemoization(suffix, values, memoization);
		
		for (auto& combination : allChildCombinations)
		{
			combination.push_front(value);
		}
		
		allCombinations.insert(allCombinations.end(), allChildCombinations.cbegin(), allChildCombinations.cend());
	}
	
	memoization.emplace(target, allCombinations);
	
	return allCombinations;
}

std::vector<std::deque<std::string_view>> allConstructWithMemoization(std::string_view target, const std::vector<std::string_view>& values)
{
	std::unordered_map<std::string_view, std::vector<std::deque<std::string_view>>> memoization;
	
	return allConstructWithMemoization(target, values, memoization);
}

namespace std // NOLINT(cert-dcl58-cpp)
{
template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& in)
{
    stream << "[";
    for (size_t i = 0; i < in.size(); ++i) {
        if (i != 0) { stream << ", "; }
        stream << in[i];
    }
    stream << "]";
    return stream;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::deque<T>& in)
{
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
	{ REQUIRE(allConstructWithMemoization("abcdef", {"ab", "abc", "cd", "def", "abcd"}) == std::vector<std::deque<std::string_view>>{{ "abc", "def" }}); }
	
	SUBCASE("Target: \"skateboard\", values available: [\"bo\", \"rd\", \"ate\", \"t\", \"ska\", \"sk\", \"boar\"]")
	{ REQUIRE(allConstructWithMemoization("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}) == std::vector<std::deque<std::string_view>>{}); }
	
	SUBCASE("Target: \"enterapotentpot\", values available: [\"a\", \"p\", \"ent\", \"enter\", \"ot\", \"o\", \"t\"]")
	{ 
		REQUIRE(allConstructWithMemoization("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}) == std::vector<std::deque<std::string_view>>{
		{ "enter", "a", "p", "ot", "ent", "p", "ot" }, 
		{ "enter", "a", "p", "ot", "ent", "p", "o", "t" }, 
		{ "enter", "a", "p", "o", "t", "ent", "p", "ot" }, 
		{ "enter", "a", "p", "o", "t", "ent", "p", "o", "t" } });
	}
	
	SUBCASE("Target: \"abcdefg\", values available: [\"a\", \"b\", \"c\", \"d\", \"abcd\", \"efg\"]")
	{ REQUIRE(allConstructWithMemoization("abcdefg", {"a", "b", "c", "d", "abcd", "efg"}) == std::vector<std::deque<std::string_view>>{{ "a", "b", "c", "d", "efg" }, { "abcd", "efg" }}); }
	
	SUBCASE("Target: \"purple\", values available: [\"purp\", \"p\", \"ur\", \"le\", \"purpl\"]")
	{ REQUIRE(allConstructWithMemoization("purple", {"purp", "p", "ur", "le", "purpl"}) == std::vector<std::deque<std::string_view>>{{ "purp", "le" }, { "p", "ur", "p", "le" }}); }
	
	SUBCASE("Target: \"eeeeeeeeeeeeeeeeeeeef\", values available: [\"e\", \"ee\", \"eee\", \"eeee\", \"eeeee\", \"eeeeee\"]")
	{ REQUIRE(allConstructWithMemoization("eeeeeeeeeeeeeeeeeeeef", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}) == std::vector<std::deque<std::string_view>>{}); };
	
	SUBCASE("Target: \"eeeeee\", values available: [\"e\", \"ee\", \"eee\", \"eeee\", \"eeeee\", \"eeeeee\"]")
	{
		REQUIRE(allConstructWithMemoization("eeeeee", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}) == std::vector<std::deque<std::string_view>>{
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