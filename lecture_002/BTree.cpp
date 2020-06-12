//
//  BinaryTree.cpp
//  BinaryTrees
//
//  Created by Noor Mohd on 10/01/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include <bits/stdc++.h>
using namespace std;

int idx = 0;

class Node
{
public:
    int data;
    Node *left, *right;

    Node()
    {
        data = 0;
        left = NULL;
        right = NULL;
    }

    Node(int data, Node *left, Node *right)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

Node *create(vector<int> &arr)
{
    if (idx == arr.size() || arr[idx] == -1)
    {
        idx++;
        return NULL;
    }
    Node *newNode = new Node(arr[idx++], NULL, NULL);
    newNode->left = create(arr);
    newNode->right = create(arr);
    return newNode;
}

int height(Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return max(height(node->left), height(node->right)) + 1;
}

int size(Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return size(node->left) + size(node->right) + 1;
}

void display(Node *node)
{
    if (node == NULL)
    {
        return;
    }

    string str = "";
    str += node->left == NULL ? "." : to_string(node->left->data);
    str += " -> " + to_string(node->data) + " <- ";
    str += node->right == NULL ? "." : to_string(node->right->data);
    cout << str << "\n";

    display(node->left);
    display(node->right);
}

void displayPath(vector<Node *> path)
{
    vector<Node *>::iterator itr;
    for (itr = path.begin(); itr != path.end(); ++itr)
    {
        cout << (*itr)->data << " ";
    }
    cout << "\n";
}

// find method will give the shortest path from root when it backtracks
bool find(Node *node, int data)
{
    if (node == NULL)
    {
        return false;
    }
    if (node->data == data)
    {
        return true;
    }
    bool res = false;
    res = res || find(node->left, data);
    res = res || find(node->right, data);
    return res;
}

vector<Node *> rootToNodePAth(Node *node, int data)
{
    vector<Node *> ans;
    if (node == NULL)
    {
        return ans;
    }
    if (node->data == data)
    {
        ans.push_back(node);
        return ans;
    }
    vector<Node *> left = rootToNodePAth(node->left, data);
    if (left.size() != 0)
    {
        left.push_back(node);
        return left;
    }

    vector<Node *> right = rootToNodePAth(node->right, data);
    if (right.size() != 0)
    {
        right.push_back(node);
        return right;
    }

    return ans;
}

bool rootToNodePath(Node *node, int data, vector<Node *> &path)
{
    if (node == NULL)
    {
        return false;
    }
    if (node->data == data)
    {
        path.push_back(node);
        return true;
    }

    bool res = false;
    res = res || rootToNodePath(node->left, data, path);
    res = res || rootToNodePath(node->right, data, path);
    if (res)
    {
        path.push_back(node);
    }
    return res;
}

void LCA(Node *root, int data1, int data2)
{
    vector<Node *> list1 = rootToNodePAth(root, data1);
    vector<Node *> list2 = rootToNodePAth(root, data2);

    int prev = -1;
    for (int i = list1.size() - 1, j = list2.size() - 1; i >= 0 && j >= 0; i--, j--)
    {
        if (list1[i]->data != list2[j]->data)
        {
            break;
        }
        prev = list1[i]->data;
    }
    cout << prev << "\n";
}

int diameter(Node *node)
{
    if (node == NULL)
    {
        return 0;
    }

    int dl = diameter(node->left);
    int dr = diameter(node->right);

    int hl = height(node->left);
    int hr = height(node->right);

    return max(max(dl, dr), hl + hr + 1);
}

vector<int> diameter2(Node *node)
{
    if (node == NULL)
    {
        vector<int> a(2, 0);
        return a;
    }

    vector<int> left = diameter2(node->left);
    vector<int> right = diameter2(node->right);

    vector<int> myAns(2);
    myAns[0] = max(max(left[0], right[0]), left[1] + right[1] + 1); // Diameter
    myAns[1] = max(left[1], right[1]) + 1;                          // Height
    return myAns;
}

void levelOrder(Node *root)
{
    list<Node *> que;
    que.push_back(root);
    int level = 0;
    while (!que.empty())
    {
        cout << "Level " << level << " : ";
        int size = que.size();
        while (size-- > 0)
        {
            Node *node = que.front();
            que.pop_front();
            cout << node->data << " ";
            if (node->left)
            {
                que.push_back(node->left);
            }
            if (node->right)
            {
                que.push_back(node->right);
            }
        }
        cout << "\n";
        level++;
    }
}

void kawy(Node *node, int k, Node *rnode)
{
    if (node == NULL)
    {
        return;
    }
    if (node == rnode)
    {
        return;
    }
    if (k == 0)
    {
        cout << node->data << " ";
        return;
    }

    kawy(node->left, k - 1, rnode);
    kawy(node->right, k - 1, rnode);
}

void kfar_01(Node *node, int k, int data)
{
    vector<Node *> path = rootToNodePAth(node, data);

    Node *rnode = NULL;
    for (int i = 0; i < path.size(); i++)
    {
        kawy(path[i], k - i, rnode);
        rnode = path[i];
    }
}

int kfar_02(Node *node, int k, int data)
{
    if (node == NULL)
    {
        return -1;
    }
    if (node->data == data)
    {
        kawy(node, k, NULL);
        return 1;
    }

    int ld = kfar_02(node->left, k, data);
    if (ld != -1)
    {
        if (ld == k)
        {
            cout << node->data << " ";
        }
        else
        {
            kawy(node, k - ld, node->left);
        }
        return ld + 1;
    }

    int rd = kfar_02(node->right, k, data);
    if (rd != -1)
    {
        if (rd == k)
        {
            cout << node->data << " ";
        }
        else
        {
            kawy(node, k - rd, node->right);
        }
        return rd + 1;
    }

    return -1;
}

void k_away(Node *root, int data, int k)
{
    list<Node *> que;
    vector<Node *> vec = rootToNodePAth(root, data);
    Node *newRoot = vec[0];
    que.push_back(newRoot);
    int level = 0;
    while (!que.empty())
    {
        if (level > k)
        {
            break;
        }
        int size = que.size();
        while (size-- > 0)
        {
            Node *node = que.front();
            que.pop_front();
            if (level == k)
            {
                cout << node->data << " ";
            }
            if (node->left)
            {
                que.push_back(node->left);
            }
            if (node->right)
            {
                que.push_back(node->right);
            }
        }
        cout << "\n";
        level++;
    }
}

class allPair
{
public:
    int height, size;
    bool find;

