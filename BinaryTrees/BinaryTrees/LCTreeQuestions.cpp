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
    if(!root->left && !root->right) return currSum;
    return sumNumbers(root->left, currSum) + sumNumbers(root->right, currSum);
}

int sumNumbers(TreeNode* root) {
    return sumNumbers(root, 0);
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

// LC 105 - Construct Binary Tree from Preorder and Inorder Traversal
TreeNode* buildTree1(vector<int>& preorder, int l1, int r1, vector<int>& inorder, int l2, int r2, unordered_map<int, int>& map) {
    if(l1>r1) return NULL;
    TreeNode *root=new TreeNode(preorder[l1]);
    if(l1==r1) return root;
    int idx=map[preorder[l1]];
    int lSize=idx-l2;
    root->left=buildTree1(preorder, l1+1, l1+lSize, inorder, l2, idx-1, map);
    root->right=buildTree1(preorder, l1+lSize+1, r1, inorder, idx+1, r2, map);
    return root;
}

TreeNode* buildTree1(vector<int>& preorder, vector<int>& inorder) {
    int n=(int) preorder.size();
    unordered_map<int, int> map;
    for(int i=0;i<n;i++) map[inorder[i]]=i;
    return buildTree1(preorder, 0, n-1, inorder, 0, n-1, map);
}

// LC 106 - Construct Binary Tree from Inorder and Postorder Traversal
TreeNode* buildTree2(vector<int>& inorder, int l1, int r1, vector<int>& postorder, int l2, int r2, unordered_map<int, int>& map) {
    if(l2>r2) return NULL;
    TreeNode *root=new TreeNode(postorder[r2]);
    if(l2==r2) return root;
    int idx=map[postorder[r2]];
    int lSize=idx-l1;
    root->left=buildTree2(inorder, l1, idx-1, postorder, l2, l2+lSize-1, map);
    root->right=buildTree2(inorder, idx+1, r1, postorder, l2+lSize, r2-1, map);
    return root;
}

TreeNode* buildTree2(vector<int>& inorder, vector<int>& postorder) {
    int n=(int) postorder.size();
    unordered_map<int, int> map;
    for(int i=0;i<n;i++) map[inorder[i]]=i;
    return buildTree2(inorder, 0, n-1, postorder, 0, n-1, map);
    }

// LC 112 - Path Sum
bool hasPathSum(TreeNode* root, int sum) {
    if(root==NULL) return false;
    if(root->val==sum && root->left==NULL && root->right==NULL) return true;
    return hasPathSum(root->left, sum-root->val) || hasPathSum(root->right, sum-root->val);
}

// LC 113 - Path Sum II
void pathSumII(TreeNode* root, int sum, vector<int>& path, vector<vector<int>>& paths) {
    if(root==NULL) return;
    path.push_back(root->val);
    if(root->val==sum && root->left==NULL && root->right==NULL) {
        paths.push_back(path);
        path.pop_back();
        return;
    }
    pathSumII(root->left, sum-root->val, path, paths);
    pathSumII(root->right, sum-root->val, path, paths);
    path.pop_back();
}

vector<vector<int>> pathSumII(TreeNode* root, int sum) {
    vector<int> path;
    vector<vector<int>> paths;
    pathSumII(root, sum, path, paths);
    return paths;
    }

// LC 437 - Path Sum III
int pathSumIII(TreeNode* root, int sum, int currSum, unordered_map<int, int>& map) {
    if(root==NULL) return 0;
    currSum+=root->val;
    int count=map[currSum-sum];
    map[currSum]++;
    count+=pathSumIII(root->left, sum, currSum, map) + pathSumIII(root->right, sum, currSum, map);
    map[currSum]--;
    return count;
}

int pathSumIII(TreeNode* root, int sum) {
    unordered_map<int, int> map;
    map[0]=1;
    return pathSumIII(root, sum, 0, map);
}

// LC 124 - Binary Tree Maximum Path Sum
int maxPathSum(TreeNode* root, int& ans) {
    if(root==NULL) return 0;
    int lSum=maxPathSum(root->left, ans), rSum=maxPathSum(root->right, ans);
    int ret=max(root->val, root->val + max(lSum, rSum));
    ans=max(ans, max(ret, root->val+lSum+rSum));
    return ret;
}

int maxPathSum(TreeNode* root) {
    int ans=INT_MIN;
    maxPathSum(root, ans);
    return ans;
    }

// LC 666 - Path Sum IV
int pathSumIV(int root, int currSum, unordered_map<int, int>& map) {
    if(map.find(root)==map.end()) return 0;
    int depth=root/10, position=root%10;
    int leftNode=(depth+1)*10 + position*2 - 1, rightNode=leftNode + 1;
    currSum+=map[root];
    if(map.find(leftNode)==map.end() && map.find(rightNode)==map.end()) {
        return currSum;
    }
    return pathSumIV(leftNode, currSum, map) + pathSumIV(rightNode, currSum, map);
}

int pathSumIV(vector<int> &nums) {
    if(nums.size()==0) return 0;
    int first=INT_MAX;
    unordered_map<int, int> map;
    for(int num: nums) {
        first=min(first, num);
        map[num/10]=num%10;
    }
    return pathSumIV(first/10, 0, map);
}

// LC 988 - Smallest String Starting From Leaf
void smallestFromLeaf(TreeNode* root, string s, string& ans) {
    if(root==NULL) return;
    s=char(root->val + 'a') + s;
    if(root->left==NULL && root->right==NULL && s<ans)
        ans=s;
    smallestFromLeaf(root->left, s, ans);
    smallestFromLeaf(root->right, s, ans);
}

string smallestFromLeaf(TreeNode* root) {
    string ans="~";
    smallestFromLeaf(root, "", ans);
    return ans;
}

class NRNode /*Next Right Node*/ {
public:
    int val;
    NRNode* left;
    NRNode* right;
    NRNode* next;
    NRNode() : val(0), left(NULL), right(NULL), next(NULL) {}
    NRNode(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
    NRNode(int _val, NRNode* _left, NRNode* _right, NRNode* _next) :
    val(_val), left(_left), right(_right), next(_next) {}
};

// LC 116 - Populating Next Right Pointers in Each Node
NRNode* connect1(NRNode* root) /*better space complexity*/ {
    if(root==NULL || root->left==NULL || root->right==NULL) return root;
    root->left->next=root->right;
    if(root->next!=NULL) root->right->next=root->next->left;
    connect1(root->left);
    connect1(root->right);
    return root;
}

NRNode* connect2(NRNode* root) {
    if(root==NULL) return NULL;
    queue<NRNode*> q;
    q.push(root);
    while(!q.empty()) {
        int size=(int) q.size();
        while(size--) {
            NRNode *node=q.front(); q.pop();
            if(size) node->next=q.front();
            if(node->left!=NULL) q.push(node->left);
            if(node->right!=NULL) q.push(node->right);
        }
    }
    return root;
}

// LC 117 - Populating Next Right Pointers in Each Node II
NRNode* connect(NRNode* root) {
    if(root==NULL) return NULL;
    queue<NRNode*> q;
    q.push(root);
    while(!q.empty()) {
        int size=(int) q.size();
        while(size--) {
            NRNode *node=q.front(); q.pop();
            if(size) node->next=q.front();
            if(node->left!=NULL) q.push(node->left);
            if(node->right!=NULL) q.push(node->right);
        }
    }
    return root;
}

// LC 114 - Flatten Binary Tree to Linked List  (Preorder)
void flatten1(TreeNode* root) /*iterative - stack*/ {
    if(root==NULL) return;
    stack<TreeNode*> st;
    st.push(root);
    while(!st.empty()) {
        TreeNode *node=st.top(); st.pop();
        if(node->right!=NULL) st.push(node->right);
        if(node->left!=NULL) st.push(node->left);
        node->left=NULL;
        node->right=st.size()==0?NULL:st.top();
    }
}

void flatten2(TreeNode* root, TreeNode*& prev) /*recursive*/ {
    if(root==NULL) return;
    if(root->left!=NULL) {
        flatten2(root->left, prev);
        prev->right=root->right;
        root->right=root->left;
        root->left=NULL;
    }
    prev=root;
    flatten2(root->right, prev);
}

void flatten2(TreeNode* root) {
    TreeNode *prev=NULL;
    flatten2(root, prev);
}

// LC 199 - Binary Tree Right Side View
void rightSideView(TreeNode* root, int level, vector<int>& ans) {
    if(root==NULL) return;
    if(ans.size()==level) ans.push_back(root->val);
    rightSideView(root->right, level+1, ans);
    rightSideView(root->left, level+1, ans);
}

vector<int> rightSideView(TreeNode* root) {
    vector<int> ans;
    rightSideView(root, 0, ans);
    return ans;
}

// LC 235 - Lowest Common Ancestor of a Binary Search Tree
TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(p->val<root->val && q->val<root->val)
        return lowestCommonAncestorBST(root->left, p, q);
    if(p->val>root->val && q->val>root->val)
        return lowestCommonAncestorBST(root->right, p, q);
    return root;
}

// LC 236 - Lowest Common Ancestor of a Binary Tree
TreeNode* lowestCommonAncestorBT(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root==NULL || root==p || root==q) return root;
    TreeNode* left=lowestCommonAncestorBT(root->left, p, q);
    TreeNode* right=lowestCommonAncestorBT(root->right, p, q);
    if(left && right) return root;
    return left!=NULL?left:right;
}

