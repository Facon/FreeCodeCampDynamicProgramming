cmake_minimum_required(VERSION 3.13)

add_executable(FibonacciTest)
add_executable(GridTravelerTest)
add_executable(CanSumTest)
add_executable(HowSumTest)
add_executable(BestSumTest)
add_executable(CanConstructTest)

target_sources(FibonacciTest
PRIVATE
	fibonacci.cpp)

target_sources(GridTravelerTest
PRIVATE
	gridTraveler.cpp)
	
target_sources(CanSumTest
PRIVATE
	canSum.cpp)
	
target_sources(HowSumTest
PRIVATE
	howSum.cpp)

target_sources(BestSumTest
PRIVATE
	bestSum.cpp)

target_sources(CanConstructTest
PRIVATE
	canConstruct.cpp)

add_test(NAME FibonacciTest COMMAND FibonacciTest)
add_test(NAME GridTravelerTest COMMAND GridTravelerTest)
add_test(NAME CanSumTest COMMAND CanSumTest)
add_test(NAME HowSumTest COMMAND HowSumTest)
add_test(NAME BestSumTest COMMAND BestSumTest)
add_test(NAME CanConstructTest COMMAND CanConstructTest)