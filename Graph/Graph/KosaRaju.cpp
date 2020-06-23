//
//  KosaRaju.cpp
//  Graph
//
//  Created by Noor Mohd on 07/03/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include<iostream>
#include<vector>
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
