//
//  KosaRaju.cpp
//  Graph
//
//  Created by Noor Mohd on 07/03/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include<bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> graph(n, vector<int>());

void dfs(vector<vector<int>> graph,int src, vector<bool>& visited,vector<int>& ans) {
    visited[src] = true;
    for (int v : graph[src]) {
        if (!visited[v])
            dfs(graph, v, visited, ans);
    }
    ans.push_back(src);
}

void kosaRajuAlgo() {
    vector<bool> visited(n,false);
    vector<int> ans;
    for (int i=0; i<n; i++) {
        if (!visited[i]) {
            dfs(graph, i, visited, ans);
        }
    }
    
    vector<vector<int>> newGraph(n, vector<int>());
    for (int u=0; u<n; u++) {
        for (int v : graph[u]) {
            newGraph[v].push_back(u);
        }
    }
    
    visited.clear();
    vector<int> scc;
    while (ans.size()!=0) {
        int u=ans.back();
        ans.pop_back();
        if (!visited[u]) {
            dfs(newGraph, u, visited, scc);
        }
    }
}

// GFG - Strongly Connected Components (Kosaraju's Algo)
void dfs(int u, vector<vector<int>>& graph, vector<bool>& visited, stack<int>& st) {
    // topological sort
    visited[u]=true;
    for(int v: graph[u])
        if(!visited[v])
            dfs(v, graph, visited, st);
    st.push(u);
}

void dfs(int u, vector<vector<int>>& graph, vector<bool>& visited) {
    visited[u]=true;
    for(int v: graph[u])
        if(!visited[v])
            dfs(v, graph, visited);
}

int kosaraju(int V, vector<int> adj[]) {
    int count=0;
    vector<bool> visited(V, false);
    vector<vector<int>> graph(V, vector<int>()), reverseGraph(V, vector<int>());
    stack<int> st;
    for(int u=0;u<V;u++)
        for(int v:adj[u])
            graph[u].push_back(v);
    for(int u=0;u<V;u++)
        for(int v:graph[u])
            reverseGraph[v].push_back(u);
    for(int i=0;i<V;i++)    // topological sort
        if(!visited[i])
            dfs(i, graph, visited, st);
    for(int i=0;i<V;i++) visited[i]=false;
    while(st.size()!=0) {
        int u=st.top();
        st.pop();
        if(!visited[u]) {
            dfs(u, reverseGraph, visited);
            count++;
        }
    }
    return count;
}
