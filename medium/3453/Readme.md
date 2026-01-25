# Separate Squares (Sum of Intervals)

[Link to the problem](https://leetcode.com/problems/separate-squares-i/description/?envType=daily-question&envId=2026-01-14)

## Problem Description
You are given a 2D integer array squares. Each squares[i] = [x_i, y_i, l_i] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.

Find the minimum y-coordinate value of a horizontal line such that the total area covered by squares above the line equals the total area covered by squares below the line.

Answers within $10^{-5}$ of the actual answer will be accepted.

**Note**: Squares may overlap. Overlapping areas should be counted *multiple times*.

## Technical Approach: Sweep-Line + Segment Tree
The areas of the overlapping squares must be summed, so it is a problem of numerical integration.

The solution implements a **Sweep-Line algorithm** and **Radix sort** for better performance.

### Key Components:
1. **Coordinate Compression**: As the x-coordinates can be large integers, they are mapped to a discrete set of indices to keep the Segment Tree efficient.
2. **Two-Pass Sweep-Line**:
   - **First Pass**: Calculates the total area of the union of all squares.
   - **Second Pass**: Finds the exact y-coordinate where the accumulated area reaches exactly half of the total area.
3. **Coordinate Sorting**: Implemented a 4-pass **Radix sort** that uses a bitwise XOR (`0x80000000`) to handle signed integers.

## Complexity Analysis
- **Time Complexity**: $O(N \log N)$, where $N$ is the number of squares. This is dominated by sorting the events.
- **Space Complexity**: $O(N)$ to store the squares and perform the sorting.

## Implementation Details
- Language: **C++14**
- Libraries: `std::vector`, `std::algorithm`
