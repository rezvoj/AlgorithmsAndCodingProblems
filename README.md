# Algorithms and Coding Problems

![License](https://img.shields.io/badge/license-MIT-blue.svg) ![Python Version](https://img.shields.io/badge/python-3.9-blue) ![C++ Version](https://img.shields.io/badge/C++-17-blue)


## Table of Contents
- [Introduction](#introduction)
- [List of Algorithms](#list-of-algorithms)
- [List of Coding Problems](#list-of-coding-problems)
- [License](#license)


## Introduction

This repository contains a collection of classic algorithms and coding problems implemented in C++ and Python, using their standard libraries. The collection predominantly features graph algorithms. The coding problems are mostly from Online Judge.


## List of Algorithms

### Dijkstra Shortest Path
An algorithm for finding the shortest paths between nodes in a graph, particularly useful for graphs with non-negative edge weights. The implementation uses a priority queue, and the time complexity is O((V + E) log V), where V is the number of vertices and E is the number of edges.

### Floyd-Warshall Shortest Path
A dynamic programming algorithm used to find the shortest paths between all pairs of nodes in a graph. The time complexity of Floyd-Warshall's algorithm is O(V^3).

### Huffman Coding
A greedy algorithm used for lossless data compression. It assigns variable-length codes to input characters based on their frequencies. The time complexity of Huffman Coding is O(n log n), where n is the number of characters.

### Kruskal MST
An algorithm for finding the Minimum Spanning Tree (MST) of a graph by sorting edges and adding them one by one, ensuring no cycles are formed. The time complexity of Kruskal's algorithm is O(E log E), where E is the number of edges.

### Matrix Chain Multiplication
A dynamic programming algorithm used to find the most efficient way to multiply a given sequence of matrices. The time complexity of this algorithm is O(n^3), where n is the number of matrices.


## List of Coding Problems

### Box Tower
Given n types of 3D boxes, each of which can be rotated and used multiple times, the goal is to stack them to create the tallest tower possible. The solution uses dynamic programming with a time complexity of O(n^2), where n is the number of possible box orientations.

### Check The Check
Given a chess board configuration, determine if a king is in check. A king is in check if it is on a square that can be attacked by an opponent’s piece on their next move. This is Online Judge problem 10196.

### Coins in Grid
Given a grid where each cell contains a certain number of coins, the goal is to find the path from the top-left to the bottom-right corner that maximizes the number of collected coins. You can only move right or down. This problem is solved using dynamic programming with a time complexity of O(n^2).

### Count The Ways
Given an amount of money in cents, determine the number of different combinations of US coins (penny, nickel, dime, quarter, half-dollar) that sum to that amount. The solution utilizes dynamic programming. This is Online Judge problem 357.

### Crypt Kicker
Given an encrypted text where each letter is consistently replaced by another letter, the task is to decrypt the text using a dictionary of known words. Each line of encrypted text may use a different set of replacements. If no solution exists, replace each letter with an asterisk. This is Online Judge problem 843.

### Expression Evaluation
Given a mathematical expression containing operators, numbers, and parentheses, the task is to evaluate the expression while respecting operator precedence and parentheses.

### Grand Dinner
Given the number of members in each team and the seating capacities of available tables, determine if it's possible to arrange seating such that no two members of the same team sit at the same table. If possible, provide a valid seating arrangement. The solution uses a greedy approach. This is Online Judge problem 10249.

### Graph Dependency
Given a directed graph, determine for each node the set of nodes it depends on. The solution uses depth-first search traversal to find all dependencies for every node.

### How Big
Given a set of circles, determine the smallest rectangular box that can fit all the circles, with all circles touching the bottom of the box. This is Online Judge problem 10012.

### Unlimited Knapsack
Given a set of items, each with a weight and value, determine the maximum value that can be obtained by filling a knapsack with unlimited copies of each item, without exceeding the knapsack's weight capacity. The solution uses dynamic programming.

### Meta-Loopless Sorts
Given a number n, generate a Pascal program that sorts n integers using only if-then-else statements and writeln statements. The program must follow strict formatting rules and avoid redundant comparisons. The solution utilizes recursion. This is Online Judge problem 110.

### Minesweeper
Determine the number of adjacent mines for each safe square in a given grid. This is Online Judge problem 10189.

### N-Queen Problem
Place N queens on an NxN chessboard such that no two queens threaten each other. The solution utilizes backtracking with early pruning to efficiently explore all possible placements and find all valid solutions.

### Paper Folding
Given a number N, generate the dragon curve that results from folding a sheet of paper N times and opening the folds to form a 90-degree angle. The output displays the curve. This is Online Judge problem 177.

### Parquet Patterns
Given an m x n grid, determine the number of ways to fill the grid completely using 1x2 planks. The solution utilizes dynamic programming with bitmasks. 

### Servicing Stations
Given a set of towns connected by direct routes, determine the minimum number of servicing stations needed such that every town has a station either in the town itself or in a neighboring town. The solution divides the implicit graph into parts and applies backtracking with multiple types of pruning. This is Online Judge problem 10160.


## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
