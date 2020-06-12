//
//  main.cpp
//  GenericTree
//
//  Created by Noor Mohd on 12/02/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Node {
public:
    int data=0;
    vector<Node*> childs;
    
    Node(int data) {
        this->data=data;
    }
};

Node* createTree(vector<int> &arr) {
    stack<Node*> st;
    Node* root=NULL;
    for (int i=0; i<arr.size(); i++) {
        if (arr[i]!=-1) {
            Node* node=new Node(arr[i]);
            if (i==0) {
                root=node;
            }
            st.push(node);
        } else {
            Node* node=st.top();
            st.pop();
            st.top()->childs.push_back(node);
        }
    }
    return root;
}

void display(Node* node) {
    cout<<node->data<<" =>";
    for (Node* n : node->childs) {
        cout<<n->data<<" ";
    }
    cout<<"\n";
    for (Node* n : node->childs) {
        display(n);
    }
}

int size(Node* node) {
    int s=0;
    for (Node* n : node->childs) {
        s+=size(n);
    }
    return s;
}

int height(Node* node) {
    int h=-1;
    for (Node* n : node->childs) {
        h=max(h, height(n));
    }
    return h+1;
}

bool isMirror(Node* node1,Node* node2) {
    if (node1->childs.size()!=node2->childs.size() || node1->data!=node2->data) {
        return false;
    }
    for (int i=0,j=(int)node2->childs.size(); i<=j; i++, j--) {
        bool res=isMirror(node1->childs[i], node2->childs[j]);
        if (!res) {
            return false;
        }
    }
    return true;
}

void linearize(Node* root) {
    if (root->childs.size()>0) {
        int size=(int)root->childs.size()-1;
        Node* node=root->childs[0];
        for (int i=1; i<root->childs.size(); i++) {
            node->childs.push_back(root->childs[i]);
        }
        while (size--) {
            root->childs.pop_back();
        }
        linearize(node);
    }
}

int main() {
    vector<int> arr= {10,20,50,-1,60,-1,-1,30,70,-1,80,100,-1,110,-1,-1,90,-1,-1,40,120,140,-1,150,-1,-1,-1};
    Node* root=createTree(arr);
    linearize(root);
    display(root);
    return 0;
}
