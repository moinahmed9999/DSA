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

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(NULL) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
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

// LC 94 - Binary Tree Inorder Traversal
void inorderTraversal1(TreeNode* root, vector<int>& ans) /*recursive*/ {
    if(root==NULL) return;
    inorderTraversal1(root->left, ans);
    ans.push_back(root->val);
    inorderTraversal1(root->right, ans);
}

vector<int> inorderTraversal1(TreeNode* root) {
    vector<int> ans;
    inorderTraversal1(root, ans);
    return ans;
}

vector<int> inorderTraversal2(TreeNode* root) /*iterative*/ {
    if(root==NULL) return {};
    vector<int> ans;
    stack<TreeNode*> st;
    while(root!=NULL || !st.empty()) {
        while(root!=NULL) {
            st.push(root);
            root=root->left;
        }
        root=st.top(); st.pop();
        ans.push_back(root->val);
        root=root->right;
    }
    return ans;
}

// LC 96 - Unique Binary Search Trees
int uniqueBST(int n) {
    vector<int> dp(n+1, 0);
    dp[0]=dp[1]=1;
    for(int i=2;i<=n;i++) {         // n=i
        for(int j=1;j<=i;j++) {     // select jth no as root
            dp[i]+=dp[j-1]*dp[i-j];
        }
    }
    return dp[n];
}

// LC 95 - Unique Binary Search Trees II
vector<TreeNode*> generateTrees1(int n) /*faster*/ {
    if(n==0) return {};
    vector<vector<vector<TreeNode*>>> dp(n+1, vector<vector<TreeNode*>>(n+1));
    for(int gap=0;gap<=n;gap++) {
        for(int i=0, j=gap;j<=n;i++, j++) {
            if(gap==0) {
                dp[i][j].push_back(NULL);
                continue;
            } else if(gap==1) {
                dp[i][j].push_back(new TreeNode(i+1));
                continue;
            }
            for(int k=i+1;k<=j;k++) {
                for(TreeNode* left: dp[i][k-1]) {
                    for(TreeNode* right: dp[k][j]) {
                        TreeNode *root=new TreeNode(k);
                        root->left=left;
                        root->right=right;
                        dp[i][j].push_back(root);
                    }
                }
            }
        }
    }
    return dp[0][n];
}

vector<TreeNode*> dfs(int s, int e) {
    if(s>e) return {nullptr};
    if(s==e) return {new TreeNode(s)};
    vector<TreeNode*> res, left, right;
    for (int i=s;i<=e;i++) {
        left=dfs(s, i-1);
        right=dfs(i+1, e);
        for (auto l: left) {
            for (auto r: right) {
                TreeNode* root = new TreeNode(i);
                root->left=l;
                root->right=r;
                res.push_back(root);
            }
        }
    }
    return res;
}

vector<TreeNode*> generateTrees2(int n) /*slower*/ {
    if(n==0) return {};
    return dfs(1, n);
}

// LC 98 - Validate Binary Search Tree
bool isValidBST1(TreeNode* root, TreeNode* min, TreeNode* max) {
    if(root==NULL) return true;
    if((min!=NULL && root->val<=min->val) ||
       (max!=NULL && root->val>=max->val)) return false;
    return isValidBST1(root->left, min, root)
    && isValidBST1(root->right, root, max);
}

bool isValidBST1(TreeNode* root) {
    return isValidBST1(root, NULL,  NULL);
}

bool isValidBST2(TreeNode* node, TreeNode* &prev) {
    if (node==NULL) return true;
    if (!isValidBST2(node->left, prev)) return false;
    if (prev!=NULL && prev->val>=node->val) return false;
    prev=node;
    return isValidBST2(node->right, prev);
}

bool isValidBST2(TreeNode* root) {
    TreeNode* prev=NULL;
    return isValidBST2(root, prev);
}

