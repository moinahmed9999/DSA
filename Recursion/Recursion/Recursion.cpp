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

vector<vector<int>> dir_01 = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
vector<string> dir_path_01 = {"L", "R", "U", "D"};

//  Four directions (L, R, U, D)
int floodfill_01(vector<vector<int>> &board, int sr, int sc, int er, int ec, string ans)
{
    if (sr == er && sc == ec)
    {
        cout << ans << "\n";
        return 1;
    }
    
    board[sr][sc] = 1; // mark yourself
    int count = 0;
    int jump = 1;
    
    for (int d = 0; d < dir_01.size(); d++)
    {
        int nsr = sr + jump * dir_01[d][0];
        int nsc = sc + jump * dir_01[d][1];
        
        if (isSafe(nsr, nsc, board))
        {
            count += floodfill_01(board, nsr, nsc, er, ec, ans + dir_path_01[d]);
        }
    }
    
    board[sr][sc] = 0;  // unmark yourself
    return count;
}

vector<vector<int>> dir_02 = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1,1}, {-1,-1}, {1,-1}, {1,1}};
vector<string> dir_path_02 = {"L", "R", "U", "D", "DI", "DII", "DIII", "DIV"};

//  Eight directions (L, R, U, D, DI, DII, DIII, DIV)
int floodfill_02(vector<vector<int>> &board, int sr, int sc, int er, int ec, string ans)
{
    if (sr == er && sc == ec)
    {
        cout << ans << "\n";
        return 1;
    }
    
    board[sr][sc] = 1; // mark yourself
    int count = 0;
    int jump = 1;
    
    for (int d = 0; d < dir_02.size(); d++)
    {
        int nsr = sr + jump * dir_02[d][0];
        int nsc = sc + jump * dir_02[d][1];
        
        if (isSafe(nsr, nsc, board))
        {
            count += floodfill_02(board, nsr, nsc, er, ec, ans + dir_path_02[d]);
        }
    }
    
    board[sr][sc] = 0;  // unmark yourself
    return count;
}

vector<vector<int>> mazeDir={{0,1},{1,0},{1,1}};
vector<string> mazeDir_path={"H","V","D"};

//  only one jump
int mazePath_01(vector<vector<int>> &board, int sr, int sc, int er, int ec, string ans)
{
    if (sr==er && sc==ec) {
        cout<<ans<<"\n";
        return 1;
    }
    board[sr][sc]=1;
    int count=0;
    int jump = 1;
    
    for (int i=0; i<mazeDir.size(); i++) {
        int nsr= sr + jump*mazeDir[i][0];
        int nsc=sc + jump * mazeDir[i][1];
        
        if (isSafe(nsr, nsc, board)) {
            count+=mazePath_01(board, nsr, nsc, er, ec, ans + mazeDir_path[i]);
        }
    }
    
    board[sr][sc]=0;
    return count;
}

//  multiple jumps
int mazePath_02(vector<vector<int>> &board, int sr, int sc, int er, int ec, string ans)
{
    if (sr==er && sc==ec) {
        cout<<ans<<"\n";
        return 1;
    }
    int jump=er;
    board[sr][sc]=1;
    int count=0;
    for (int i=0; i<mazeDir.size(); i++) {
        for (int j=1; j<=jump; j++) {
            int nsr= sr + j*mazeDir[i][0];
            int nsc=sc + j * mazeDir[i][1];
            
            if (isSafe(nsr, nsc, board)) {
                count+=mazePath_02(board, nsr, nsc, er, ec, ans+mazeDir_path[i]+to_string(j)+" ");
            }
        }
    }
    
    board[sr][sc]=0;
    return count;
}

bool isSafeRat(int r, int c, vector<vector<int>> &board)
{
    if (r < 0 || c < 0 || r >= board.size() || c >= board[1].size() || board[r][c] == 1)
        return false;
    return true;
}

