cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED YES)

project(DynamicProgramming)

if(MSVC)
	add_compile_options(/W4 /WX)
else()
	add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

find_package(doctest)

link_libraries(doctest::doctest)

enable_testing()

add_subdirectory(src/original)
add_subdirectory(src/memoization)
#add_subdirectory(src/tabulation)


