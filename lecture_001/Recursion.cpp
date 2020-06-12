//
//  Recursion.cpp
//  Recursion
//
//  Created by Noor Mohd on 22/01/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include <bits/stdc++.h>
using namespace std;

int permutation_01(string str, string ans)
{
    if (str.length() == 0)
    {
        cout << ans << "\n";
        return 1;
    }
    
    int count = 0;
    for (int i = 0; i < str.length(); i++)
    {
        char ch = str[i];
        string nstr = str.substr(0, i) + str.substr(i + 1);
        count += permutation_01(nstr, ans + ch);
    }
    return count;
}

int permutation_02(string str, string ans)
{
    if (str.length() == 0)
    {
        cout << ans << "\n";
        return 1;
    }
    
    int count = 0;
    vector<bool> vis(26, false);
    for (int i = 0; i < str.length(); i++)
    {
        char ch = str[i];
        if (!vis[ch - 'a'] == true)
        {
            vis[ch - 'a'] = true;
            string nstr = str.substr(0, i) + str.substr(i + 1);
            count += permutation_02(nstr, ans + ch);
        }
    }
    return count;
}

bool isSafe(int r, int c, vector<vector<int>> &board)
{
    if (r < 0 || c < 0 || r >= board[0].size() || c >= board[1].size() || board[r][c] == 1)
        return false;
    return true;
}

vector<vector<int>> dir = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
vector<string> dir_path = {"L", "R", "U", "D"};
int jump = 1;
int floodfill(vector<vector<int>> &board, int sr, int sc, int er, int ec, string ans)
{
    if (sr == er && sc == ec)
    {
        cout << ans << "\n";
        return 1;
    }
    
    board[sr][sc] = 1; // mark yourself
    int count = 0;
    
    for (int d = 0; d < dir.size(); d++)
    {
        int nsr = sr + jump * dir[d][0];
        int nsc = sc + jump * dir[d][1];
        
        if (isSafe(nsr, nsc, board))
        {
            count += floodfill(board, nsr, nsc, er, ec, ans + dir_path[d]);
        }
    }
    
    board[sr][sc] = 0;  // unmark yourself
    return count;
}

int combination(int totalMembers, int memebers,string ans)
{
    if (memebers==totalMembers) {
        cout<<ans<<"\n";
        return 1;
    }
    
    int count=0;
    for (int i=memebers; i<totalMembers; i++) {
        count+=combination(totalMembers, i+1, ans + " " + to_string(i));
    }
    return count;
}

int coinInfiniteCombination(vector<int> &coins,int idx,int target,string ans)
{
    if (target==0) {
        cout<<ans<<"\n";
        return 1;
    }
    int count=0;
    for (int i=idx; i<coins.size(); i++) {
        if (target>=coins[i]) {
            count+=coinInfiniteCombination(coins, i, target-coins[i], ans + " " + to_string(coins[i]));
        }
    }
    return count;
}

// Infinite coins
int coinInfinitePermutation_01(vector<int> &coins,int target,string ans)
{
    if (target==0) {
        cout<<ans<<"\n";
        return 1;
    }
    int count=0;
    for (int i=0; i<coins.size(); i++) {
        if (target>=coins[i]) {
            count+=coinInfinitePermutation_01(coins, target-coins[i], ans + " " + to_string(coins[i]));
        }
    }
    return count;
}

// Only one coin per denomination
int coinInfinitePermutation_02(vector<int> &coins,vector<bool> &vis,int target,string ans)
{
    if (target==0) {
        cout<<ans<<"\n";
        return 1;
    }
    int count=0;
    for (int i=0; i<coins.size(); i++) {
        if (target>=coins[i] && vis[i]==false) {
            vis[i]=true;
            count+=coinInfinitePermutation_02(coins,vis,target-coins[i], ans + " " + to_string(coins[i]));
            vis[i]=false;
        }
    }
    return count;
}

