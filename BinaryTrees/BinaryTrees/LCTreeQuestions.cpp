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

// LC 222 - Count Complete Tree Nodes
int height(TreeNode* root) {
    return root==NULL ?-1:1+height(root->left);
}

int countCompleteTreeNodes(TreeNode* root) {
    int h=height(root);
    return h<0 ? 0 : height(root->right) == h-1 ? (1<<h) + countCompleteTreeNodes(root->right)
    : (1<<(h-1)) + countCompleteTreeNodes(root->left);
}

// LC 129 - Sum Root to Leaf Numbers
int sumNumbers(TreeNode* root, int sum) {
    if(!root) return 0;
    int currSum = (10*sum) + root->val;
    if(!root->left &&  !root->right) return currSum;
    return sumNumbers(root->left, currSum) + sumNumbers(root->right, currSum);
}

int sumNumbers(TreeNode* root) {
    if(!root) return 0;
    if(!root->left &&  !root->right) return root->val;
    return sumNumbers(root->left, root->val) + sumNumbers(root->right, root->val);
}

// LC 102 - Binary Tree Level Order Traversal
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> ans;
    if(!root) return ans;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        int size=(int) q.size();
        vector<int> levelOrder;
        while(size--) {
            TreeNode* node=q.front();
            q.pop();
            levelOrder.push_back(node->val);
            if(node->left!=NULL) q.push(node->left);
            if(node->right!=NULL) q.push(node->right);
        }
        if(levelOrder.size()!=0) ans.push_back(levelOrder);
    }
    return ans;
}

// LC 107 - Binary Tree Level Order Traversal II
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    vector<vector<int>> ans;
    if(!root) return ans;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        int size=(int) q.size();
        vector<int> levelOrder;
        while(size--) {
            TreeNode* node=q.front();
            q.pop();
            levelOrder.push_back(node->val);
            if(node->left!=NULL) q.push(node->left);
            if(node->right!=NULL) q.push(node->right);
        }
        if(levelOrder.size()!=0) ans.push_back(levelOrder);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

// LC 637 - Average of Levels in Binary Tree
vector<double> averageOfLevels(TreeNode* root) {
    vector<double> ans;
    if(!root) return ans;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        int size=(int) q.size();
        double levelSum=0;
        for(int i=0;i<size;i++) {
            TreeNode* node=q.front();
            q.pop();
            levelSum+=node->val;
            if(node->left!=NULL) q.push(node->left);
            if(node->right!=NULL) q.push(node->right);
        }
        ans.push_back(levelSum/size);
    }
    return ans;
}

// LC 654 - Maximum Binary Tree
int getMax(vector<int>& nums, int l, int r) {
    int idx=l;
    for(int i=l+1;i<=r;i++)
        if(nums[i]>nums[idx]) idx=i;
    return idx;
}

TreeNode* constructMaximumBinaryTree(vector<int>& nums, int l, int r) {
    if(l>r) return NULL;
    if(l==r) return new TreeNode(nums[l]);
    int max=getMax(nums, l, r);
    TreeNode* root=new TreeNode(nums[max]);
    root->left=constructMaximumBinaryTree(nums, l, max-1);
    root->right=constructMaximumBinaryTree(nums, max+1, r);
    return root;
}

TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    return constructMaximumBinaryTree(nums, 0, (int) nums.size()-1);
}

// LC 998 - Maximum Binary Tree II
TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
    if(root!=NULL && (root->val)>val) {
        root->right=insertIntoMaxTree(root->right, val);
        return root;
    }
    TreeNode* node=new TreeNode(val);
    node->left=root;
    return node;
}

// LC 285 - Inorder Successor in BST
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    if(root==NULL) return NULL;
    if(root->val<=p->val) return inorderSuccessor(root->right, p);
    TreeNode* successor=inorderSuccessor(root->left, p);
    return successor==NULL?root: successor;
}

// LC 510 - Inorder Successor in BST II
class Node{
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};

Node* inorderSuccessor(Node* root) {
    if(root==NULL) return NULL;
    Node* node;
    if (root->right!=NULL) {
        node=root->right;
        while (node->left!=NULL) node=node->left;
    } else {
        node=root->parent;
        while (node!=NULL && node->val<root->val) node=node->parent;
    }
    return node;
}