vector<vector<int>> ratMazeDir={{0,1},{1,0}};
vector<string> ratMazeDir_path={"F","D"};   // Forward, Down

//  1 means obstacle and means empty space
int ratInMaze(vector<vector<int>> &board, int sr, int sc, int er, int ec, string ans)
{
    if (sr==er && sc==ec) {
        cout<<ans<<"\n";
        return 1;
    }
    
    board[sr][sc]=1;
    int count=0;
    
    for (int i=0; i< ratMazeDir.size(); i++) {
        int nsr = sr + ratMazeDir[i][0];
        int nsc = sc + ratMazeDir[i][1];
        
        if (isSafeRat(nsr, nsc, board)) {
            count+=ratInMaze(board, nsr, nsc, er, ec, ans + ratMazeDir_path[i]);
        }
    }
    
    board[sr][sc]=0;
    return count;
}

vector<vector<int>> rottenOrange;

bool isSageOrange(int r,int c,vector<vector<int>> oranges)
{
    if (r<0 || r>=oranges.size() || c<0 || c>=oranges[0].size() || oranges[r][c]==0 || oranges[r][c]==2) {
        return false;
    }
    return true;
}

vector<vector<int>> rottenOrangeDir = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
vector<string> rottenOrangeDir_path = {"L", "R", "U", "D"};

int rottenOranges(vector<vector<int>> &oranges,int idx)
{
    int count=0;
    int size=(int)rottenOrange.size();
    for (int i=idx; i<size; i++) {
        for (int j=0; j<rottenOrangeDir.size(); j++) {
            
            int r=rottenOrange[i][0] + rottenOrangeDir[j][0];
            int c=rottenOrange[i][1] + rottenOrangeDir[j][1];
            
            if (isSageOrange(r,c,oranges)) {
                oranges[r][c]=2;
                vector<int> x={r,c};
                rottenOrange.push_back(x);
            }
        }
    }
    
    if (rottenOrange.size()>size) {
        count++;
        count+=rottenOranges(oranges,size);
    }
    
    int flag=0;
    for (int i=0; i<oranges.size(); i++) {
        for (int j=0; j<oranges[0].size(); j++) {
            if (oranges[i][j]==1) {
                flag++;
                break;
            }
        }
    }

    if (flag==0) {
        return count;
    }
    return -1;
//    return count;
    
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
    bool rowBool=(rowBit &(1<<r))==0;
    bool columnBool=(columnBit &(1<<c))==0;
    bool diagBool=(diagBit &(1<<(r+c)))==0;
    bool antiDiagBool=(antiDiagBit &(1<<(r-c+boxSize-1)))==0;
    bool ans=rowBool && columnBool && diagBool && antiDiagBool;
    return ans;
    //    return (rowBit &(1<<r))==0 && (columnBit &(1<<c))==0 && (diagBit &(1<<(r+c)))==0 && (antiDiagBit &(1<<(r-c+boxSize-1)))==0 ;
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
                             ans + "(" + to_string(r)+","+to_string(c) + ") " );
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
        if (isQueenSafe_03(row, i)) {
            markUnmarkQueenBits(row, i);
            count+=NQueen_04(row+1,tnq-1,
                             ans + "(" + to_string(row)+","+to_string(i) + ") " );
            markUnmarkQueenBits(row, i);
        }
    }
    return count;
}

vector<vector<int>> board=
    {{3, 0, 6, 5, 0, 8, 4, 0, 0},
    {5, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 7, 0, 0, 0, 0, 3, 1},
    {0, 0, 3, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0},
    {1, 3, 0, 0, 0, 0, 2, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 7, 4},
    {0, 0, 5, 2, 0, 6, 3, 0, 0}};
vector<int> rows(9,0);
vector<int> columns(9,0);
vector<vector<int>> mat(3,vector<int>(3,0));