// LC 99 - Recover Binary Search Tree
void recoverTree(TreeNode* root, TreeNode* &prev, TreeNode* &n1, TreeNode* &n2) {
    if(root==NULL) return;
    recoverTree(root->left, prev, n1, n2);
    if(prev!=NULL && n1==NULL && prev->val>=root->val) n1=prev;
    if(prev!=NULL && n1!=NULL && prev->val>=root->val) n2=root;
    prev=root;
    recoverTree(root->right, prev, n1, n2);
}

void recoverTree(TreeNode* root) {
    TreeNode *prev=NULL, *n1=NULL, *n2=NULL;
    recoverTree(root, prev, n1, n2);
    swap(n1->val, n2->val);
}

// LC 662 - Maximum Width of Binary Tree
int widthOfBinaryTree(TreeNode* root) {
    if(root==NULL) return 0;
    queue<pair<TreeNode*, int>> q;
    q.push({root, 1});
    int ans=0;
    while(!q.empty()) {
        int size=(int) q.size(), l=INT_MAX, r=INT_MIN, flag=0;
        if(size==1) q.front().second=1; // important to prevent overflow
        for(;size>0;size--, flag++) {
            TreeNode *node=q.front().first;
            int idx=q.front().second;
            q.pop();
            l=min(l, idx);
            r=max(r, idx);
            if(node->left!=NULL) q.push({node->left,idx*2});
            if(node->right!=NULL) q.push({node->right,idx+idx+1});
        }
        if(flag>0) ans=max(ans, r-l+1);
    }
    return ans;
}

// LC 108 - Convert Sorted Array to Binary Search Tree
TreeNode* sortedArrayToBST(vector<int>& nums, int l, int r) {
    if(l>r) return NULL;
    int m=(l+r)/2;
    TreeNode *root=new TreeNode(nums[m]);
    root->left=sortedArrayToBST(nums, l, m-1);
    root->right=sortedArrayToBST(nums, m+1, r);
    return root;
}

TreeNode* sortedArrayToBST1(vector<int>& nums) /*recursion method*/ {
    return sortedArrayToBST(nums, 0, (int) nums.size()-1);
}

// LC 109 - Convert Sorted List to Binary Search Tree
TreeNode* sortedListToBST1(ListNode* head) {
    if(head==NULL) return NULL;
    ListNode *slow=head, *fast=head, *prev=NULL;
    while (fast->next!=NULL && fast->next->next!=NULL) {
        prev=slow;
        slow=slow->next;
        fast=fast->next->next;
    }
    if(prev!=NULL) prev->next=NULL;
    TreeNode* root=new TreeNode(slow->val);
    if(slow!=head) root->left=sortedListToBST1(head);
    root->right=sortedListToBST1(slow->next);
    return root;
}

TreeNode* sortedListToBST2(ListNode* &head, int l, int r) /*inorder method*/ {
    if(l>r) return NULL;
    int m=(l+r)/2;
    TreeNode *left=sortedListToBST2(head, l, m-1);
    TreeNode *root=new TreeNode(head->val, left, NULL);
    head=head->next;    // to maintain inorder traversal - VVIMP
    root->right=sortedListToBST2(head, m+1, r);
    return root;
}

TreeNode* sortedListToBST2(ListNode* head) {
    int size=0;
    for(ListNode *node=head;node!=NULL;node=node->next)
        size++;
    return sortedListToBST2(head, 0, size-1);
    }

// LC 144 - Binary Tree Preorder Traversal

void preorderTraversal1(TreeNode* root, vector<int>& ans) /*recursive*/ {
    if(root==NULL) return;
    ans.push_back(root->val);
    preorderTraversal1(root->left, ans);
    preorderTraversal1(root->right, ans);
}

vector<int> preorderTraversal1(TreeNode* root) {
    vector<int> ans;
    preorderTraversal1(root, ans);
    return ans;
}

