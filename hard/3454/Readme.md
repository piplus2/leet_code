# Separate Squares (Union of Intervals)

[Liunk to the problem](https://leetcode.com/problems/separate-squares-ii/description/?envType=daily-question&envId=2026-01-14)

## Problem Description
You are given a 2D integer array squares. Each squares[i] = [x_i, y_i, l_i] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.

Find the minimum y-coordinate value of a horizontal line such that the total area covered by squares above the line equals the total area covered by squares below the line.

Answers within $10^{-5}$ of the actual answer will be accepted.

**Note**: Squares may overlap. Overlapping areas should be counted only once in this version.

## Technical Approach: Sweep-Line + Segment Tree
Since the squares can overlap, a simple summation of areas is not sufficient. I have considered the "Klee's measure problem" to calculate the union of the areas of the squares.

The solution implements a **Sweep-Line algorithm** integrated with a **Segment Tree** to achieve optimal time complexity.

### Key Components:
1. **Coordinate Compression**: As the x-coordinates can be large integers, they are mapped to a discrete set of indices to keep the Segment Tree efficient.
2. **Segment Tree**: Used to maintain the "union length" of active intervals along the x-axis. 
   - **Update Complexity**: $O(\log N)$
   - **Memory**: $O(N)$ using a contiguous vector for cache locality.
3. **Two-Pass Sweep-Line**:
   - **First Pass**: Calculates the total area of the union of all squares.
   - **Second Pass**: Finds the exact y-coordinate where the accumulated area reaches exactly half of the total area.

## Complexity Analysis
- **Time Complexity**: $O(N \log N)$, where $N$ is the number of squares. This is dominated by sorting the events and the $2N$ updates to the Segment Tree.
- **Space Complexity**: $O(N)$ to store the tree nodes and the compressed coordinates.

## Implementation Details
- Language: **C++14**
- Libraries: `std::vector`, `std::set`, `std::algorithm`
