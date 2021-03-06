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

// LC 839 - Similar String Groups
int find(int i, vector<int>& parents) {
    if (i!=parents[i])
        parents[i]=find(parents[i], parents);
    return parents[i];
}

void join(int i, int j, vector<int>& parents, vector<int>& size, int& count) {
    int p1=find(i, parents), p2=find(j, parents);
    if(p1==p2) return ;
    count--;
    if (size[p1]<size[p2]) {
        parents[p1]=p2;
        size[p2]+=size[p1];
    } else {
        parents[p2]=p1;
        size[p1]+=size[p2];
    }
}

bool similar(string &a, string &b) {
    int differentChar = 0;
    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i] && ++differentChar > 2)
            return false;
    return true;
}

int numSimilarGroups(vector<string>& A) {
    int n=(int) A.size();
    vector<int> parents(n), size(n, 1);
    for(int i=0;i<n;i++) parents[i]=i;
    int count=n;
    for (int i=0;i<n;i++)
        for (int j=i+1;j<n;j++)
            if (similar(A[i], A[j]))
                join(i, j, parents, size, count);
    return count;
}

// LC 959 - Regions Cut By Slashes
void join(int x, int y, vector<int>& parents, int& count) {
    int p1=find(x, parents), p2=find(y, parents);
    if (p1!=p2) {
        parents[p1]=p2;
        count--;
    }
}

int get(int i, int j, int k, int n) {
    return ((i*n)+j)*4 + k;
}

int regionsBySlashes(vector<string>& grid) {
    int n=(int) grid.size();
    int N= n*n*4, count=N;
    vector<int> parents(N);
    for (int i=0;i<N;i++) parents[i]=i;
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            if(i-1>=0) join(get(i,j,0,n), get(i-1,j,3,n), parents, count);
            if(j-1>=0) join(get(i,j,1,n), get(i,j-1,2,n), parents, count);
            if(j+1<n) join(get(i,j,2,n), get(i,j+1,1,n), parents, count);
            if(i+1<n) join(get(i,j,3,n), get(i+1,j,0,n), parents, count);
            if (grid[i][j]!='\\') {
                join(get(i,j,0,n), get(i,j,1,n), parents, count);
                join(get(i,j,2,n), get(i,j,3,n), parents, count);
            }
            if (grid[i][j]!='/') {
                join(get(i,j,0,n), get(i,j,2,n), parents, count);
                join(get(i,j,1,n), get(i,j,3,n), parents, count);
            }
        }
    }
    return count;
}

// LC 1319 - Number of Operations to Make Network Connected
int makeConnected(int n, vector<vector<int>>& connections) {
    if (n==1) return 0;
    vector<int> parent(n, 0);
    iota(parent.begin(), parent.end(), 0);
    int duplicate = 0;
    for (vector<int>& connection : connections) {
        int pu=find(connection[0], parent);
        int pv=find(connection[1], parent);
        if (pu!=pv) parent[pu]=pv;
        else duplicate++;
    }
    int components=0;
    for (int i=0;i<n;i++)
        if (i==parent[i]) components++;
    return components-1>duplicate? -1 : components- 1;
}

// LC 924 - Minimize Malware Spread
int minMalwareSpread(vector<vector<int>> &graph, vector<int> &initial) {
    int n =(int) graph.size();
    vector<int> parents(n);
    for (int i = 0; i < n; i++) parents[i]=i;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && graph[i][j] == 1)
                parents[find(i, parents)] = find(j, parents);
    
    vector<int> IPC(n, 0); //infected patient count
    vector<int> POC(n, 0); //population of country
    
    sort(initial.begin(), initial.end());
    int ans = initial[0];
    for (int patient : initial) IPC[find(patient, parents)]++;
    for (int i = 0; i < n; i++) POC[find(i, parents)]++;
    
    int maxPopulation = 0;
    for (int patient : initial) {
        if (IPC[parents[patient]] == 1 &&
            POC[parents[patient]] > maxPopulation) {
            maxPopulation = POC[parents[patient]];
            ans = patient;
        }
    }
    
    return ans;
}

// LC 928 - Minimize Malware Spread II
void join(int u, int v, vector<int>& parents, vector<int>& size) {
    int p1=find(u, parents), p2=find(v, parents);
    if(p1==p2) return;
    if(size[p1]<size[p2]) {
        parents[p1]=p2;
        size[p2]+=size[p1];
    } else {
        parents[p2]=p1;
        size[p1]+=size[p2];
    }
}

