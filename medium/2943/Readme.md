# Maximize Area of Square Hole in Grid

[Link to the problem](https://leetcode.com/problems/maximize-area-of-square-hole-in-grid/description/?envType=daily-question&envId=2026-01-15)

## Problem Description

You are given two integers `n` and `m` representing the internal horizontal and vertical bars of a grid, and two arrays `hBars` and `vBars` containing the indices of the bars that can be removed.

The goal is to find the maximum area of a **square-shaped** hole that can be created by removing some of the removable bars. Removing  consecutive bars creates a gap of length .

## Technical Approach: Sorting + Linear Scan

The problem is reduced to finding the longest sequence of consecutive integers in both `hBars` and `vBars`.

### Key Components:

1. **Consecutive Sequence Detection**: The algorithm identifies the maximum number of consecutive bars () available for removal in each dimension.
2. **Lazy Duplicate Handling**: Instead of always cleaning the input, the algorithm handles duplicates during the linear scan or uses a conditional `std::unique` to maximize performance.
3. **Early Exit Optimization**: If the number of bars provided matches the total number of internal bars ( or ), the algorithm skips the scan and immediately returns the maximum possible length.
4. **Square Constraint**: The final side of the square  is determined by the minimum of the two maximum gaps found: .

## Complexity Analysis

* **Time Complexity**: , where  and  are the lengths of `hBars` and `vBars`. The complexity is dominated by the sorting step. The subsequent scan is .
* **Space Complexity**:  (or  depending on the `std::sort` implementation), as the sorting is performed in-place on the input vectors.

## Implementation Details

* **Language**: C++14/17
* **Performance**: Beats 100% of C++ submissions 🚀.
* **Robustness**: Handles duplicate bar indices and empty inputs.
