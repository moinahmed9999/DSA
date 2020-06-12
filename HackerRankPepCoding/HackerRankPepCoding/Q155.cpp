//
//  Q155.cpp
//  HackerRankPepCoding
//
//  Created by Noor Mohd on 30/01/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<int>> dir={{-1,0},{0,-1},{1,0},{0,1}};

bool isSafeRat(int r, int c,vector<vector<int>> &maze)
{
    if (r<0 || r>=maze.size() || c<0 || c>=maze[0].size() || maze[r][c]==0) {
        return false;
    }
    return true;
}

bool ratInMaze(int r,int c, int count,vector<vector<int>> &maze, int limit)
{
    if (r==maze.size()-1 && c==maze[0].size()-1) {
        if (count<=limit) {
            return true;
        }
        return false;   
    }
    
    bool res=false;
    
    maze[r][c]=0;
    
    for (int i=0; i<dir.size(); i++) {
        int nr=r+dir[i][0];
        int nc=c+dir[i][1];
        
        if (isSafeRat(nr, nc, maze)) {
            res=res || ratInMaze(nr, nc, count+1, maze, limit);
        }
    }
    
    maze[r][c]=1;
    
    return res;
}

int main() {
    
    int N;
    cin>>N;
    
    vector<vector<int>> maze(N,vector<int>(N,0));

    int x;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin>>x;
            maze[i][j]=x;
        }
    }
    
    int limit;
    cin>>limit;
    
    if (ratInMaze(0, 0, 0, maze, limit)==false) {
        cout<<"false";
    }
    else
        cout<<"true";
    
    
    return 0;
}