int queenCombination(vector<bool> &boxes,int bn,int qpsf, int tnq,string ans)
{
    if (qpsf==tnq) {
        cout<<ans<<"\n";
        return 1;
    }
    int count=0;
    for (int i=bn; i<boxes.size(); i++) {
        count+=queenCombination(boxes, i+1,qpsf+1, tnq,
                                ans + "b" + to_string(i) + "q" + to_string(qpsf) + " " );
    }
    return count;
}

int queenPermutation(vector<bool> &boxes,int qpsf, int tnq,string ans)
{
    if (qpsf==tnq) {
        cout<<ans<<"\n";
        return 1;
    }
    int count=0;
    for (int i=0; i<boxes.size(); i++) {
        if (boxes[i]==false) {
            boxes[i]=true;
            count+=queenPermutation(boxes, qpsf+1, tnq,
                                    ans + "b" + to_string(i) + "q" + to_string(qpsf) + " " );
            boxes[i]=false;
        }
    }
    return count;
}

int queen2DComination(vector<vector<bool>> &boxes,int bn,int qpsf,int tnq,string ans)
{
    if (qpsf==tnq) {
        cout<<ans<<"\n";
        return 1;
    }
    int count=0;
    for (int i=bn; i<boxes.size() * boxes[0].size(); i++) {
        int r=i/boxes[0].size();
        int c=i%boxes[0].size();
        if (boxes[r][c]==false) {
            boxes[r][c]=true;
            count+=queen2DComination(boxes, i+1,qpsf+1, tnq,
                                      ans + "(" + to_string(r) + "," + to_string(c) + ") " );
            boxes[r][c]=false;
        }
    }
    return count;
}

int queen2DPermutation(vector<vector<bool>> &boxes,int qpsf,int tnq,string ans)
{
    if (qpsf==tnq) {
        cout<<ans<<"\n";
        return 1;
    }
    int count=0;
    for (int i=0; i<boxes.size() * boxes[0].size(); i++) {
        int r=i/boxes[0].size();
        int c=i%boxes[0].size();
        if (boxes[r][c]==false) {
            boxes[r][c]=true;
            count+=queen2DPermutation(boxes, qpsf+1, tnq,
                                     ans + "(" + to_string(r) + "," + to_string(c) + ") " );
            boxes[r][c]=false;
        }
    }
    return count;
}

vector<vector<int>> q_dir = {{0, -1}, {-1, 0}, {-1, -1}, {-1, 1}, {0, 1}, {1, 0}, {1, 1}, {1, -1}};

bool isQueenSafe_01(vector<vector<bool>> &boxes, int r, int c)
{
    
    for (int d = 0; d < q_dir.size(); d++)
    {
        for (int jump = 1; jump <= boxes.size(); jump++)
        {
            int nr = r + jump * q_dir[d][0];
            int nc = c + jump * q_dir[d][1];
            
            if (nr >= 0 && nc >= 0 && nr < boxes.size() && nc < boxes[0].size())
            {
                if (boxes[nr][nc])
                    return false;
            }
            else
                break;
        }
    }
    
    return true;
}

int NQueen_01(vector<vector<bool>> &boxes,int bn,int qpsf,int tnq,string ans)
{
    if (qpsf==tnq) {
        cout<<ans<<"\n";
        return 1;
    }
    int count=0;
    for (int i=bn; i<boxes.size() * boxes[0].size(); i++) {
        int r=i/boxes[0].size();
        int c=i%boxes[0].size();
        if (boxes[r][c]==false && isQueenSafe_01(boxes, r, c)) {
            boxes[r][c]=true;
            count+=NQueen_01(boxes, i+1,qpsf+1, tnq,
                          ans + "(" + to_string(r) + "," + to_string(c) + ") " );
            boxes[r][c]=false;
        }
    }
    return count;
}

int noOfRows=4;
int noOfColums=4;
int boxSize=noOfColums;

int rowBit=0;
int columnBit=0;
int diagBit=0;
int antiDiagBit=0;

vector<bool> row(noOfRows,false);
vector<bool> column(noOfColums,false);
vector<bool> diag(noOfRows + noOfColums -1,false);
vector<bool> antiDiag(noOfRows + noOfColums -1,false);
vector<vector<bool>> boxes(noOfRows,vector<bool>(noOfColums,false));

