//
//  UnionType.cpp
//  Graph
//
//  Created by Noor Mohd on 23/02/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include <bits/stdc++.h>
using namespace std;

char findParentLSES(char ch, vector<char>& parent) {
    if (parent[ch-'a'] == ch) {
        return ch;
    }
    return parent[ch-'a']=findParentLSES(parent[ch-'a'], parent);
}

string lexicographicallySmallestEquivalentString(string A, string B,string S) {
    vector<char> parent;
    string ans="";
    
    for (int i=0; i<26; i++) {
        parent.push_back('a' + i);
    }
    
    for (int i=0; i<A.size(); i++) {
        char p1=findParentLSES(A[i], parent);
        char p2=findParentLSES(B[i], parent);
        if (p1 - p2 < 0) {    // A[i]'s parent is lexicographically small
            parent[p2 - 'a']=p1;
        } else {    // B[i]'s parent is lexicographically small
            parent[p1 - 'a']=p2;
        }
    }
    
    for (int i=0; i<S.size(); i++) {
        char ch=findParentLSES(S[i], parent);
        ans+=ch;
    }
    
    return ans;
}

int findParent(int u,vector<int>& parent) {
    if (parent[u]!=u) {
        return parent[u]=findParent(parent[u], parent);     //  Compression
    }
    return u;
}

void Union (int a,int b,vector<int>& parent,vector<int>& size) {
    int p=findParent(a, parent);
    int q=findParent(b, parent);
    
    if (size[p]<size[q]) {
        parent[p]=q;
        size[q]+=size[p];
    } else {
        parent[q]=p;
        size[p]+=size[q];
    }
}

int main()
{
//    string A="parker",B="morris",S="parser";
//    cout<<lexicographicallySmallestEquivalentString(A, B, S)<<"\n";
    
    return 0;
}