// LC 257 - Binary Tree Paths
void binaryTreePaths(TreeNode* root, string s, vector<string>& ans) {
    if(root==NULL) return;
    s+="->" + to_string(root->val);
    if(root->left==NULL && root->right==NULL) ans.push_back(s);
    binaryTreePaths(root->left, s, ans);
    binaryTreePaths(root->right, s, ans);
}

vector<string> binaryTreePaths(TreeNode* root) {
    if(root==NULL) return {};
    vector<string> ans;
    string s=to_string(root->val);
    if(root->left==NULL && root->right==NULL) ans.push_back(s);
    binaryTreePaths(root->left, s, ans);
    binaryTreePaths(root->right, s, ans);
    return ans;
}

// LC 1110 - Delete Nodes And Return Forest
TreeNode* delNodes(TreeNode* root, unordered_set<int>& set, vector<TreeNode*>& ans) {
    if(root==NULL) return NULL;
    root->left=delNodes(root->left, set, ans);
    root->right=delNodes(root->right, set, ans);
    if(set.find(root->val)!=set.end()) {
        if(root->left!=NULL) ans.push_back(root->left);
        if(root->right!=NULL) ans.push_back(root->right);
        return NULL;
    }
    return root;
}

vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
    unordered_set<int> set;
    vector<TreeNode*> ans;
    for(int node: to_delete) set.insert(node);
    if(delNodes(root, set, ans)!=NULL) ans.push_back(root);
    return ans;
}

