/*
Given an array nums, you can perform the following operation any number of times:

Select the adjacent pair with the minimum sum in nums. If multiple such pairs exist, choose the leftmost one.
Replace the pair with their sum.
Return the minimum number of operations needed to make the array non-decreasing.

An array is said to be non-decreasing if each element is greater than or equal to its previous element (if it exists).
*/

#include <vector>
#include <tuple>
#include <queue>

using namespace std;

struct Node
{
    long val;
    long index;
    Node *prev;
    Node *next;
    bool valid;
};

class Solution
{
public:
    int minimumPairRemoval(vector<int> &nums)
    {
        // priority queue (sum, index of L, L, R)
        priority_queue<tuple<long, long, Node *, Node *>,
                       vector<tuple<long, long, Node *, Node *>>,
                       greater<tuple<long, long, Node *, Node *>>>
            pq;

        vector<Node *> memory_pool;

        int n = nums.size();
        int violations = 0;
        Node *curr = new Node{nums[0], 0, nullptr, nullptr, true};
        memory_pool.push_back(curr);
        for (int i = 1; i < n; ++i)
        {
            if (nums[i] < nums[i - 1])
                violations++;

            Node *newNode = new Node{nums[i], i, curr, nullptr, true};
            memory_pool.push_back(newNode);
            curr->next = newNode;
            pq.push(make_tuple(nums[i - 1] + nums[i], i - 1, curr, newNode));
            curr = newNode;
        }

        int operations = 0;
        while (violations > 0 && !pq.empty())
        {
            auto [sum, idx, L, R] = pq.top();
            pq.pop();

            // check if valid
            if (!L->valid || !R->valid || L->next != R)
                continue;

            // lazy deletion
            L->valid = false;
            R->valid = false;

            // violations that we are removing
            if (L->val > R->val)
                violations--;
            if (L->prev != nullptr && L->prev->val > L->val)
                violations--;
            if (R->next != nullptr && R->val > R->next->val)
                violations--;

            Node *S = new Node{L->val + R->val, L->index, L->prev, R->next, true};
            memory_pool.push_back(S);
            operations++;

            // violations that we are introducing
            if (S->prev != nullptr && S->prev->val > S->val)
                violations++;
            if (S->prev != nullptr)
            {
                S->prev->next = S;
                pq.push({S->prev->val + S->val, S->prev->index, S->prev, S});
            }

            if (S->next != nullptr && S->val > S->next->val)
                violations++;
            if (S->next != nullptr)
            {
                S->next->prev = S;
                pq.push({S->val + S->next->val, S->index, S, S->next});
            }
        }

        for (Node *n : memory_pool)
            delete n;

        return operations;
    }
};

int main()
{
    vector<int> nums = {2, 2, -1, 3, -2, 2, 1, 1, 1, 0, -1};
    Solution sol;
    int nops = sol.minimumPairRemoval(nums);
}