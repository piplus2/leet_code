/*
You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.

Find the minimum y-coordinate value of a horizontal line such that the total area covered by squares above the line equals the total area covered by squares below the line.

Answers within 10-5 of the actual answer will be accepted.

Note: Squares may overlap. Overlapping areas should be counted only once in this version.
*/

#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
typedef long long ll;


struct Node {
    int count = 0;  // number of squares in interval
    ll length = 0;  // length of the union
};


class SegmentTree {
    private:
        vector<Node> tree;
        vector<int>& coords;
        int n;

        void update(int node, int start, int end, int L, int R, int val)
        {
            if (coords[start] >= L && coords[end] <= R) {
                // if the square falls in the interval, increase the count by val
                tree[node].count += val;
            } else {
                int mid = (start + end) / 2;
                if (L < coords[mid]) update(2 * node, start, mid, L, R, val);
                if (R > coords[mid]) update(2 * node + 1, mid, end, L, R, val);
            }

            if (tree[node].count > 0) {
                // we know that there's full squares inside the interval
                // take the union
                tree[node].length = coords[end] - coords[start];
            } else if (end - start > 1) {
                tree[node].length = tree[2 * node].length + tree[2 * node + 1].length;
            } else {
                tree[node].length = 0;
            }
        }
    public:
        SegmentTree(vector<int>& sorted_coords) : coords(sorted_coords) {
            n = coords.size() - 1;
            tree.resize(4 * n);
        }

        void add(int L, int R) {
            update(1, 0, n, L, R, 1);
        }

        void remove(int L, int R) {
            update(1, 0, n, L, R, -1);
        }

        ll get_union_length() {
            return tree[1].length;
        }

        void reset() {
            for (auto& node : tree) {
                node.count = 0;
                node.length = 0;
            }
        }
};


struct Event {
    int y;
    int x1, x2;
    int type;   // +1 if start a new square or -1 if ends

    // to sort the events
    bool operator<(const Event& other) const {
        return y < other.y;
    }
};


class Solution {
    // Use an ordered map to keep the squares data in the form
    // <y, area_slope>
    map<int, ll> slope_changes;

    public:
        double separateSquares(vector<vector<int>>& squares) {
            vector<Event> events;
            set<int> unique_x;
            // square = [x_bottom_left, y_bottom_left, side_length]
            for (auto sq : squares)
            {
                int x_bottom = sq[0];
                int y_bottom = sq[1];
                int side = sq[2];

                if (side == 0) {
                    // skip empty squares
                    continue;
                }

                unique_x.insert(x_bottom);
                unique_x.insert(x_bottom + side);

                events.push_back({y_bottom, x_bottom, x_bottom + side, 1});
                events.push_back({y_bottom + side, x_bottom, x_bottom + side, -1});
                
            }

            sort(events.begin(), events.end());

            // sort the x coords
            vector<int> x_coords(unique_x.begin(), unique_x.end());
            unique_x.clear();  // free mem

            SegmentTree st(x_coords);

            // calculate total area
            ll total_area = 0;
            for (int i = 0; i < events.size() - 1; ++i) {
                if (events[i].type == 1) st.add(events[i].x1, events[i].x2);
                else st.remove(events[i].x1, events[i].x2);

                total_area += (double)st.get_union_length() * (events[i+1].y - events[i].y);
            }

            double target = total_area / 2.0;
            double current_area = 0;
            st.reset();

            for (int i = 0; i < events.size() - 1; ++i) {
                if (events[i].type == 1) st.add(events[i].x1, events[i].x2);
                else st.remove(events[i].x1, events[i].x2);

                ll width = st.get_union_length();
                ll delta_y = events[i+1].y - events[i].y;
                double segment_area = (double)width * delta_y;

                if (current_area + segment_area >= target) {
                    return(double)events[i].y + (target - current_area) / width;
                }
                current_area += segment_area;
            }

            return -1;
        }
};


int main() {
    vector<vector<int>> coords = {{15,21,2},{19,21,3}};
    Solution sol;
    double y_med = sol.separateSquares(coords);

    cout.precision(10);

    cout << y_med << endl;

    return 0;
}