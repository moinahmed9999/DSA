//
//  DirectedGraph.cpp
//  Graph
//
//  Created by Noor Mohd on 12/03/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include <bits/stdc++.h>
using namespace std;

int n=8;
vector<vector<int>> graph(n,vector<int> ());

void display() {
    for (int i = 0; i < n; i++) {
        cout << i << " -> ";
        for (int e : graph[i]) {
            cout << e << ", ";
        }
        cout << "\n";
    }
    cout << "\n";
}

//  Topological Sort

void dfsTopologicalSort_01(int u, vector<bool> &visited, stack<int> &st) {
    visited[u]=true;
    for (int v : graph[u]) {
        if (!visited[v]) {
            dfsTopologicalSort_01(v, visited, st);
        }
    }
    st.push(u);
}

void topologicalSort_01() {     //  Cannot tell if cycle has occured
    vector<bool> visited(n, false);
    stack<int> st;
    for (int i=0; i<n; i++) {
        if (!visited[i]) {
            dfsTopologicalSort_01(i, visited, st);
        }
    }
    while (!st.empty()) {
        cout<<st.top()<<" ";
        st.pop();
    }
}

bool dfsTopologicalSort_02(int u,vector<bool> &visited,vector<bool> &cycle,vector<int> &st) {
    visited[u]=cycle[u]=true;
    bool res=false;
    for (int v : graph[u]) {
        if (!visited[v]) {
            res = dfsTopologicalSort_02(v, visited, cycle,st);
        } else if (cycle[v]){
            return true;    //  Cycle detected
        }
    }
    cycle[u]=false;
    st.push_back(u);
    return res;
}

vector<int> topologicalSort_02() {     //  Can tell if cycle has occured using a cycle array
    vector<bool> visited(n, false);
    vector<bool> cycle(n, false);
    vector<int> st;
    bool res=false;
    for (int i=0; i<n && !res; i++) {
        if (!visited[i]) {
            res = res || dfsTopologicalSort_02(i, visited, cycle, st);
        }
    }
    if (res) {
        st.clear();
    }
    for (int i=0; i<st.size(); i++) {
        cout<<st[i]<<" ";
    }
    cout<<"\n";
    return st;
}

bool dfsTopologicalSort_03(int u,vector<int> &visited,vector<int> &st) {
    if (visited[u]==1) {
        return true;
    } else if (visited[u]==2) {
        return false;
    }
    visited[u]=1;
    bool res=false;
    for (int v : graph[u]) {
        res = res || dfsTopologicalSort_03(v, visited, st);
    }
    visited[u]=2;
    st.push_back(u);
    return res;
}

vector<int> topologicalSort_03() {
    //  Can tell if cycle has occured using a int visited array
    vector<int> visited(n, 0);
    vector<int> st;
    bool res=false;
    for (int i=0; i<n && !res; i++) {
        if (!visited[i]) {
            res = dfsTopologicalSort_03(i, visited, st);
        }
    }
    if (res) {
        st.clear();
    }
    for (int i=0; i<st.size(); i++) {
        cout<<st[i]<<" ";
    }
    cout<<"\n";
    return st;
}

void topologicalSortKhansAlgo() {
    vector<int> incidentEdges(n,0);
    for (int i=0; i<n; i++) {
        for (int v : graph[i]) {
            incidentEdges[v]++;
        }
    }
    queue<int> q,ans;
    for (int i=0; i<n; i++) {
        if (incidentEdges[i]==0) {
            q.push(i);
        }
    }
    while (q.size()!=0) {
        int u=q.front();
        q.pop();
        ans.push(u);
        for (int v : graph[u]) {
            if (--incidentEdges[v]==0) {
                q.push(v);
            }
        }
    }
    if (ans.size()!=n) {
        cout<<"Cycle !!\n";
    } else {
        while (ans.size()!=0) {
            cout<<ans.front()<<" ";
            ans.pop();
        }
        cout<<"\n";
    }
}


int main() {
    graph[0].push_back(1);
    graph[0].push_back(6);
    graph[1].push_back(2);
    graph[2].push_back(3);
    graph[4].push_back(5);
    graph[5].push_back(3);
    graph[7].push_back(4);
    graph[7].push_back(6);
    
//    topologicalSort_01();
//    topologicalSort_02();
//    topologicalSort_03();
//    topologicalSortKhansAlgo();
    return 0;
}
