cmake_minimum_required(VERSION 3.13)

add_executable(FibonacciTest)

target_sources(FibonacciTest
PRIVATE
	fibonacci.cpp)
	
add_executable(GridTravelerTest)

target_sources(GridTravelerTest
PRIVATE
	gridTraveler.cpp)
	
add_executable(CanSumTest)

target_sources(CanSumTest
PRIVATE
	canSum.cpp)
	
add_executable(HowSumTest)

target_sources(HowSumTest
PRIVATE
	howSum.cpp)

add_executable(BestSumTest)

target_sources(BestSumTest
PRIVATE
	bestSum.cpp)

add_test(NAME FibonacciTest COMMAND FibonacciTest)
add_test(NAME GridTravelerTest COMMAND GridTravelerTest)
add_test(NAME CanSumTest COMMAND CanSumTest)
add_test(NAME HowSumTest COMMAND HowSumTest)
add_test(NAME BestSumTest COMMAND BestSumTest)