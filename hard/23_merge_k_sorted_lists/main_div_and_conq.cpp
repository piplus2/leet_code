/*
You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.
*/

#include <vector>

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
private:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        ListNode dummy(0);
        ListNode *curr = &dummy;

        while (l1 != nullptr && l2 != nullptr)
        {
            if (l1->val < l2->val)
            {
                curr->next = l1;
                l1 = l1->next;
            }
            else
            {
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;
        }
        if (l1 != nullptr)
        {
            curr->next = l1;
        }
        else
        {
            curr->next = l2;
        }

        return dummy.next;
    }

public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        int n = lists.size();

        if (n == 0)
            return nullptr;

        int round = 1;
        while (round < n)
        {
            for (size_t i = 0; i + round < n; i += round * 2)
            {
                lists[i] = mergeTwoLists(lists[i], lists[i + round]);
            }
            round *= 2;
        }

        return lists[0];
    }
};