void sudoku()
{
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            if (board[i][j]!=0) {
                int mask=1<<board[i][j];
                if ((rows[i]&mask)==0 && (columns[j]&mask)==0 && (mat[i/3][j/3]&mask)==0)
                    // if that bit is off
                {
                    rows[i] |=mask;     // turn on that bit
                    columns[j] |=mask;
                    mat[i/3][j/3] |=mask;
                }
                else    // invalid board
                    return;
            }
        }
    }
}

int sudoku_01(int bno)
{
    if (bno==81)
    {
        for (vector<int> boardRow: board)
        {
            for (int element: boardRow) {
                cout<<element<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
        return 1;
    }
    
    int count=0;
    
    int i=bno/9;
    int j=bno%9;
    
    if (board[i][j]==0)
    {
        for (int num=1; num<=9; num++)
        {
            int mask=1<<num;
            if ((rows[i]&mask)==0 && (columns[j]&mask)==0 && (mat[i/3][j/3]&mask)==0)
            {
                //  turn on the bit
                rows[i] ^=mask;
                columns[j] ^=mask;
                mat[i/3][j/3] ^=mask;
                
                board[i][j]=num;
                
                count+=sudoku_01(bno+1);
                
                //  turn off the bit
                rows[i] ^=mask;
                columns[j] ^=mask;
                mat[i/3][j/3] ^=mask;
                
                board[i][j]=0;
                
            }
        }
    }
    else
        count+=sudoku_01(bno+1);
    
    return count;
}

string str1="send";
string str2="more";
string str3="money";
string uniqueStr;
vector<int> mapping(26,-1);
vector<bool> isTaken(10,false);

void crypto()
{
    uniqueStr=str1+str2+str3;
    
    vector<int> freq(26,0);
    
    for (int i=0; i<uniqueStr.size(); i++) {
        freq[uniqueStr[i]-'a']++;
    }
    uniqueStr="";
    for (int i=0; i<26; i++) {
        if (freq[i]>0) {
            uniqueStr+=(char) (i + 'a');
        }
    }
}

int stringToNum(string str)
{
    int x=0;
    for (int i=0; i<str.size(); i++) {
        int idx=str[i] - 'a';
        x=x*10+mapping[idx];
    }
    return x;
}

void printCrypto()
{
    for (int i=0; i<uniqueStr.size(); i++) {
        int idx=uniqueStr[i] - 'a';
        cout<<uniqueStr[i]<<"="<<mapping[idx]<<",";
    }
    cout<<"\n";
}

int crypto_01(int idx)
{
    if (idx==uniqueStr.length()) {
        int num1=stringToNum(str1);
        int num2=stringToNum(str2);
        int num3=stringToNum(str3);
        
        if (num1 + num2 == num3) {
            printCrypto();
            return 1;
        }
        
        else {
            return 0;
        }
    }
    
    int count =0;
    for (int num=0; num<=9; num++) {
        if (!isTaken[num]) {
            mapping[uniqueStr[idx] - 'a']=num;
            isTaken[num]=true;
            count+=crypto_01(idx+1);
            mapping[uniqueStr[idx] - 'a']=-1;
            isTaken[num]=false;
        }
    }
    return count;
}

bool canPlaceWordH(vector<vector<char>> &board, int x, int y, string word)
{
    if (word.size()>board[0].size()) {
        return false;
    }else if (y==0 && y+word.size()<board[0].size() && board[x][y+word.size()]=='-')
        return false;
    else if (y+word.size()==board[0].size() && board[x][y-1]=='-')
        return false;
    else if ((y-1>=0 && board[x][y-1]=='-') ||
             (y+word.size()<board[0].size() && board[x][y+word.size()]=='-'))
        return false;
    
    for (int i=0; i<word.size(); i++) {
        if (board[x][y+i]!='-' && board[x][y+i]!=word[i]) {
            return false;
        }
    }
    return true;
}

bool canPlaceWordV(vector<vector<char>> &board, int x, int y, string word)
{
    if (word.size()>board.size()) {
        return false;
    }else if (x==0 && x+word.size()<board.size() && board[x+word.size()][y]=='-')
        return false;
    else if (x+word.size()==board.size() && board[x-1][y]=='-')
        return false;
    else if ((x-1>=0 &&board[x-1][y]=='-' ) ||
             (x+word.size()<board.size() && board[x+word.size()][y]=='-'))
        return false;
    
    for (int i=0; i<word.size(); i++) {
        if (board[x+i][y]!='-' && board[x+i][y]!=word[i]) {
            return false;
        }
    }
    return true;
}

vector<bool> placeWordH(vector<vector<char>> &board, int x, int y, string word)
{
    vector<bool> loc(word.size(),false);
    for (int i=0; i<word.size(); i++) {
        if (board[x][y+i]=='-') {
            board[x][y+i]=word[i];
            loc[i]=true;
        }
    }
    return loc;
}

vector<bool> placeWordV(vector<vector<char>> &board, int x, int y, string word)
{
    vector<bool> loc(word.size(),false);
    for (int i=0; i<word.size(); i++) {
        if (board[x+i][y]=='-') {
            board[x+i][y]=word[i];
            loc[i]=true;
        }
    }
    return loc;
}

void unplaceWordH(vector<vector<char>> &board, int x, int y,vector<bool> &loc)
{
    for (int i=0; i<loc.size(); i++) {
        if (loc[i]) {
            board[x][y+i]='-';
        }
    }
}

void unplaceWordV(vector<vector<char>> &board, int x, int y,vector<bool> &loc)
{
    for (int i=0; i<loc.size(); i++) {
        if (loc[i]) {
            board[x+i][y]='-';
        }
    }
}

int crossword(vector<vector<char>> &board, int idx, vector<string> words)
{
    if (idx==words.size()) {
        //  Print the board
        for (vector<char> boardRow: board) {
            for (char element: boardRow) {
                cout<<element<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
        
        return 1;
    }
    
    int count=0;
    
    for (int i=0; i<board.size(); i++) {
        for (int j=0; j<board[0].size(); j++) {
            if (board[i][j]=='-' || board[i][j]==words[idx][0]) {
                if (canPlaceWordH(board, i, j, words[idx])) {
                    vector<bool> loc=placeWordH(board, i, j, words[idx]);
                    count+=crossword(board, idx+1, words);
                    unplaceWordH(board, i, j,loc);
                }
                
                if (canPlaceWordV(board, i, j, words[idx])) {
                    vector<bool> loc=placeWordV(board, i, j, words[idx]);
                    count+=crossword(board, idx+1, words);
                    unplaceWordV(board, i, j,loc);
                }
            }
        }
    }
    
    return count;

}

bool isValidWord(string str,vector<string> dictionary)
{
    for (int i=0; i<dictionary.size(); i++) {
        if (str==dictionary[i]) {
            return true;
        }
    }
    return false;
}

int wordBreak(string str, string ans,vector<string> dictionary)
{
    if (str.size()==0) {
        cout<<ans<<"\n";
        return 1;
    }
    
    int count=0;
    
    for (int i=0; i<str.size(); i++) {
        string nans=str.substr(0,i+1);
        if (isValidWord(nans, dictionary)) {
            string nstr=str.substr(i+1);
            count+=wordBreak(nstr, ans + nans + " ", dictionary);
        }
    }
    
    return count;
}

void findLeftRight(int &left, int &right,vector<int> &arr,vector<bool> &isTaken)
{
    int leftPos=left,rightPos=right;
    while (leftPos-1>=0) {
        if (!isTaken[leftPos-1]) {
            left=arr[leftPos-1];
            break;
        }
        leftPos--;
    }
    if (leftPos == 0) {
        left=1;
    }
    
    while (rightPos+1<arr.size()) {
        if (!isTaken[rightPos+1]) {
            right=arr[rightPos+1];
            break;
        }
        rightPos++;
    }
    if (rightPos == arr.size()-1) {
        right=1;
    }
}

int burstBalloon_01(vector<int> &arr,vector<bool> &isTaken)
{
    int maxAns=INT_MIN;
    int flag=0;
    for (int i=0; i<arr.size(); i++) {
        if (!isTaken[i]) {
            flag++;
            isTaken[i]=true;
            
            int left=i,right=i;
            
            findLeftRight(left,right,arr, isTaken);
            
            int myAns=left*(arr[i])*right;
            
            int ans=burstBalloon_01(arr, isTaken);
            
            maxAns=max(maxAns, myAns + ans);
            
            isTaken[i]=false;
        }
    }
    
    return flag>0?maxAns:0;
}

int main()
{
//    vector<vector<int>> board(4, vector<int>(4, 0));
//    cout << floodfill_01(board, 0, 0, 3, 3, "");
//    cout << floodfill_02(board, 0, 0, 3, 3, "");
//    cout<<mazePath_01(board, 0, 0, 3, 3, "");
//    cout<<mazePath_02(board, 0, 0, 3, 3, "");
//    board = { { 0, 1, 1, 1 },
//              { 0, 0, 1, 0 },
//              { 1, 0, 1, 1 },
//              { 0, 0, 0, 0 } };
//    cout<<ratInMaze(board, 0, 0, 3, 3, "");
    
    
//    vector<vector<int>> oranges = { {2, 1, 0, 2, 1},
//                                    {1, 0, 1, 2, 1},
//                                    {1, 0, 0, 2, 1}};
//
//    for (int i=0; i<oranges.size(); i++) {
//        for (int j=0; j<oranges[0].size(); j++) {
//            if (oranges[i][j]==2) {
//                vector<int> x={i,j};
//                rottenOrange.push_back(x);
//            }
//        }
//    }
//    cout<<rottenOranges(oranges,0);
    
    
//        cout<<combination(5, 0, "")<<"\n";
//        vector<int> coins={2,3,5,7};
//        cout<<coinInfiniteCombination(coins, 0, 10, "")<<"\n";
//        cout<<coinInfinitePermutation_01(coins, 10, "")<<"\n";
//        vector<bool> vis(4,false);
//        cout<<coinInfinitePermutation_02(coins, vis, 10, "")<<"\n";
//
//    /**
//     vector<vector<bool>> boxes(noOfRows,vector<bool>(noOfColums,false));
//     cout<<NQueen_02(boxes, 0, 0, 4, "");
//     **/
//
//        cout<<NQueen_03(0, 0, noOfRows, "");
//
//        cout<<NQueen_04(0,noOfRows,"");
    
//    sudoku();   // initialize all bits acc to pre-filled sudoku board
//    cout<<sudoku_01(0);
    
//    crypto();
//    cout<<crypto_01(0);

//    string str="ilikesamsungmobile";
//    vector<string> dictionary ={"i","like","sam","sung","samsung","mobile"};
//
//    cout<<wordBreak(str, "", dictionary);
    
//    vector<vector<char>> crosswordBoard = {
//        {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
//        {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
//        {'+', '-', '-', '-', '-', '-', '-', '-', '+', '+'},
//        {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
//        {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
//        {'+', '-', '-', '-', '-', '-', '-', '+', '+', '+'},
//        {'+', '-', '+', '+', '+', '-', '+', '+', '+', '+'},
//        {'+', '+', '+', '+', '+', '-', '+', '+', '+', '+'},
//        {'+', '+', '+', '+', '+', '-', '+', '+', '+', '+'},
//        {'+', '+', '+', '+', '+', '+', '+', '+', '+', '+'}};
//
//    vector<string> words = {"agra", "norway", "england", "gwalior"};
//    cout << crossword(crosswordBoard, 0,words) << "\n";
    
    vector<int> arr={3,1,5,8};
    vector<bool> isTakenBalloon(arr.size(),false);
    cout<<burstBalloon_01(arr, isTakenBalloon)<<"\n";
    return 0;
}
