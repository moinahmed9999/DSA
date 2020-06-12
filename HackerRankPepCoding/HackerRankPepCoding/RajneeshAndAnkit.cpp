//
//  RajneeshAndAnkit.cpp
//  HackerRankPepCoding
//
//  Created by Noor Mohd on 08/02/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
};

int addNode(Node* root,int a,int data) {
    if (root==NULL) {
        return -1;
    }
    if (root->data==a) {
        if (root->left==NULL) {
            Node* x=new Node;
            x->data=data;
            x->left=x->right=NULL;
            root->left=x;
            return 1;
        }else if (root->right==NULL) {
            Node* x=new Node;
            x->data=data;
            x->left=x->right=NULL;
            root->right=x;
            return 1;
        }
    }
    else {
        int ans=addNode(root->left, a, data);
        if (ans==-1) {
            ans=addNode(root->right, a, data);
            return ans;
        }
        else return 1;
    }
    return -1;
}

vector<int> rootToNodePath(Node* node, int data) {
    vector<int> arrayList;
    if (node == NULL) {
        return arrayList; }
    if (node->data == data) {
        arrayList.push_back(node->data);
        return arrayList;
    }
    vector<int> left = rootToNodePath(node->left, data);
    if (left.size()!=0) {
        left.push_back(node->data);
        return left;
    }
    vector<int> right = rootToNodePath(node->right, data);
    if (right.size()!=0) {
        right.push_back(node->data);
        return right;
    }
    return arrayList;
}

//bool findAway(Node* root, int des) {
//    if (root==NULL) {
//        return false;
//    }
//    if (root->data==des) {
//        return true;
//    }
//    bool res=false;
//    res=res|| findAway(root->left, des);
//    res=res|| findAway(root->right, des);
//    return res;
//}

int main() {
    int N;
    cin>>N;
    vector<vector<bool>> arena(N,vector<bool>(N,false));
    Node* root=new Node;
    root->data=1;
    root->left=root->right=NULL;
    for (int i=1; i<N; i++) {
        int x,y;
        cin>>x>>y;
        addNode(root, x, y);
    }
    int Q;
    cin>>Q;
    while (Q--) {
        int way;
        int X,Y;
        cin>>way>>X>>Y;
        vector<int> path;
        if (way==0) {
            path=rootToNodePath(root, Y);
            int flag=0;
            for (int i=0; i<path.size(); i++) {
                if (path[i]==X) {
                    flag++;
                    break;
                }
            }
            if (flag==0) {
                cout<<"NO\n";
            }
            else
                cout<<"YES\n";
        }
        else {
            path=rootToNodePath(root, X);
            int flag=0;
            for (int i=0; i<path.size(); i++) {
                if (path[i]==Y) {
                    flag++;
                    break;
                }
            }
            if (flag==0) {
                cout<<"NO\n";
            }
            else
                cout<<"YES\n";
        }
    }
    return 0;
}