// LC 337 - House Robber III
vector<int> dfs(TreeNode* root) {   //0 means rob and 1 means not rob
    if(root==NULL) return {0,0};
    vector<int> left=dfs(root->left), right=dfs(root->right), ans(2);
    ans[0]=root->val + left[1] + right[1];
    ans[1]=max(left[0], left[1]) + max(right[0], right[1]);
    return ans;
}

int rob(TreeNode* root) {
    vector<int> ans=dfs(root);
    return max(ans[0], ans[1]);
    }

// LC 450 - Delete Node in a BST
TreeNode* deleteNode(TreeNode* root, int key) {
    if(root==NULL) return NULL;
    if(key<root->val) root->left=deleteNode(root->left, key);
    else if(key>root->val) root->right=deleteNode(root->right, key);
    else {
        if(root->left==NULL) return root->right;
        else if(root->right!=NULL) {
            TreeNode *node=root->right;
            while(node->left!=NULL) {
                node=node->left;
            }
            root->val=node->val;
            root->right=deleteNode(root->right, root->val);
            return root;
        } else return root->left;
    }
    return root;
}

// LC 501 - Find Mode in Binary Search Tree
void findMode(TreeNode* root, int& freq, int& maxFreq, int& prev, vector<int>& ans) /*inorder*/ {
    if(root==NULL) return;
    findMode(root->left, freq, maxFreq, prev, ans);
    
    freq=prev==root->val?freq+1:1;
    if(freq==maxFreq) ans.push_back(root->val);
    else if(freq>maxFreq) {
        maxFreq=freq;
        ans.clear();
        ans.push_back(root->val);
    }
    prev=root->val;
    
    findMode(root->right, freq, maxFreq, prev, ans);
}

vector<int> findMode(TreeNode* root) {
    int freq=0, maxFreq=0, prev=INT_MIN;
    vector<int> ans;
    findMode(root, freq, maxFreq, prev, ans);
    return ans;
}

// LC 538 - Convert BST to Greater Tree
void convertBST(TreeNode* root, int &prev) {
    if(root==NULL) return;
    convertBST(root->right, prev);
    root->val+=prev;
    prev=root->val;
    convertBST(root->left, prev);
}

TreeNode* convertBST(TreeNode* root) {
    int prev=0;
    convertBST(root, prev);
    return root;
    }

// LC 563 - Binary Tree Tilt
int findTilt(TreeNode* root, int& ans) {
    if(root==NULL) return 0;
    int left=findTilt(root->left, ans), right=findTilt(root->right, ans);
    ans+=abs(left-right);
    return left+root->val+right;
}

int findTilt(TreeNode* root) {
    int ans=0;
    findTilt(root, ans);
    return ans;
}

// LC 572 - Subtree of Another Tree
bool match(TreeNode* s, TreeNode* t) {
    if(s==NULL && t==NULL) return true;
    if(s==NULL || t==NULL || s->val!=t->val) return false;
    return match(s->left, t->left) && match(s->right, t->right);
}

bool isSubtree(TreeNode* s, TreeNode* t) {
    if(s==NULL) return false;
    if(s->val==t->val && match(s, t)) return true;
    return isSubtree(s->left, t) || isSubtree(s->right, t);
}

