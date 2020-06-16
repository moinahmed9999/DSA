//
//  main.cpp
//  Graph
//
//  Created by Noor Mohd on 15/02/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include <bits/stdc++.h>
using namespace std;

//int* fun() {    // Test stack growth direction
//    int a=10;
//    int* b=&a;
//    return b;
//}

class Edge {
public:
    int v=0;
    int w=0;
    Edge(int v, int w) {
        this->v=v;
        this->w=w;
    }
};

int n=10;
vector<vector<Edge*>> graph(n,vector<Edge*>());

void addEdge(int u,int v,int w) {
    graph[u].push_back(new Edge(v,w));
    graph[v].push_back(new Edge(u,w));
}

void display() {
    for (int i=0; i<n; i++) {
        cout<<i<<" -> ";
        for (Edge* e : graph[i]) {
            cout<<"("<<e->v<<","<<e->w<<") ";
        }
        cout<<"\n";
    }
}

int searchVertex(int u, int v) {
    int idx=-1;
    for (int i=0; i<graph[u].size(); i++) {
        if (graph[u][i]->v==v) {
            idx=i;
            break;
        }
    }
    return idx;
}

void removeEdge(int u,int v) {
    for (int i=0; i<graph[u].size(); i++) {
        if (graph[u][i]->v==v) {
            graph[u].erase(graph[u].begin() + i);
            break;
        }
    }
    for (int i=0; i<graph[v].size(); i++) {
        if (graph[v][i]->v==u) {
            graph[v].erase(graph[v].begin() + i);
            break;
        }
    }
}

void removeVertex_01(int v) {
    vector<int> edges;
    for (int i=0; i<graph[v].size(); i++) {
        edges.push_back(graph[v][i]->v);
    }
    for (int u=0; u<edges.size(); u++) {
        for (int i=0; i<graph[u].size(); i++) {
            if (graph[u][i]->v==v) {
                graph[u].erase(graph[u].begin() + i);
                break;
            }
        }
    }
    int size=(int)graph[v].size();
    while (size--) {
        graph[v].pop_back();
    }
}

void removeVertex_02(int u) {
    for (int i=(int)graph[u].size() -1; i>=0; i--) {
        int v=graph[u][i]->v;
        removeEdge(u, v);
    }
}

//  DFS
bool hasPath(int source,int destination,vector<bool> &visited, string ans) {
    if (source==destination) {
        cout<<ans + to_string(destination) + " " << "\n";
        return true;
    }
    visited[source]=true;
    bool res=false;
    for (Edge* e : graph[source]) {
        if (!visited[e->v]) {
            res= res || hasPath(e->v, destination, visited, ans + to_string(source) + " " );
        }
    }
    return res;
}

int allPath(int source,int destination,vector<bool> &visited, string ans) {
    if (source==destination) {
        cout<<ans + to_string(destination) + " " << "\n";
        return 1;
    }
    visited[source]=true;
    int count=0;
    for (Edge* e : graph[source]) {
        if (!visited[e->v]) {
            count += allPath(e->v, destination, visited, ans + to_string(source) + " " );
        }
    }
    visited[source]=false;
    return count;
}

void hamiltonianPath(int src, int osrc, vector<bool> &visited, int count, string ans) {
    if (count==n-1) {
        int vIdx=searchVertex(src, osrc);
        if (vIdx!=-1) {
            cout<<"Cycle : " + ans + " " + to_string(src)<< "\n";
        } else {
            cout<<"Path : " + ans + " " + to_string(src)<< "\n";
        }
    }
    visited[src]=true;
    for (Edge* e : graph[src]) {
        if (!visited[e->v]) {
            hamiltonianPath(e->v, osrc, visited, count + 1, ans + " " + to_string(src));
        }
    }
    visited[src]=false;
}

void dfs(int u,vector<bool> &visited) {
    visited[u]=true;
    cout<<u<<" ";
    for (Edge* e : graph[u]) {
        if (!visited[e->v]) {
            dfs(e->v, visited);
        }
    }
}

void dfsSurroundedRegions(int r, int c, int n, int m, vector<vector<char>> &board) {
    if (board[r][c]!='O') {
        return;
    }
    board[r][c]='+';
    if (r-1>=0) {
        dfsSurroundedRegions(r-1, c, n, m, board);
    }
    if (r+1<n) {
        dfsSurroundedRegions(r+1, c, n, m, board);
    }
    if (c-1>=0) {
        dfsSurroundedRegions(r, c-1, n, m, board);
    }
    if (c+1<m) {
        dfsSurroundedRegions(r, c+1, n, m, board);
    }
}

void surroundedRegions(vector<vector<char>> &board) {
    if (board.size() == 0)
        return;
    int n=(int)board.size();
    int m=(int)board[0].size();
    for (int i=0; i<m; i++) {
        if (board[0][i]=='O') {
            dfsSurroundedRegions(0, i, n, m, board);
        }
        if (board[n-1][i]=='O') {
            dfsSurroundedRegions(n-1, i, n, m, board);
        }
    }
    for (int i=0; i<n; i++) {
        if (board[i][0]=='O') {
            dfsSurroundedRegions(i, 0, n, m, board);
        }
        if (board[i][m-1]=='O') {
            dfsSurroundedRegions(i, m-1, n, m, board);
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (board[i][j]=='O') {
                board[i][j]='X';
            }
            if (board[i][j]=='+') {
                board[i][j]='O';
            }
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cout<<board[i][j]<<" ";
        }
        cout<<"\n";
    }
}

