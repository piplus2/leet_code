# Given the root of a binary search tree, return a balanced binary search tree with the same node values. If there is more than one answer, return any of them.

# A binary search tree is balanced if the depth of the two subtrees of every node never differs by more than 1.

from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def inOrder(self, node, res):
        if node is None:
            return
        
        self.inOrder(node.left, res)
        res.append(node)
        self.inOrder(node.right, res)

    def performBalance(self, list_nodes, left, right):
        if left > right:
            return None
        
        mid = (left + right) // 2
        root = list_nodes[mid]
        
        root.left = self.performBalance(list_nodes, left, mid - 1)
        root.right = self.performBalance(list_nodes, mid + 1, right)

        return root

    def balanceBST(self, root) -> Optional[TreeNode]:
        inorder_list = []
        self.inOrder(root, inorder_list)
        return self.performBalance(inorder_list, 0, len(inorder_list)-1)


def build_simple_tree(values):
    nodes = [TreeNode(v) for v in values if isinstance(v, int)]
    
    for i in range(len(nodes) - 1):
        nodes[i].right = nodes[i+1]
        
    return nodes[0] if nodes else None


def main():

    node_list = [1,"null",2,"null",3,"null",4,"null","null"]
    root = build_simple_tree(node_list)

    sol = Solution()
    root = sol.balanceBST(root)

    
        