// LC 513 - Find Bottom Left Tree Value
int findBottomLeftValue(TreeNode* root) /*bfs from right to left*/ {
    queue<TreeNode*> q;
    q.push(root);
    TreeNode *curr=NULL;
    while(!q.empty()) {
        curr=q.front(); q.pop();
        if(curr->right!=NULL) q.push(curr->right);
        if(curr->left!=NULL) q.push(curr->left);
    }
    return curr->val;
}

// LC 515 - Find Largest Value in Each Tree Row
void largestValues(TreeNode* root, int level, vector<int>& ans) {
    if(root==NULL) return;
    ans[level]=max(ans[level], root->val);
    if((root->left!=NULL || root->right!=NULL) && (ans.size()<level+2))
        ans.push_back(INT_MIN);
    largestValues(root->left, level+1, ans);
    largestValues(root->right, level+1, ans);
}

vector<int> largestValues(TreeNode* root) {
    if(root==NULL) return {};
    vector<int> ans(1, INT_MIN);
    largestValues(root, 0, ans);
    return ans;
}

// LC 623 - Add One Row to Tree
TreeNode* addOneRow(TreeNode* root, int v, int d) {
    if(d==1) return new TreeNode(v, root, NULL);
    int depth=2;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        int size=(int) q.size();
        while(size--) {
            TreeNode *node=q.front(); q.pop();
            if(depth==d) {
                node->left=new TreeNode(v, node->left, NULL);
                node->right=new TreeNode(v, NULL, node->right);
            } else {
                if(node->left!=NULL) q.push(node->left);
                if(node->right!=NULL) q.push(node->right);
            }
        }
        depth++;
    }
    return root;
}

// LC 297 - Serialize and Deserialize Binary Tree
string serialize1(TreeNode* root) /*Encodes a tree to a single string*/ {
    string s="";
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        TreeNode *node=q.front(); q.pop();
        if(node==NULL) s+="#,";
        else {
            s+=to_string(node->val) + "," ;
            q.push(node->left);
            q.push(node->right);
        }
    }
    return s;
}

TreeNode* deserialize1(string data) /*Decodes your encoded data to tree*/ {
    if(data=="#,") return NULL;
    stringstream ss(data);
    string s;
    getline(ss,s,',');
    TreeNode *root=new TreeNode(stoi(s));
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        TreeNode *node=q.front(); q.pop();
        getline(ss,s,',');
        if(s!="#") {
            node->left=new TreeNode(stoi(s));
            q.push(node->left);
        }
        getline(ss,s,',');
        if(s!="#") {
            node->right=new TreeNode(stoi(s));
            q.push(node->right);
        }
    }
    return root;
}

string serialize2(TreeNode* root) {
    if(root==NULL) return "#";
    return to_string(root->val)+","+serialize2(root->left)+","+serialize2(root->right);
}

TreeNode* deserialize2(stringstream& ss) {
    string s;
    getline(ss,s,',');
    if(s=="#") return NULL;
    return new TreeNode(stoi(s), deserialize2(ss), deserialize2(ss));
}

TreeNode* deserialize2(string data) {
    stringstream ss(data);
    return deserialize2(ss);
}

// LC 652 - Find Duplicate Subtrees
string serializeTree(TreeNode* root, unordered_map<string, int>& map, vector<TreeNode*>& ans) {
    if(root==NULL) return "#";
    string s=to_string(root->val)+","+serializeTree(root->left, map, ans)+","+serializeTree(root->right, map, ans);
    map[s]++;
    if(map[s]==2) ans.push_back(root);
    return s;
}

vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    unordered_map<string, int> map;
    vector<TreeNode*> ans;
    serializeTree(root, map, ans);
    return ans;
}

// LC 968 - Binary Tree Cameras
int minCameraCover(TreeNode *root, int& ans) {
    // 0 - not covered, 1 - has camera, 2 - covered
    if(root==NULL) return 2;
    int left=minCameraCover(root->left, ans), right=minCameraCover(root->right, ans);
    if(left==0 || right==0) {
        ans++;
        return 1;
    }
    return left==1 || right==1?2: 0;
}

int minCameraCover(TreeNode* root) {
    int ans=0;
    int res=minCameraCover(root, ans);
    return ans+=res==0?1:0;
}

// LC 979 - Distribute Coins in Binary Tree
int distributeCoins(TreeNode* root, int& ans) {
    if(root==NULL) return 0;
    int left=distributeCoins(root->left, ans), right=distributeCoins(root->right, ans);
    ans+=abs(left) + abs(right);
    return root->val+left+right-1;
}

int distributeCoins(TreeNode* root) {
    int ans=0;
    distributeCoins(root, ans);
    return ans;
}
