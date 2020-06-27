//
//  main.cpp
//  Graph
//
//  Created by Noor Mohd on 15/02/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> iPair;

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

void addEdge(int u,int v,int w, vector<vector<Edge*>>& graph) {
    graph[u].push_back(new Edge(v,w));
    graph[v].push_back(new Edge(u,w));
}

void display(vector<vector<Edge*>>& graph) {
    for (int i=0; i<graph.size(); i++) {
        cout<<i<<" -> ";
        for (Edge* e : graph[i]) {
            cout<<"("<<e->v<<","<<e->w<<") ";
        }
        cout<<"\n";
    }
}

int searchVertex(int u, int v, vector<vector<Edge*>>& graph) {
    int idx=-1;
    for (int i=0; i<graph[u].size(); i++) {
        if (graph[u][i]->v==v) {
            idx=i;
            break;
        }
    }
    return idx;
}

void removeEdge(int u,int v, vector<vector<Edge*>>& graph) {
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

void removeVertex_01(int v, vector<vector<Edge*>>& graph) {
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

void removeVertex_02(int u, vector<vector<Edge*>>& graph) {
    for (int i=(int)graph[u].size() -1; i>=0; i--) {
        int v=graph[u][i]->v;
        removeEdge(u, v, graph);
    }
}

//  DFS
bool hasPath(int source,int destination, vector<vector<Edge*>>& graph, vector<bool> &visited, string ans) {
    if (source==destination) {
        cout<<ans + to_string(destination) + " " << "\n";
        return true;
    }
    visited[source]=true;
    bool res=false;
    for (Edge* e : graph[source]) {
        if (!visited[e->v]) {
            res= res || hasPath(e->v, destination, graph, visited, ans + to_string(source) + " " );
        }
    }
    visited[source]=false;
    return res;
}

int allPath(int source,int destination, vector<vector<Edge*>>& graph, vector<bool> &visited, string ans) {
    if (source==destination) {
        cout<<ans + to_string(destination) + " " << "\n";
        return 1;
    }
    visited[source]=true;
    int count=0;
    for (Edge* e : graph[source]) {
        if (!visited[e->v]) {
            count += allPath(e->v, destination, graph, visited, ans + to_string(source) + " " );
        }
    }
    visited[source]=false;
    return count;
}

void hamiltonianPath(int src, int osrc, vector<vector<Edge*>>& graph, vector<bool> &visited, int count, string ans) {
    if (count==graph.size()-1) {
        int vIdx=searchVertex(src, osrc, graph);
        if (vIdx!=-1) {
            cout<<"Cycle : " + ans + " " + to_string(src)<< "\n";
        } else {
            cout<<"Path : " + ans + " " + to_string(src)<< "\n";
        }
    }
    visited[src]=true;
    for (Edge* e : graph[src]) {
        if (!visited[e->v]) {
            hamiltonianPath(e->v, osrc, graph, visited, count + 1, ans + " " + to_string(src));
        }
    }
    visited[src]=false;
}

void dfs(int u,vector<bool> &visited, vector<vector<Edge*>>& graph) {
    visited[u]=true;
    cout<<u<<" ";
    for (Edge* e : graph[u]) {
        if (!visited[e->v]) {
            dfs(e->v, visited, graph);
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
void hasCycle(int src, vector<bool> &visited, vector<vector<Edge*>>& graph) {
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

void bfs(int src, vector<bool> &visited, vector<vector<Edge*>>& graph) {
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

void gcc(vector<vector<Edge*>>& graph) {
    vector<bool> visited(graph.size(),false);
    int count=0;
    for (int i=0; i<graph.size(); i++) {
        if (!visited[i]) {
            bfs(i, visited, graph);
            count++;
        }
    }
    cout<<"GCC : "<<count<<"\n";
}

bool isBipartite(int u, vector<int>& visited, vector<vector<Edge*>>& graph) {
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

void bipartite(vector<vector<Edge*>>& graph) {
    vector<int> visited(graph.size(),-1);
    for (int i=0; i<graph.size(); i++) {
        if (visited[i]==-1) {
            bool res=isBipartite(i, visited, graph);
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

// LC 815 - Bus Routes
int busRoutes(vector<vector<int>>& routes, int S, int T) {
    unordered_map<int, vector<int>> stops;
    for (int i = 0; i < routes.size(); i++) {
        for (auto n : routes[i]) stops[n].push_back(i);
    }
    int ans = 0;
    queue<int> que;
    que.push(S);
    set<int> visitedStop, visitedBus;
    while (!que.empty()) {
        int size = (int) que.size();
        set<int> tmp;
        while (size--) {
            int cur = que.front();
            que.pop();
            if (cur == T) return ans;
            if (visitedStop.count(cur)) continue;
            visitedStop.emplace(cur);
            for (auto bus : stops[cur]) {
                if (visitedBus.count(bus)) continue;
                visitedBus.emplace(bus);
                for (auto stop : routes[bus])
                    tmp.emplace(stop);
            }
        }
        for (auto s : tmp) que.push(s);
        ans++;
    }
    return -1;
}

// LC 994 - Rotting Oranges
int orangesRotting(vector<vector<int>>& grid) {
    int n=(int) grid.size();
    if(n==0) return -1;
    int m=(int) grid[0].size();
    int ans=-1, count=0;
    queue<vector<int>> q;
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(grid[i][j]==2) q.push({i,j});
            else if(grid[i][j]==1) count++;
        }
    }
    if(count==0) return 0;
    while(!q.empty()) {
        int size=(int) q.size(), flag=0;
        while(size--) {
            vector<int> front=q.front();
            int x=front[0], y=front[1];
            q.pop();
            if(x-1>=0 && grid[x-1][y]==1) {
                grid[x-1][y]=2;
                q.push({x-1, y});
                flag++;
                count--;
            }
            if(x+1<n && grid[x+1][y]==1) {
                grid[x+1][y]=2;
                q.push({x+1, y});
                flag++;
                count--;
            }
            if(y-1>=0 && grid[x][y-1]==1) {
                grid[x][y-1]=2;
                q.push({x, y-1});
                flag++;
                count--;
            }
            if(y+1<m && grid[x][y+1]==1) {
                grid[x][y+1]=2;
                q.push({x, y+1});
                flag++;
                count--;
            }
        }
        if(flag>0) ans=ans==-1?1:ans+1;
    }
    return ans==-1 || count!=0?-1: ans;
}

// LC 127 - Word Ladder
int wordLadder(string beginWord, string endWord, vector<string>& wordList) {
    unordered_map<string, vector<string>> map;
    unordered_map<string, bool> visited;
    bool flag=false;
    for(string word: wordList) {
        if(word==endWord) flag=true;
        for(int i=0;i<word.size();i++) {
            string newWord=word.substr(0,i) + '*' + word.substr(i+1);
            map[newWord].push_back(word);
            visited[newWord]=false;
        }
    }
    if(!flag)  return 0;
    flag=false;
    int level=1;
    queue<string> q;
    q.push(beginWord);
    while(!q.empty()) {
        int size=(int) q.size();
        while(size--) {
            string currWord=q.front();
            q.pop();
            if(currWord==endWord) {
                flag=true;
                break;
            }
            for(int i=0;i<currWord.size();i++) {
                string newWord=currWord.substr(0,i)+'*'+currWord.substr(i+1);
                if(!visited[newWord]) {
                    visited[newWord]=true;
                    for(string word: map[newWord]) {
                        if(word!=currWord) {
                            q.push(word);
                        }
                    }
                }
            }
        }
        if(flag) break;
        level++;
    }
    if(flag) return level;
    return 0;
}

// LC 433 - Minimum Genetic Mutation
int minGeneticMutation(string start, string end, vector<string>& bank) {
    unordered_map<string, vector<string>> map;
    unordered_map<string, bool> visited;
    bool flag=false;
    for(string gene: bank) {
        if(gene==end) flag=true;
        for(int i=0;i<gene.size();i++) {
            string newGene=gene.substr(0,i) + '*' + gene.substr(i+1);
            map[newGene].push_back(gene);
            visited[newGene]=false;
        }
    }
    if(!flag)  return -1;
    flag=false;
    int level=0;
    queue<string> q;
    q.push(start);
    while(!q.empty()) {
        int size=(int) q.size();
        while(size--) {
            string currGene=q.front();
            q.pop();
            if(currGene==end) {
                flag=true;
                break;
            }
            for(int i=0;i<currGene.size();i++) {
                string newGene=currGene.substr(0,i)+'*'+currGene.substr(i+1);
                if(!visited[newGene]) {
                    visited[newGene]=true;
                    for(string gene: map[newGene]) {
                        if(gene!=currGene) {
                            q.push(gene);
                        }
                    }
                }
            }
        }
        if(flag) break;
        level++;
    }
    if(flag) return level;
    return -1;
}

// LC 854 - K-Similar Strings
int kSimilarStrings(string A, string B) {
    int n=(int) A.size();
    if(n==0) return 0;
    if(A==B) return 0;
    unordered_set<string> visited;
    queue<string> q;
    int level=0;
    bool flag=false;
    q.push(B);
    visited.insert(B);
    while(!q.empty()) {
        int size=(int) q.size();
        while(size--) {
            string b=q.front();
            q.pop();
            if(b==A) {
                flag=true;
                break;
            }
            // finding possible swaps starting with first unmatched character
            int i=0;
            while(A[i]==b[i]) i++;
            for(int j=i+1;j<n;j++) {
                if(b[j]==A[i]) {
                    swap(b[i], b[j]);
                    if(visited.find(b)==visited.end()) {
                        q.push(b);
                        visited.insert(b);
                    }
                    swap(b[i], b[j]);
                }
            }
        }
        if(flag) break;
        level++;
    }
    return level;
}

// LC 743 - Network Delay Time
int networkDelayTime(vector<vector<int>>& times, int N, int K) {
    int ans=0, count=0;
    vector<bool> visited(N, false);
    vector<vector<iPair>> graph(N, vector<iPair>());
    for(vector<int>& edge: times)
        graph[edge[0]-1].push_back(make_pair(edge[1]-1, edge[2]));
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    pq.push(make_pair(0, K-1));
    while(!pq.empty()) {
        int u=pq.top().second, wsf=pq.top().first;
        pq.pop();
        if(visited[u]) continue;
        visited[u]=true;
        count++;
        ans=wsf;
        for(auto& edge: graph[u]) {
            if(!visited[edge.first]) {
                pq.push(make_pair(wsf+edge.second, edge.first));
            }
        }
    }
    return count==N?ans:-1;
}

int main() {
    int n=4;
    vector<vector<Edge*>> graph(n,vector<Edge*>());
    addEdge(0, 1, 10, graph);
    addEdge(0, 2, 10, graph);
    addEdge(0, 3, 10, graph);
    addEdge(2, 1, 10, graph);
    addEdge(3, 1, 10, graph);
    addEdge(3, 2, 10, graph);
//    addEdge(3, 4, 10, graph);
//    addEdge(4, 5, 10, graph);
//    addEdge(3, 6, 10, graph);
//    addEdge(5, 6, 10, graph);
//    addEdge(7, 6, 10, graph);
//    addEdge(8, 9, 10, graph);
//    display(graph);
    vector<bool> visited(n,false);
//    hasPath(0, 6, graph, visited, "");
    hamiltonianPath(0, 0, graph, visited, 0, "");
//    dfs(0, visited, graph);
//    vector<vector<char>> board={
//        {'X','X','X','X'},
//        {'X','O','O','X'},
//        {'X','X','O','X'},
//        {'X','O','X','X'}   };
//    surroundedRegions(board);
//    hasCycle(0, visited, graph);
//    bfs(0, visited, graph);
//    gcc(graph);
//    bipartite(graph);
    return 0;
}
void shortestPath(vector<pair<int,int> > adj[], int V, int src)
{
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
    
    vector<int> dist(V, INT_MAX);
    pq.push(make_pair(0, src));
    dist[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        for (auto x : adj[u])
        {
            int v = x.first;
            int weight = x.second;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
