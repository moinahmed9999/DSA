//
//  LCTreeQuestions.cpp
//  BinaryTrees
//
//  Created by Noor Mohd on 18/06/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include <bits/stdc++.h>
using namespace std;


// Definition for a binary tree node.
class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// LC 617 - Merge Two Binary Trees
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
    if(t1==NULL) return t2;
    if(t2==NULL) return t1;
    TreeNode* root=new TreeNode();
    root->val=t1->val+t2->val;
    root->left=mergeTrees(t1->left, t2->left);
    root->right=mergeTrees(t1->right, t2->right);
    return root;
}

// LC 938 - Range Sum of BST
int rangeSumBST(TreeNode* root, int L, int R) {
    if(root==NULL) {
        return 0;
    }
    int sum=root->val>=L && root->val<=R?root->val : 0;
    sum+=rangeSumBST(root->left, L, R);
    sum+=rangeSumBST(root->right, L, R);
    return sum;
}

// LC 104 - Maximum Depth of Binary Tree
int maxDepth(TreeNode* root) {
    if(root==NULL) return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

// LC 111 - Minimum Depth of Binary Tree
int minDepth(TreeNode* root) {
    if(root==NULL) return 0;
    int left=minDepth(root->left);
    int right=minDepth(root->right);
    if(left==0) return right+1;
    if(right==0) return left+1;
    return min(left, right) + 1;
}

// LC 110 - Balanced Binary Tree
int isBalancedHeight(TreeNode* root) {
    if(!root) return 0;
    int left=isBalancedHeight(root->left);
    if(left==-1) return -1;
    int right=isBalancedHeight(root->right);
    if(right==-1) return -1;
    if(abs(left-right)>1) return -1;
    return max(left, right) + 1;
}

bool isBalanced(TreeNode* root) {
    return isBalancedHeight(root)!=-1;
}

// LC 530 - Minimum Absolute Difference in BST
void getMinimumDifferenceInorder(TreeNode* root, int& prev, int& minDiff) {
    if(!root) return;
    getMinimumDifferenceInorder(root->left, prev, minDiff);
    if(prev!=-1) minDiff=min(minDiff, abs(root->val-prev));
    prev=root->val;
    getMinimumDifferenceInorder(root->right, prev, minDiff);
}

int getMinimumDifference(TreeNode* root) {
    int minDiff=INT_MAX, prev=-1;
    getMinimumDifferenceInorder(root, prev, minDiff);
    return minDiff;
}

// LC 543 - Diameter of Binary Tree
int diameterOfBinaryTreeHeight(TreeNode* root, int& maxDiameter) {
    if(!root) return 0;
    int left=diameterOfBinaryTreeHeight(root->left, maxDiameter);
    int right=diameterOfBinaryTreeHeight(root->right, maxDiameter);
    maxDiameter=max(maxDiameter, left+right);
    return max(left, right) + 1;
}

int diameterOfBinaryTree(TreeNode* root) {
    if(!root) return 0;
    int maxDiameter=INT_MIN;
    diameterOfBinaryTreeHeight(root, maxDiameter);
    return maxDiameter;
}

// LC 872 - Leaf-Similar Trees
void leafSimilarDfs(TreeNode* node, vector<int>& leaves) {
    if (!node) return;
    if (!(node->left) && !(node->right))
        leaves.push_back(node->val);
    leafSimilarDfs(node->left, leaves);
    leafSimilarDfs(node->right, leaves);
}

bool leafSimilar(TreeNode* root1, TreeNode* root2) {
    vector<int> leaves1, leaves2;
    leafSimilarDfs(root1, leaves1);
    leafSimilarDfs(root2, leaves2);
    return leaves1==leaves2;
}

// LC 100 - Same Tree
bool isSameTree(TreeNode* p, TreeNode* q) {
    if(!p && !q) return true;
    if((p!=NULL && !q) || (!p && q!=NULL)) return false;
    if(p->val!=q->val) return false;
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}


// LC 101 - Symmetric Tree
bool isSymmetric(TreeNode* root1, TreeNode* root2) {
    if(!root1 && !root2) return true;
    if((root1!=NULL && !root2) || (!root1 && root2!=NULL)) return false;
    if(root1->val!=root2->val) return false;
    return isSymmetric(root1->left, root2->right) && isSymmetric(root1->right, root2->left);
}

bool isSymmetric(TreeNode* root) {
    if(!root) return true;
    return isSymmetric(root->left, root->right);
}

// LC 404 - Sum of Left Leaves
int sumOfLeftLeaves(TreeNode* root, bool isLeftChild) {
    if(!root) return 0;
    if(!root->left && !root->right && isLeftChild) return root->val;
    return sumOfLeftLeaves(root->left, true) + sumOfLeftLeaves(root->right, false);
}

int sumOfLeftLeaves(TreeNode* root) {
    if(!root) return 0;
    return sumOfLeftLeaves(root->left, true) + sumOfLeftLeaves(root->right, false);
}
