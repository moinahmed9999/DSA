//
//  MST.cpp
//  Graph
//
//  Created by Noor Mohd on 26/06/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include <bits/stdc++.h>
using namespace std;

// LC 1168 - Optimise Water Distribution in a Village   (Kruskal's Algorithm)
int find(int i, vector<int>& parents) {
    if (i!=parents[i])
        parents[i]=find(parents[i], parents);
    return parents[i];
}

void join(int u, int v, vector<int>& parents, vector<int>& size, vector<int>& pipe, int& ans) {
    int p1=find(u, parents), p2=find(v, parents);
    if(p1==p2) return;
    if(size[u]<size[v]) {
        parents[p1]=p2;
        size[v]+=size[u];
        ans+=pipe[2];
    } else {
        parents[p2]=p1;
        size[u]+=size[v];
        ans+=pipe[2];
    }
}

int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
    int ans = 0;
    for(int i=0; i<n; i++) pipes.push_back({0, i+1, wells[i]});
    sort(pipes.begin(), pipes.end(), [](auto &a, auto &b) {return a[2] < b[2]; });
    vector<int> parents(n+1), size(n+1, 1);
    iota(parents.begin(), parents.end(), 0);
    for(vector<int>& pipe : pipes) {
        join(pipe[0], pipe[1], parents, size, pipe, ans);
    }
    return ans;
}

// LC 1135 - Connecting Cities With Minimum Cost    (Kruskal's Algorithm)
void join(int u, int v, vector<int>& parents, vector<int>& size, vector<int>& connection, int& ans, int& count) {
    int p1=find(u, parents), p2=find(v, parents);
    if(p1==p2) return;
    if(size[u]<size[v]) {
        parents[p1]=p2;
        size[v]+=size[u];
        ans+=connection[2];
        count--;
    } else {
        parents[p2]=p1;
        size[u]+=size[v];
        ans+=connection[2];
        count--;
    }
}

int minimumCost(int n, vector<vector<int>> connections) {
    int ans = 0, count=n-1;
    sort(connections.begin(), connections.end(), [](auto &a, auto &b) {return a[2] < b[2]; });
    vector<int> parents(n), size(n, 1);
    iota(parents.begin(), parents.end(), 0);
    for(vector<int>& connection : connections) {
        if (count==0) return ans;
        join(connection[0]-1, connection[1]-1, parents, size, connection, ans, count);
    }
    return count!=0?-1:ans;
}

// HackerEarth - Mr. President
void join(int u, int v, vector<int>& parents, vector<int>& size, vector<int>& road, vector<int>& res, int& ans, int& count) {
    int p1=find(u, parents), p2=find(v, parents);
    if(p1==p2) return;
    if(size[u]<size[v]) {
        parents[p1]=p2;
        size[v]+=size[u];
    } else {
        parents[p2]=p1;
        size[u]+=size[v];
    }
    ans+=road[2];
    count--;
    res.push_back(road[2]);
}

int mrPresident(int n, int m, int k, vector<vector<int>>& roads) {
    int ans = 0, count=n-1, transformation=0;
    sort(roads.begin(), roads.end(), [](auto &a, auto &b) {return a[2] < b[2]; });
    vector<int> parents(n), size(n, 1), res;
    iota(parents.begin(), parents.end(), 0);
    for(vector<int>& road : roads) {
        if (count==0) break;
        join(road[0]-1, road[1]-1, parents, size, road, res, ans, count);
    }
    if(count!=0) return -1;
    sort(res.begin(), res.end());
    int x=(int) res.size();
    for(int i=x-1;i>=0;i--) {
        if(ans<=k) break;
        ans+=1-res[i];
        transformation++;
    }
    return ans<=k?transformation:-1;
}
