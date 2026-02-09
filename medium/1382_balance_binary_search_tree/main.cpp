/*
Given the root of a binary search tree, return a balanced binary search tree with the same node values. If there is more than one answer, return any of them.

A binary search tree is balanced if the depth of the two subtrees of every node never differs by more than 1.
*/

#include <vector>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
private:
    void inOrder(TreeNode *node, vector<TreeNode *> &listNodes)
    {
        if (node == nullptr)
        {
            return;
        }

        inOrder(node->left, listNodes);
        node->left = nullptr;
        listNodes.push_back(node);
        inOrder(node->right, listNodes);
        node->right = nullptr;
    }

    TreeNode *doBalance(vector<TreeNode *> &listNodes, size_t left, size_t right)
    {
        if (left > right)
            return nullptr;

        size_t mid = (size_t)((left + right) / 2);
        TreeNode *root = listNodes[mid];

        root->left = doBalance(listNodes, left, mid - 1);
        root->right = doBalance(listNodes, mid + 1, right);

        return root;
    }

public:
    TreeNode *balanceBST(TreeNode *root)
    {
        vector<TreeNode *> inOrderList;
        inOrder(root, inOrderList);
        return doBalance(inOrderList, 0, inOrderList.size() - 1);
    }
};