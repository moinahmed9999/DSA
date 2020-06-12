//
//  Articulation.cpp
//  Graph
//
//  Created by Noor Mohd on 08/03/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

int n=6;
int countTime=0;
int rootCount=0;

vector<int> low(n,0);
vector<int> dis(n,0);
vector<int> par(n,0);
vector<int> ap(n,0);
vector<bool> vis(n, false);

vector<vector<int>> graph(n, vector<int>());

void addEdge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
}

void dfs(int u) {
    dis[u]=low[u]=countTime++;
    vis[u]=true;
    for (int nbr : graph[u]) {
        if (!vis[nbr]) {    //unvisited
            if (par[u] == -1) {
                rootCount++;
            }
            par[nbr]=u;
            dfs(nbr);
            
            // check for articulation point
            // bactrack condition
            if (dis[u] <= low[nbr]) {
                ap[u]++;
            }
            
            // check for articulation edge
            if (dis[u] < low[nbr]) {
                cout<<"Articulation Edge : "<<u<<"->"<<nbr<<"\n";
            }
            
            // update low
            low[u]=min(low[u], low[nbr]);
        } else if (nbr != par[u]) {  // visited and not parent
            low[u]=min(low[u], dis[nbr]);
        }
    }
}

void APointAndBridge() {
    int src=0;
    dfs(src);
    if (rootCount==1) {
        ap[src]--;
    }
}

int main()
{
    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(1, 3);
    addEdge(1, 4);
    addEdge(1, 5);
    addEdge(4, 5);
    APointAndBridge();
    int count=0;
    for(int i=0;i<n;i++) {
        if(ap[i]>0)
            count++;
    }
    cout<<count<<"\n";
    return 0;
}