vector<int> preorderTraversal2(TreeNode* root) /*iterative*/ {
    if(root==NULL) return {};
    vector<int> ans;
    stack<TreeNode*> st;
    st.push(root);
    while(!st.empty()) {
        TreeNode *node=st.top(); st.pop();
        ans.push_back(node->val);
        if(node->right!=NULL) st.push(node->right);
        if(node->left!=NULL) st.push(node->left);
    }
    return ans;
}

// LC 145 - Binary Tree Postorder Traversal
void postorderTraversal1(TreeNode* root, vector<int>& ans) /*recursive*/ {
    if(root==NULL) return;
    postorderTraversal1(root->left, ans);
    postorderTraversal1(root->right, ans);
    ans.push_back(root->val);
}

vector<int> postorderTraversal1(TreeNode* root) {
    vector<int> ans;
    postorderTraversal1(root, ans);
    return ans;
}

vector<int> postorderTraversal2(TreeNode* root) /*iterative*/ {
    if(root==NULL) return {};
    vector<int> ans;
    stack<TreeNode*> st;
    st.push(root);
    while(!st.empty()) {
        TreeNode *node=st.top(); st.pop();
        ans.insert(ans.begin(), node->val);
        if(node->left!=NULL) st.push(node->left);
        if(node->right!=NULL) st.push(node->right);
    }
    return ans;
    }

// LC 863 - All Nodes Distance K in Binary Tree
void distanceKDown(TreeNode* root, int K, vector<int>& ans) {
    if(root==NULL) return;
    if(K==0) {
        ans.push_back(root->val);
        return;
    }
    distanceKDown(root->left, K-1, ans);
    distanceKDown(root->right, K-1, ans);
}

int distanceK(TreeNode* root, TreeNode* target, int K, vector<int>& ans) {
    if(root==NULL) return -1;
    if(root==target) {
        distanceKDown(root, K, ans);
        return K-1;
    }
    int left=distanceK(root->left, target, K, ans);
    if(left==0) {
        ans.push_back(root->val);
        return -1;
    } else if(left>0) {
        distanceKDown(root->right, left-1, ans);
        return left-1;
    }
    int right=distanceK(root->right, target, K, ans);
    if(right==0) {
        ans.push_back(root->val);
        return -1;
    } else if(right>0) {
        distanceKDown(root->left, right-1, ans);
        return right-1;
    }
    return -1;
}

vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
    vector<int> ans;
    distanceK(root, target, K, ans);
    return ans;
}

// LC 687 - Longest Univalue Path
int countUnivalePath(TreeNode* root, TreeNode* target) {
    if(root==NULL || root->val!=target->val) return 0;
    int left=countUnivalePath(root->left, target);
    int right=countUnivalePath(root->right, target);
    return max(left, right) + 1;
}

void longestUnivaluePath(TreeNode* root, int& ans) {
    if(root==NULL) return;
    int count=countUnivalePath(root->left, root) + countUnivalePath(root->right, root);
    ans=max(ans, count);
    longestUnivaluePath(root->left, ans);
    longestUnivaluePath(root->right, ans);
}

int longestUnivaluePath(TreeNode* root) {
    int ans=0;
    longestUnivaluePath(root, ans);
    return ans;
}

// LC 103 - Binary Tree Zigzag Level Order Traversal
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> ans;
    if(root==NULL) return ans;
    queue<TreeNode*> q;
    q.push(root);
    int zigzag=1;
    while(!q.empty()) {
        int size=(int) q.size(), idx;
        vector<int> levelOrder(size);
        if(zigzag==1) idx=0;
        else idx=size-1;
        while(size--) {
            TreeNode *node=q.front(); q.pop();
            levelOrder[idx]=node->val;
            idx+=zigzag;
            if(node->left!=NULL) q.push(node->left);
            if(node->right!=NULL) q.push(node->right);
        }
        ans.push_back(levelOrder);
        zigzag*=-1;
    }
    return ans;
}

