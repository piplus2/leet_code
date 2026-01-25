/*
You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.

Find the minimum y-coordinate value of a horizontal line such that the total area of the squares above the line equals the total area of the squares below the line.

Answers within 10-5 of the actual answer will be accepted.

Note: Squares may overlap. Overlapping areas should be counted multiple times.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;


struct Point {
    int y;
    int delta;
    bool operator<(const Point& other) const {
        return y < other.y;
    }
};


void radix_sort(vector<Point>& a) {
    int n = a.size();
    vector<Point> b(n);
    // Processiamo 8 bit alla volta (256 buckets) per un totale di 4 passaggi
    for (int shift = 0; shift < 32; shift += 8) {
        int count[256] = {0};
        
        for (int i = 0; i < n; i++) {
            // Mapping del segno: convertiamo l'int in un valore ordinabile come unsigned
            unsigned int u = (unsigned int)a[i].y ^ 0x80000000;
            count[(u >> shift) & 0xFF]++;
        }
        
        // Calcolo dei prefissi (Buckets)
        for (int i = 1; i < 256; i++) count[i] += count[i - 1];
        
        // Costruzione dell'array temporaneo (stabile, partendo dal fondo)
        for (int i = n - 1; i >= 0; i--) {
            unsigned int u = (unsigned int)a[i].y ^ 0x80000000;
            b[--count[(u >> shift) & 0xFF]] = a[i];
        }
        a = b;
    }
}

class Solution {
    // Use an ordered map to keep the squares data in the form
    // <y, area_slope>

    public:
        double separateSquares(vector<vector<int>>& squares) {
            ios_base::sync_with_stdio(false);
            cin.tie(NULL);

            vector<Point> points;
            points.reserve(squares.size() * 2);
            // square = [x_bottom_left, y_bottom_left, side_length]
            // since we sum the areas, we just ignore x
            for (auto sq : squares)
            {
                if (sq[2] == 0) continue;
                points.push_back({sq[1], sq[2]});
                points.push_back({sq[1] + sq[2], -sq[2]});
            }

            radix_sort(points);

            // calculate total area
            double total_area = 0;
            ll current_width = 0;
            int n = points.size();

            for (size_t i = 0; i < n - 1; ++i) {
                current_width += points[i].delta;
                total_area += (double)current_width * (points[i+1].y - points[i].y);
                // if (points[i+1].y > points[i].y) {
                //     // only update when we move to a new point
                //     total_area += current_width * (points[i+1].y - points[i].y);
                // }
            }

            double target = total_area * 0.5;
            double current_area = 0;
            current_width = 0;

            for (size_t i = 0; i < n - 1; ++i) {
                current_width += (double)points[i].delta;
                double next_area = current_area + (double)current_width * (points[i+1].y - points[i].y);
                if (next_area >= target - 1e-9) {
                    return (double)points[i].y + (target - current_area) / current_width;
                }
                // now update current_area
                current_area = next_area;
            }
            return (double)points.back().y;
        }
};
