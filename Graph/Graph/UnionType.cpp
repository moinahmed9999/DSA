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

// LC 685 - Redundant Connection II
vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
    // If there is no loop, then either one vertex must have two parents (or no edge is redundant.) If there is a loop, then either one vertex has two parents, or every vertex has one parent(root is child of one of the nodes).
    int n=(int) edges.size();
    vector<int> parent(n+1), ans1, ans2;
    vector<int> size(n+1,1);
    
    // find edge containing vertex with two parents
    for(int i=0;i<n;i++) {
        if(parent[edges[i][1]]==0)
            parent[edges[i][1]]=edges[i][0];
        else {
            ans1={parent[edges[i][1]], edges[i][1]};
            ans2=edges[i];
            edges[i][1]=0;  // mark that it has two parents
        }
    }
    
    // reset parents
    for(int i=1;i<=n;i++) parent[i]=i;
    
    // check for
    for(int i=0;i<n;i++) {
        if(edges[i][1]==0) continue;    // want last of the multiple answers
        int u=edges[i][0], v=edges[i][1];
        int pu=findParent(u, parent);
        if(pu==v) {             // conflict
            if(ans1.empty())    // loop root->1->2->4->1
                return edges[i]; // root is child of one of the nodes
            return ans1;        // ans1 is the additional node
        }
        parent[v]=pu;
    }
    return ans2; // w/o ans2 the tree is valid means ans2 is additional node
}

// LC 721 - Accounts Merge
int find(vector<int>& parent, int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent, parent[i]);
}

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    vector<int> parent(accounts.size(), 0);
    unordered_map<string, int> email_id;
    
    // We gather all the e-mails and the group in whick thet belong
    // We make groups for the case that one e-mail has multiple accounts
    for (int i = 0; i < accounts.size(); i++) {
        // Initialize the parent vector
        parent[i] = i;
        for (int j = 1; j < accounts[i].size(); j++) {
            // If this e-mail has been found again then union-find in order
            // to add under the same group the current e-mail and the already
            // stored e-mail
            if (email_id.find(accounts[i][j]) != email_id.end()) {
                int f1 = find(parent, i);
                int f2 = find(parent, email_id[accounts[i][j]]);
                // Union
                parent[f1] = f2;
            } else {
                // If this e-mail is found for the first time then add it to
                // the map
                email_id[accounts[i][j]] = i;
            }
        }
    }
    // We make a new map in order to store for every group the e-mails it contains
    unordered_map<int, vector<string>> mres;
    for (auto it : email_id) {
        int f = find(parent, it.second);
        mres[f].push_back(it.first);
    }
    
    // In the previous (mres) map we have our answer but we must give the proper structure
    // We add the name of the account (we retieve it from the initial vector since we have
    // the number of the group) and we sort the e-mails.
    vector<vector<string>> res;
    for (auto it : mres) {
        sort(it.second.begin(), it.second.end());
        vector<string> tmp = {accounts[it.first][0]};
        for (auto i : it.second) tmp.push_back(i);
        res.push_back(tmp);
    }
    return res;
}

int main()
{
//    string A="parker",B="morris",S="parser";
//    cout<<lexicographicallySmallestEquivalentString(A, B, S)<<"\n";
    
    return 0;
}
