/*
You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.
*/

#include <vector>
#include <queue>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        int n = lists.size();

        priority_queue<pair<int, ListNode *>, vector<pair<int, ListNode *>>, greater<pair<int, ListNode *>>> pq;

        ListNode dummy(0);
        ListNode *curr = &dummy;

        for (size_t i = 0; i < n; ++i)
        {
            if (lists[i] != nullptr)
                pq.push(make_pair(lists[i]->val, lists[i]));
        }

        while (!pq.empty())
        {
            pair<int, ListNode *> smallest = pq.top();
            pq.pop();
            curr->next = smallest.second;
            curr = smallest.second;
            if (smallest.second->next != nullptr)
            {
                smallest.second = smallest.second->next;
                smallest.first = smallest.second->val;
                pq.push(smallest);
            }
        }

        return dummy.next;
    }
};