//  BFS
void hasCycle(int src, vector<bool> &visited) {
    queue<int> q;
    q.push(src);
    while (q.size()!=0) {
        int size=(int)q.size();
        while (size--) {
            int u=q.front();
            q.pop();
            if (visited[u]) {
                cout<<"Cycle : " + to_string(u) + "\n";
                continue;
            }
            visited[u]=true;
            for (Edge* e : graph[u]) {
                if (!visited[e->v]) {
                    q.push(e->v);
                }
            }
        }
    }
}

void bfs(int src, vector<bool> &visited) {
    queue<int> q;
    visited[src]=true;
    cout<<src<<" ";
    q.push(src);
    while (q.size()!=0) {
        int size=(int)q.size();
        while (size--) {
            int u=q.front();
            q.pop();
            for (Edge* e : graph[u]) {
                if (!visited[e->v]) {
                    visited[e->v]=true;
                    cout<<e->v<<" ";
                    q.push(e->v);
                }
            }
        }
    }
    cout<<"\n";
}

void gcc() {
    vector<bool> visited(n,false);
    int count=0;
    for (int i=0; i<n; i++) {
        if (!visited[i]) {
            bfs(i, visited);
            count++;
        }
    }
    cout<<"GCC : "<<count<<"\n";
}

bool isBipartite(int u, vector<int>& visited) {
    queue<pair<int, int>> q;
    q.push({u,0});
    while (q.size()!=0) {
        int v=q.front().first;
        int c=q.front().second;
        q.pop();
        if (visited[v]!=-1) {
            if (visited[v]!=c) {
                return false;   //  Conflict
            }
            continue;
        }
        visited[v]=c;
        for (Edge* e : graph[v]) {
            if (visited[v]==-1) {
                q.push({e->v,(c+1)%2});
            }
        }
    }
    return true;
}

void bipartite() {
    vector<int> visited(n,-1);
    for (int i=0; i<n; i++) {
        if (visited[i]==-1) {
            bool res=isBipartite(i, visited);
            if (!res) {
                cout<<(boolalpha)<<false<<"\n";
            }
        }
    }
    cout<<(boolalpha)<<true<<"\n";
}

// LC 787 - Cheapest Flights Within K Stops
int dfsCheapestFlightWithinKStops(vector<vector<vector<int>>>& graph, vector<bool>& visited, vector<vector<int>>& dp,  int src, int dst, int k) {
    if(src==dst) return 0;
    if(k==0) return -1;
    if(dp[k][src]!=0) return dp[k][src];
    visited[src]=true;
    int res, minCost=INT_MAX;
    for(vector<int> edge: graph[src]) {
        if(!visited[edge[0]]) {
            res=dfsCheapestFlightWithinKStops(graph, visited, dp, edge[0], dst, k-1);
            if(res!=-1) {
                minCost=min(minCost, res+edge[1]);
            }
        }
    }
    visited[src]=false;
    return dp[k][src]=minCost==INT_MAX?-1:minCost;
}

int cheapestFlightWithinKStops(int n, vector<vector<int>>& flights, int src, int dst, int K) {
    vector<vector<vector<int>>> graph(n);
    vector<bool> visited(n, false);
    vector<vector<int>> dp(K+1, vector<int> (n, 0));
    for(vector<int> flight: flights) {
        graph[flight[0]].push_back({flight[1], flight[2]});
    }
    visited[src]=true;
    int res, minCost=INT_MAX;
    for(vector<int> edge: graph[src]) {
        if(!visited[edge[0]]) {
            res=dfsCheapestFlightWithinKStops(graph, visited, dp, edge[0], dst, K);
            if(res!=-1) {
                minCost=min(minCost, res+edge[1]);
            }
        }
    }
    visited[src]=false;
    return minCost==INT_MAX?-1:minCost;
}

// LC 1092 - Flower Planting With No Adjacent
vector<int> gardenNoAdj(int N, vector<vector<int>>& paths) {
    vector<vector<int>> graph(N, vector<int>());
    vector<int> color(N); // color of each garden
    for(vector<int> path: paths) {
        graph[path[0]-1].push_back(path[1]-1);
        graph[path[1]-1].push_back(path[0]-1);
    }
    for(int i=0;i<N;i++) {
        vector<int> unavailableColors(4, 0);
        for(int v: graph[i]) {
            if(color[v]!=0/*it has been assigned a color, means unavailable*/) {
                unavailableColors[color[v]-1]=1;
            }
        }
        for(int j=1;j<=4;j++) {
            if(unavailableColors[j-1]==0/*available color*/) {
                color[i]=j;
            }
        }
    }
    return color;
}

int main() {
    addEdge(0, 1, 10);
    addEdge(0, 3, 10);
    addEdge(2, 1, 10);
    addEdge(3, 2, 10);
    addEdge(3, 4, 10);
    addEdge(4, 5, 10);
    addEdge(4, 6, 10);
    addEdge(5, 6, 10);
    addEdge(7, 8, 10);
    addEdge(8, 9, 10);
//    display();
    vector<bool> visited(n,false);
//    hasPath(0, 6, visited, "");
//    hamiltonianPath(0, 0, visited, 0, "");
//    dfs(0, visited);
//    vector<vector<char>> board={
//        {'X','X','X','X'},
//        {'X','O','O','X'},
//        {'X','X','O','X'},
//        {'X','O','X','X'}   };
//    surroundedRegions(board);
//    hasCycle(0, visited);
//    bfs(0, visited);
//    gcc();
    bipartite();
    return 0;
}