bool isQueenSafe_02(int r, int c)
{
    return !row[r] && !column[c] && !diag[r+c] && !antiDiag[r-c+ boxSize-1] ;
}

void markQueenInArray(int r,int c)
{
    row[r]=true;
    column[c]=true;
    diag[r+c]=true;
    antiDiag[r-c+ boxSize-1]=true;
}

void unMarkQueenInArray(int r,int c)
{
    row[r]=false;
    column[c]=false;
    diag[r+c]=false;
    antiDiag[r-c+ boxSize-1]=false;
}

int NQueen_02(vector<vector<bool>> &boxes,int bn,int qpsf,int tnq,string ans)
{
    if (qpsf==tnq) {
        cout<<ans<<"\n";
        return 1;
    }
    int count=0;
    for (int i=bn; i<boxes.size() * boxes[0].size(); i++) {
        int r=i/boxes[0].size();
        int c=i%boxes[0].size();
        if (isQueenSafe_02(r, c)) {
            // if(isQueenSafe_02(boxes, r, c)) { ... }
            markQueenInArray(r, c);
            count+=NQueen_02(boxes, i+1,qpsf+1, tnq,
                             ans + "(" + to_string(r) + "," + to_string(c) + ") " );
            unMarkQueenInArray(r, c);
        }
    }
    return count;
}

bool isQueenSafe_03(int r, int c)
{
    return (rowBit &(1<<r))==0 && (columnBit &(1<<c))==0 && (diagBit &(1<<(r+c)))==0 && (antiDiagBit &(1<<(r-c+boxSize-1)))==0 ;
}

void markUnmarkQueenBits(int r,int c)
{
    rowBit^=1<<r;
    columnBit^=1<<c;
    diagBit^=1<<(r+c);
    antiDiagBit^=1<<(r-c+ boxSize-1);
}

int NQueen_03(int bn,int qpsf,int tnq,string ans)
{
    if (qpsf==tnq) {
        cout<<ans<<"\n";
        return 1;
    }
    int count=0;
    for (int i=bn; i<noOfRows * noOfColums; i++) {
        int r=i/boxes[0].size();
        int c=i%boxes[0].size();
        if (isQueenSafe_03(r, c)) {
            markUnmarkQueenBits(r, c);
            count+=NQueen_03(i+1,qpsf+1, tnq,
                             ans + "(" + to_string(r) + "," + to_string(c) + ") " );
            markUnmarkQueenBits(r, c);
        }
    }
    return count;
}

int NQueen_04(int row,int tnq,string ans)
{
    if (tnq == 0) {
        cout<<ans<<"\n";
        return 1;
    }
    int count=0;
    for (int i=0; i<noOfColums; i++) {
        int r=row;
        int c=i%boxes[0].size();
        if (isQueenSafe_03(r, c)) {
            markUnmarkQueenBits(r, c);
            count+=NQueen_04(row+1,tnq-1,
                             ans + "(" + to_string(r) + "," + to_string(c) + ") " );
            markUnmarkQueenBits(r, c);
        }
    }
    return count;
}

int main()
{
//    vector<vector<int>> board(3, vector<int>(3, 0));
//    cout << floodfill(board, 0, 0, 2, 2, "");
//    cout<<combination(5, 0, "")<<"\n";
//    vector<int> coins={2,3,5,7};
//    cout<<coinInfiniteCombination(coins, 0, 10, "")<<"\n";
//    cout<<coinInfinitePermutation_01(coins, 10, "")<<"\n";
//    vector<bool> vis(4,false);
//    cout<<coinInfinitePermutation_02(coins, vis, 10, "")<<"\n";
    
    /**
    vector<vector<bool>> boxes(noOfRows,vector<bool>(noOfColums,false));
    cout<<NQueen_02(boxes, 0, 0, 4, "");
    **/
    
//    cout<<NQueen_03(0, 0, 4, "");
    
    cout<<NQueen_04(0,4,"");
    
    return 0;
}