int minMalwareSpreadII(vector<vector<int>>& graph, vector<int>& initial) {
    int n=(int) graph.size();
    vector<int> parents(n), size(n,1), uninfected(n,1);
    vector<int> infectedNeighbour(n, 0);
    iota(parents.begin(), parents.end(), 0);
    for(int i: initial) uninfected[i]=0; // infected
    for(int i=0;i<n;i++) if(uninfected[i])
        for(int j=0;j<n;j++) if(uninfected[j])
            if(graph[i][j])
                join(i,j,parents,size);
    // map of infected->{uninfected neighbours's parent}
    unordered_map<int, unordered_set<int>> map;
    for(int i: initial) {
        for(int j=0;j<n;j++) if(uninfected[j])
            if(graph[i][j])
                map[i].insert(find(j, parents));
        for(int k: map[i])
            infectedNeighbour[k]++;
    }
    int ans=-1, maxSize=-1;
    // find a dsu component with only one infected neighbour
    for(pair<int, unordered_set<int>> p: map) {
        int countSize=0;
        for(int i: p.second)
            if(infectedNeighbour[i]==1)
                countSize+=size[i];// size of that component
        if(countSize> maxSize || (countSize==maxSize && p.first<ans)) {
            ans=p.first;
            maxSize=countSize;
        }
    }
    return ans;
}

// HackerRank - Journey to the Moon
int journeyToMoon(int n, vector<vector<int>> astronaut) {
    vector<int> parents(n), size(n, 1);
    iota(parents.begin(), parents.end(), 0);
    for(vector<int>& pair: astronaut) {
        join(pair[0], pair[1], parents, size);
    }
    int sum=0, ans=0;
    unordered_set<int> set;
    for(int i=0;i<n;i++) set.insert(find(i, parents));
    for(int i: set) {
        ans+=size[i]*sum;
        sum+=size[i];
    }
    return ans;
}

// LC 128 - Longest Consecutive Sequence
int longestConsecutive(vector<int>& nums) {
    int n=(int) nums.size(), ans=0;
    vector<int> parents(n), size(n, 1);
    iota(parents.begin(), parents.end(), 0);
    unordered_map<int, int> map;
    for(int i=0;i<n;i++) {
        if(map.find(nums[i])!=map.end()) continue;
        map[nums[i]]=i;
        if(map.find(nums[i]-1)!=map.end())
            join(i, map[nums[i]-1], parents, size);
        if(map.find(nums[i]+1)!=map.end())
            join(i, map[nums[i]+1], parents, size);
    }
    for(int i=0;i<n;i++)
        ans=max(ans, size[i]);
    return ans;
}

// LC 434 - Number of Islands II
vector<int> numIslands2(int n, int m, vector<vector<int>> &operators) {
    int N=n*m, k=(int) operators.size() ,count=0;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    vector<int> parents(N, -1), size(N, -1), res(k);
    for(int i=0;i<k;i++) {
        int x=operators[i][0], y=operators[i][1];
        if(grid[x][y]) {
            res[i]=count;
            continue;
        }
        grid[x][y]=1;
        count++;
        int a=(m*x)+y;
        parents[a]=a;
        size[a]=1;
        if(x-1>=0 && grid[x-1][y]==1) {
            int b=(m*(x-1))+y;
            join(a, b, parents, size, count);
        }
        if(x+1<n && grid[x+1][y]==1) {
            int b=(m*(x+1))+y;
            join(a, b, parents, size, count);
        }
        if(y-1>=0 && grid[x][y-1]==1) {
            int b=(m*x)+(y-1);
            join(a, b, parents, size, count);
        }
        if(y+1<m && grid[x][y+1]==1) {
            int b=(m*x)+(y+1);
            join(a, b, parents, size, count);
        }
        res[i]=count;
    }
    return res;
}

// LC 399 - Evaluate Division
void add(string& a, unordered_map<string, string>& parents, unordered_map<string, double>& val) {
    if(parents.find(a)!=parents.end()) return;
    parents[a]=a;
    val[a]=1.0;
}

string find(string& a, unordered_map<string, string>& parents, unordered_map<string, double>& val) {
    string p=parents[a];
    if(p!=a) {
        string pp=find(p, parents, val);
        val[a]=val[a]*val[p];
        parents[a]=pp;
    }
    return parents[a];
}

void join(string& a, string& b, double v, unordered_map<string, string>& parents, unordered_map<string, double>& val) {
    add(a, parents, val);
    add(b, parents, val);
    string p1=find(a, parents, val), p2=find(b, parents, val);
    parents[p1]=p2;
    val[p1]=v*val[b]/val[a];
}

vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
    unordered_map<string, string> parents;
    unordered_map<string, double> val;
    vector<double> res(queries.size());
    // for a/b=2.0 , b is parent of a.
    // if a or b are not present in map already then their val is 1.0;
    // during join, we find relative value of the members of a component
    // and during find we put each child with correct parent and on the way
    // we evaluate the correct val;
    for(int i=0;i<(int) equations.size();i++) {
        join(equations[i][0], equations[i][1], values[i], parents, val);
    }
    for (int i=0; i<(int) queries.size();i++) {
        string x=queries[i][0], y=queries[i][1];
        res[i]=(parents.find(x)!=parents.end() &&
                parents.find(y)!=parents.end() &&
                find(x, parents, val)==find(y, parents, val))?
        (val[x]/val[y]):-1.0;
    }
    return res;
}

int main()
{
//    string A="parker",B="morris",S="parser";
//    cout<<lexicographicallySmallestEquivalentString(A, B, S)<<"\n";
    
    return 0;
}
