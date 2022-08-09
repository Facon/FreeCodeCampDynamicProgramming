# FreeCodeCampDynamicProgramming
Dynamic programming exercises written in C++17 from FreeCodeCamp in YouTube: https://youtu.be/oBt53YbR9Kk.

This repository serves as a very good starting point to learn or remember about dynamic programming.

## Why C++?
It is my favourite language and I wanted to see the language differences in the implementation. The C++17 implementation is only a little harder to understand than the JavaScript one.

In any case, it is the small price that we pay for better performance.

## Algorithms' complexity
### Time complexity
| Program | Brute force | Memoization | Tabulation
| ----------- | ----------- | ----------- | ----------- |
| Fibonacci | O(2<sup>n</sup>) | O(n) | O(n) |
| GridTraveler | O(2<sup>(n+m)</sup>) | O(n*m) | O(n*m) |
| CanSum | O(n<sup>m</sup>)) | O(n*m) | O(n*m) |
| HowSum | O(n<sup>m</sup>*m) | O(n*m<sup>2</sup>) | O(n*m<sup>2</sup>) |
| BestSum | O(n<sup>m</sup>*m) | O(n*m<sup>2</sup>) | O(n*m<sup>2</sup>) |
| CanConstruct | O(n<sup>m</sup>*m) | O(n*m<sup>2</sup>) | O(n*m<sup>2</sup>) |
| CountConstruct | O(n<sup>m</sup>*m) | O(n*m<sup>2</sup>) | O(n*m<sup>2</sup>) |
| AllConstruct | O(n<sup>m</sup>) | O(n<sup>m</sup>) | O(n<sup>m</sup>) |

### Space complexity
| Program | Brute force | Memoization | Tabulation
| ----------- | ----------- | ----------- | ----------- |
| Fibonacci | O(n) | O(n) | O(n) |
| GridTraveler | O(n+m) | O(n*m) | O(n*m) |
| CanSum | O(m) | O(m) | O(m) |
| HowSum | O(m) | O(m<sup>2</sup>) | O(m<sup>2</sup>) |
| BestSum | O(m<sup>2</sup>) | O(m<sup>2</sup>) | O(m<sup>2</sup>) |
| CanConstruct | O(m<sup>2</sup>) | O(m<sup>2</sup>) | O(m) |
| CountConstruct | O(m<sup>2</sup>) | O(m<sup>2</sup>) | O(m) |
| AllConstruct | O(m) | O(n<sup>m</sup>) | O(n<sup>m</sup>) |

## Alvin's memoization recipe
1. Make it work
   - Visualize the problem as a tree
   - Implement the tree using recursion
   - Test it
2. Make it efficient
   - Add a memo object
   - Add a base case to return memo value
   - Store return values into the memo

## Alvin's tabulation recipe
- Visualize the problem as a table
- Size the table based on the inputs
- Initialize the table with default values
- Seed the trivial answer into the table
- Iterate through the table
- Fill further positions based on the current position

## Notes on exercises
### CanSum, HowSum and BestSum notes
* CanSum: "Can you do it? yes/no"
* HowSum: "How will you do it?"
* BestSum: "What is the optimize way to do it?"
----
* CanSum: Decision problem
* HowSum: Combinatoric problem
* BestSum: Optimization problem

### CanConstruct, CountConstruct and AllConstruct notes
* CanConstruct: "Can you do it? yes/no"
* CountConstruct: "In how many ways will you do it?"
* AllConstruct: "What are all the possible ways to do it?"
----
* CanSum: Decision problem
* HowSum: Combinatoric enumeration problem
* AllConstruct: Combinatoric construction problem

## Conclusion
- Notice any overlapping subproblems
- Decide what is the trivially smallest input
- Think recursively to use Memoization
- Think iteratively to use Tabulation
- Draw a strategy first!
