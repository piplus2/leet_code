/*
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.
*/

#include <iostream>
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
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        if (!l1) return l2;
        if (!l2) return l1;

        int carry = 0;
        ListNode dummy(0);
        ListNode *head = l1;
        ListNode *prev = &dummy;  // preserve head of l1

        while (l1 != nullptr && l2 != nullptr)
        {
            int sum = l1->val + l2->val + carry;
            carry = sum / 10;
            sum = sum % 10;
            l1->val = sum;
            prev = l1;
            l1 = l1->next;
            l2 = l2->next;
        }

        if (l2 != nullptr) {
            prev->next = l2;
            l1 = l2;
        }

        while (l1 != nullptr && carry != 0)
        {
            int sum = l1->val + carry;
            carry = sum / 10;
            sum = sum % 10;
            l1->val = sum;
            prev = l1;
            l1 = l1->next;
            if (carry == 0) break;
        }

        if (carry != 0) {
            prev->next = new ListNode(carry);
        }
        
        return head;
    }
};

ListNode *append(ListNode *head, int data)
{
    ListNode *node = new ListNode;
    node->val = data;
    ListNode *last = head;
    while (last->next != nullptr)
    {
        last = last->next; // Traverse to end
    }
    last->next = node; // Append new node
    return head;
}

int main()
{
    ListNode *l1 = new ListNode(2);
    ListNode *l2 = new ListNode(5);

    l1 = append(l1, 4);
    l1 = append(l1, 3);

    l2 = append(l2, 6);
    l2 = append(l2, 4);

    Solution sol;
    ListNode *lsum = sol.addTwoNumbers(l1, l2);

    return 0;
}