    int ceil, floor;

    Node *pred, *succ, *prev;

    allPair()
    {
        height = size = 0;
        find = false;

        ceil = INT_MAX;
        floor = INT_MIN;

        pred = succ = prev = NULL;
    }
};

void allSoln(Node *node, int level, int data, allPair *sol)
{
    if (node == NULL)
    {
        return;
    }

    sol->size++;
    sol->height = max(sol->height, level);
    sol->find = sol->find || node->data == data;

    if (node->data > data && node->data < sol->ceil)
    {
        sol->ceil = node->data;
    }
    if (node->data < data && node->data > sol->floor)
    {
        sol->floor = node->data;
    }

    if (node->data == data && sol->pred == NULL)
    {
        sol->pred = sol->prev;
    }
    else
    {
        if (sol->prev && sol->prev->data == data)
        {
            sol->succ = node;
            return;
        }
    }

    sol->prev = node;

    allSoln(node->left, level + 1, data, sol);
    allSoln(node->right, level + 1, data, sol);
}

int prev = INT_MIN;

bool isBST(Node *node)
{
    if (node == NULL)
    {
        return true;
    }

    if (!isBST(node->left))
    {
        return false;
    }

    if (::prev > node->data)
    {
        return false;
    }
    ::prev = node->data;

    if (!isBST(node->right))
    {
        return false;
    }

    return true;
}


int main()
{
    int arr[] = {10, 20, 30, -1, -1, 40, -1, -1, 50, 60, 80, -1, -1, -1, 70, 90, -1, 100, -1, -1, -1};
    int n = sizeof(arr);
    vector<int> vec(arr, arr + n);
    Node *root = create(vec);

    //    display(root);
    //
    //    cout<<"Height of BinaryTree is : "<<height(root)<<"\n";
    //
    //    cout<<"Size of BinaryTree is : "<<size(root)<<"\n";
    //
    //    cout<<"Find 80 : "<<find(root,25)<<"\n";
    //
    //    cout<<"Shortest path from Root to Node\n";
    //    vector<Node*> ans;
    //
    //    rootToNodePath(root, 100, ans);
    //    displayPath(ans);
    //
    //    ans=rootToNodePAth(root, 90);
    //    displayPath(ans);
    //
    //    LCA(root, 100, 60);
    //
    //    cout<<"Diameter : "<<diameter(root)<<"\n";
    //
    //    vector<int> dia=diameter2(root);
    //    cout<<"Diameter : "<<dia[0]<<"\n";
    //    levelOrder(root);
    //    kfar_02(root, 2, 50);
    //    allPair pair;
    //    allPair *sol=&pair;
    //    allSoln(root, 0, 90, sol);
    //    if (sol->pred) {
    //        cout<<"Pred : "<<sol->pred->data;
    //    }
    //    if (sol->succ) {
    //        cout<<"\nSucc : "<<sol->succ->data<<"\n";
    //    }
    
    return 0;
}
