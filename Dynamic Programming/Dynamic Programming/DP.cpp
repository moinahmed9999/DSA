//
//  DP.cpp
//  Dynamic Programming
//
//  Created by Noor Mohd on 10/05/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include <bits/stdc++.h>
#include <vector>

using namespace std;

// Fibonacci ------------------------------------------------

int fibonacciMemo(int n, vector<int>& dp) {
    if (n<=1) {
        return dp[n]=n;
    }
    if (dp[n!=0]) {
        return dp[n];
    }
    return dp[n]=fibonacciMemo(n-1,dp) + fibonacciMemo(n-2,dp);
}

int fibonacciTab(int n, vector<int>& dp) {
    for (int i=0; i<n+1; i++) {
        if(i<=1) {
            dp[i]=i;
            continue;
        }
        dp[i]=dp[i-1]+dp[i-2];
    }
    return dp[n];
}

void fibonacci() {
    int n=10;
    vector<int> dp(n+1,0);
//    cout<<fibonacciTab(n, dp)<<"\n";
//    cout<<fibonacciMemo(n, dp)<<"\n";
}


// UniquePaths ------------------------------------------------
/*
 No of ways to reach from top left to bottom down of a 2D matrix
 */

int uniquePaths2MovesRec(int sr, int sc, int m/*colums*/, int n/*rows*/) {
    if(sr==n-1 && sc==m-1)  return 1;
    
    int rightWays=0,downWays=0;
    
    // right move
    if(sc+1<m) {
        rightWays =uniquePaths2MovesRec(sr,sc+1,m,n);
    }
    
    // down move
    if(sr+1<n) {
        downWays =uniquePaths2MovesRec(sr+1,sc,m,n);
    }
    
    return rightWays+downWays;
}

int uniquePaths2MovesMemo(int sr, int sc, int m/*colums*/, int n/*rows*/,
                          vector<vector<int>>& dp) {
    if(sr==n-1 && sc==m-1)  return dp[sr][sc]=1;
    
    if (dp[sr][sc]!=0) {
        return dp[sr][sc];
    }
    
    int rightWays=0,downWays=0;
    
    // right move
    if(sc+1<m) {
        rightWays =uniquePaths2MovesMemo(sr,sc+1,m,n,dp);
    }
    
    // down move
    if(sr+1<n) {
        downWays =uniquePaths2MovesMemo(sr+1,sc,m,n,dp);
    }
    
    return dp[sr][sc]=rightWays+downWays;
}

int uniquePaths2MovesTab(int m/*colums*/, int n/*rows*/,
                          vector<vector<int>>& dp) {
    for (int i=n-1; i>=0; i--) {
        for (int j=m-1; j>=0; j--) {
            if(i==n-1 && j==m-1) {
                dp[i][j]=1;
                continue;
            }
            
            // right move
            if(j+1<m) {
                dp[i][j]+=dp[i][j+1];
            }
            
            // down move
            if(i+1<n) {
                dp[i][j]+=dp[i+1][j];
            }
        }
    }
    return dp[0][0];
}

int uniquePaths2MovesMultiJumpsMemo(int sr, int sc, int m/*colums*/, int n/*rows*/,
                          vector<vector<int>>& dp) {
    if(sr==n-1 && sc==m-1)  return dp[sr][sc]=1;
    
    if (dp[sr][sc]!=0) {
        return dp[sr][sc];
    }
    
    int rightWays=0,downWays=0;
    
    // right move
    for (int jumps=1; sc+jumps<m; jumps++) {
        rightWays +=uniquePaths2MovesMemo(sr,sc+jumps,m,n,dp);
    }
    
    // down move
    for (int jumps=1; sr+jumps<n; jumps++) {
        downWays +=uniquePaths2MovesMemo(sr+jumps,sc,m,n,dp);
    }
    
    return dp[sr][sc]=rightWays+downWays;
}

int uniquePaths2MovesMultiJumpsTab(int m/*colums*/, int n/*rows*/,
                         vector<vector<int>>& dp) {
    for (int i=n-1; i>=0; i--) {
        for (int j=m-1; j>=0; j--) {
            if(i==n-1 && j==m-1) {
                dp[i][j]=1;
                continue;
            }
            
            // right moves
            for (int jump=1; j+jump<m; jump++) {
                dp[i][j]+=dp[i][j+jump];
            }
            
            // left moves
            for (int jump=1; i+jump<n; jump++) {
                dp[i][j]+=dp[i+jump][j];
            }
        }
    }
    return dp[0][0];
}

// For 3 moves, just add one more call for the diagonal move

void uniquePaths() {
    
}

// CountBooardPath ------------------------------------------------
/*
 No of ways to reach from initial position (0) to end (n-1) of a board
 of length n, using a dice with faces 1 to 6, by rolling the dice
 */

int countBoardPathRec(int n, int idx) {
    if(idx==n-1) return 1;
    int count=0,dice=1;
    while(dice<=6 && idx+dice<n) {
        count+=countBoardPathRec(n,idx+dice);
        dice++;
    }
    return count;
}

int countBoardPathMemo(int n, int idx, vector<int>& dp) {
    if(idx==n-1) return dp[idx]=1;
    int dice=1;
    if (dp[idx]!=0) {
        return dp[idx];
    }
    while(dice<=6 && idx+dice<n) {
        dp[idx]+=countBoardPathMemo(n,idx+dice,dp);
        dice++;
    }
    return dp[idx];
}

int countBoardPathTab(int n, vector<int>& dp) {
    for (int i=n-1; i>=0; i--) {
        if (i==n-1) {
            dp[i]=1;
            continue;
        }
        int dice=1;
        while(dice<=6 && i+dice<n) {
            dp[i]+=dp[i+dice];
            dice++;
        }
    }
    return dp[0];
}

void countBoardPath() {
//    cout<<countBoardPathRec(11, 0)<<"\n";
    vector<int> dp(10,0);
//    cout<<countBoardPathMemo(11, 0, dp)<<"\n";
//    cout<<countBoardPathTab(11, dp)<<"\n";
}

// ClimbingStairs and MinCostCLimbingStairs and MinimumPathSun and GoldMine------------------

// LC 70
int climbStairs(int n) {
    if(n<=2) return n;
    vector<int> dp(n,0);
    dp[n-1]=1;
    dp[n-2]=2;
    for(int i=n-3;i>=0;i--) {
        dp[i]=dp[i+1]+dp[i+2];
    }
    return dp[0];
}

// LC 746
int minCostClimbingStairs(vector<int>& cost) {
    int n=(int) cost.size();
    vector<int> dp(n,0);
    for(int i=n-1;i>=0;i--) {
        if(i>=n-2) {
            dp[i]=cost[i];
            continue;
        }
        dp[i]=cost[i]+min(dp[i+1],dp[i+2]);
    }
    return min(dp[0],dp[1]);
}

// LC 64
int minPathSum(vector<vector<int>>& grid) {
    int n=(int) grid.size(), m=(int) grid[0].size();
    vector<vector<int>> dp(n, vector<int>(m,0));
    for(int i=n-1;i>=0;i--) {
        for(int j=m-1;j>=0;j--) {
            if(i==n-1 && j==m-1) {
                dp[i][j]=grid[i][j];
                continue;
            }
            if(i==n-1) dp[i][j]=grid[i][j]+dp[i][j+1];
            else if(j==m-1) dp[i][j]=grid[i][j]+dp[i+1][j];
            else dp[i][j]=grid[i][j]+ min(dp[i][j+1],dp[i+1][j]);
        }
    }
    return dp[0][0];
}

// GoldMineProblem - GFG
int goldMineProblem(vector<vector<int>>& matrix) {
    int n=(int) matrix.size(),m=(int) matrix[0].size();
    int Max;
    vector<vector<int>> dp(n,vector<int>(m));
    for(int j=m-1;j>=0;j--) {
        for(int i=0;i<n;i++) {
            if(j==m-1) {
                dp[i][j]=matrix[i][j];
                continue;
            }
            Max=0;
            if(i-1>=0) Max=max(Max,dp[i-1][j+1]);
            Max=max(Max,dp[i][j+1]);
            if(i+1<n) Max=max(Max,dp[i+1][j+1]);
            dp[i][j]=matrix[i][j]+Max;
        }
    }
    Max=0;
    for(int i=0;i<n;i++) {
        Max=max(Max,dp[i][0]);
    }
    return Max;
}

// NumberOfWays ---------------------------------------------

// NumberOfWaysToPairPeople - GFG
int numberOfWaysToPairPeople(int n) {
    vector<int> dp(n+1);
    for (int i=1; i<=n; i++) {
        if (i<=2) {
            dp[i]=i;
            continue;
        }
        dp[i]=dp[n-1]+(n-1)*dp[n-2];
    }
    return dp[n];
}

// NumberOfWaysToPartitionASetIntoKSubsets
int numberOfWaysToPartitionASetIntoKSubsetsRec(int n, int k) {
    if (k==1 || n==k) {
        return 1;
    }
    
    int oneSet = numberOfWaysToPartitionASetIntoKSubsetsRec(n-1,k-1);
    int joinOtherSet = numberOfWaysToPartitionASetIntoKSubsetsRec(n-1, k);
    
    return oneSet + k*joinOtherSet;
}

int numberOfWaysToPartitionASetIntoKSubsetsMemo(int n, int k, vector<vector<int>>& dp) {
    if (k==1 || n==k) {
        return dp[n][k]=1;
    }
    
    if (dp[n][k]!=0) {
        return dp[n][k];
    }
    
    int oneSet = numberOfWaysToPartitionASetIntoKSubsetsMemo(n-1,k-1, dp);
    int joinOtherSet = numberOfWaysToPartitionASetIntoKSubsetsMemo(n-1, k, dp);
    
    return dp[n][k]=oneSet + k*joinOtherSet;
}

int numberOfWaysToPartitionASetIntoKSubsetsTab(int n, int k, vector<vector<int>>& dp) {
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=k && j<=i; j++) {
            if (j==1 || i==j) {
                dp[i][j]=1;
                continue;
            }
            dp[i][j]=dp[i-1][j-1] + j*dp[i-1][j];
        }
    }
    return dp[n][k];
}

void numberOfWaysToPartitionASetIntoKSubsets() {
//    cout<<numberOfWaysToPartitionASetIntoKSubsetsRec(5, 3)<<"\n";
    int n=5,k=3;
    vector<vector<int>> dp(n+1, vector<int>(k+1,0));
//    cout<<numberOfWaysToPartitionASetIntoKSubsetsMemo(n, k, dp)<<"\n";
//    cout<<numberOfWaysToPartitionASetIntoKSubsetsTab(n, k, dp)<<"\n";
}

// String Problems -------------------------------------------

// IsPalindromicSubstring
/* gives a matrix telling if the string s.substr(i,j+1-i) is a palindrome or not */
void displayDp(vector<vector<bool>>& dp) {
    int n=(int) dp.size();
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cout<<dp[i][j]<<" ";
        }
        cout<<"\n";
    }
}

bool isPalindromicSubstringRecHelper(string s, int si, int ei) {
    if (si==ei) return true;
    if (s[si]!=s[ei]) return false;
    if (si+1==ei) return true;
    return isPalindromicSubstringRecHelper(s, si+1, ei-1);
}

void isPalindromicSubstringRec(string s, vector<vector<bool>>& dp) {
    int n=(int) s.size();
    for (int i=0; i<n; i++) {
        for (int j=i; j<n; j++) {
            dp[i][j]=isPalindromicSubstringRecHelper(s, i, j);
        }
    }
    displayDp(dp);
}

void isPalindromicSubstringTab(string s, vector<vector<bool>>& dp) {
    int n=(int) s.size();
    for (int gap=0; gap<n; gap++) {
        for (int i=0,j=gap; j<n; i++,j++) {
            if (gap==0) dp[i][j]=true;
            else if (gap==1 && s[i]==s[j]) dp[i][j]=true;
            else dp[i][j]=s[i]==s[j] && dp[i+1][j-1];
        }
    }
    displayDp(dp);
}

void isPalindromicSubstring() {
    string s = "abccbde";
    int n=(int) s.size();
    vector<vector<bool>> dp(n, vector<bool> (n, false));
//    isPalindromicSubstringRec(s, dp);
    isPalindromicSubstringTab(s, dp);
}

// PalindromicSubstring - LC 647
/* count how many palindromic substrings are there in the given string */
/* this is same as isPalindromicSubstring, we just have to count the number of substrings that have dp[i][j]==true */
int palindromicSubstringTab(string s, vector<vector<bool>>& dp) {
    int n=(int) s.size();
    int count=0;
    for (int gap=0; gap<n; gap++) {
        for (int i=0,j=gap; j<n; i++,j++) {
            if (gap==0) dp[i][j]=true;
            else if (gap==1 && s[i]==s[j]) dp[i][j]=true;
            else dp[i][j]=s[i]==s[j] && dp[i+1][j-1];
            count+=dp[i][j]?1:0;
        }
    }
    return count;
}

int countSubstrings(string s) { // Expand Around Center
    int n =(int) s.size();
    int count = n;
    for (int i = 0; i < n; i++) {
        int j = i - 1, k = i + 1;
        while (j >= 0 && k < n && s[j] == s[k]) {
            count++;
            j--;
            k++;
        }
        j = i - 1; k = i;
        while (j >= 0 && k < n && s[j] == s[k]) {
            count++;
            j--;
            k++;
        }
    }
    return count;
}

void palindromicSubstring() {
    string s = "abccbde";
    int n=(int) s.size();
    vector<vector<bool>> dp(n, vector<bool> (n, false));
//    cout<<palindromicSubstringTab(s, dp)<<"\n";
//    cout<<countSubstrings(s)<<"\n";
}

// LongestPalindromicSubstring - LC 5
/* given a string s, find the longest palindromic substring in s */
int longestPalindromicSubstringRec(string s,int si, int ei) {
    if (si==ei) {
        return 1;
    } else if(si+1==ei && s[si]==s[ei]) {
        return 2;
    }
    
    if(s[si]!=s[ei] || s[si+1]!=s[ei-1]) {
        int x=longestPalindromicSubstringRec(s, si, ei-1);
        int y=longestPalindromicSubstringRec(s, si+1, ei);
        return max(x,y);
    }
    return longestPalindromicSubstringRec(s, si+1, ei-1) + 2;
}

int longestPalindromicSubstringTab(string s) {
    int n=(int) s.size();
    vector<vector<int>> dp(n,vector<int> (n,0));
    for (int gap=0; gap<n; gap++) {
        for (int i=0, j=gap; j<n; i++,j++) {
            if (i==j) {
                dp[i][j]=1;
                continue;
            } else if(gap==1 && s[i]==s[j]) {
                dp[i][j]=2;
                continue;
            }
            if(s[i]!=s[j] || s[i+1]!=s[j-1]) {
                dp[i][j]=max(dp[i][j-1], dp[i+1][j]);
            } else {
                dp[i][j]=dp[i+1][j-1] + 2;
            }
        }
    }
    return dp[0][n-1];
}

string longestPalindromicSubstringTabString(string s) {
    /* if a substring ia not a palindrome then dp[i][j]=0 else i will store the length of that substring */
    int n=(int) s.size();
    int maxLen=0, maxL=-1,maxR=-1;
    vector<vector<int>> dp(n,vector<int> (n,0));
    for (int gap=0; gap<n; gap++) {
        for (int i=0, j=gap; j<n; i++,j++) {
            if (i==j) {
                dp[i][j]=1;
            } else if(gap==1 && s[i]==s[j]) {
                dp[i][j]=2;
            } else if (s[i]==s[j] && dp[i+1][j-1]!=0) {
                dp[i][j]=dp[i+1][j-1] + 2;
            }
            if(maxLen < dp[i][j]) {
                maxLen = dp[i][j];
                maxL=i;
                maxR=j;
            }
        }
    }
    return s.substr(maxL, maxLen);
}

int expandAroundCenter (string &s, int left, int right) {   // O(n^2) time & O(1) space
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1;
}

string longestPalindrome(string s) {
    if (s.size()==0) return s;
    int max_len = INT_MIN;
    int start = 0, end = 0;
    for (int i = 0; i < s.size(); i++) {
        int len1 = expandAroundCenter (s, i, i);
        int len2 = expandAroundCenter (s, i, i+1);
        int len = max (len1, len2);
        if (len > max_len) {
            start = i - (len-1)/2;
            end = i + len/2;
            max_len = len;
        }
    }
    
    return (s.substr(start, max_len));
}

void longestPalindromicSubstring() {
    string s="aaaabbaa";
//    int n=(int) s.size();
//    cout<<longestPalindromicSubstringRec(s, 0, n-1)<<"\n";
//    cout<<longestPalindromicSubstringTab(s)<<"\n";
    cout<<longestPalindromicSubstringTabString(s)<<"\n";
}

// LongestPalindromicSubsequence - LC 516
/* given a string s, find the longest palindromic subsequence in s */
// TODO return the string not the length

int longestPalindromicSubsequenceRec(string s, int si, int ei) {
    if (si==ei) {
        return 1;
    }
    if (si+1==ei && s[si]==s[ei]) {
        return 2;
    }
    if (s[si]!=s[ei]) {
        int x=longestPalindromicSubsequenceRec(s, si, ei-1);
        int y=longestPalindromicSubsequenceRec(s, si+1, ei);
        
        return max(x,y);
    }
    return longestPalindromicSubsequenceRec(s, si+1, ei-1) + 2;
}

int longestPalindromicSubsequenceMemo(string s, int si, int ei, vector<vector<int>>& dp) {
    if (si==ei) {
        return dp[si][ei]=1;
    }
    if (si+1==ei && s[si]==s[ei]) {
        return dp[si][ei]=2;
    }
    if (dp[si][ei]!=0) {
        return dp[si][ei];
    }
    if (s[si]!=s[ei]) {
        int x=longestPalindromicSubsequenceMemo(s, si, ei-1, dp);
        int y=longestPalindromicSubsequenceMemo(s, si+1, ei, dp);
        
        return dp[si][ei]=max(x,y);
    }
    return dp[si][ei]=longestPalindromicSubsequenceMemo(s, si+1, ei-1, dp) + 2;
}

int longestPalindromicSubsequenceTab(string s) {
    int n=(int) s.size();
    vector<vector<int>> dp(n,vector<int> (n,0));
    for (int gap=0; gap<n; gap++) {
        for (int i=0,j=gap; j<n; i++, j++) {
            if (i==j) {
                dp[i][j]=1;
            } else if(s[i]!=s[j]) {
                dp[i][j]=max(dp[i][j-1], dp[i+1][j]);
            } else {
                dp[i][j]=dp[i+1][j-1]+2;
            }
        }
    }
    return dp[0][n-1];
}

void longestPalindromicSubsequence() {
    string s="aaaabbaa";
    int n=(int) s.size();
    vector<vector<int>> dp(n, vector<int>(n,0));
//    cout<<longestPalindromicSubsequenceRec(s, 0, n-1)<<"\n";
//    cout<<longestPalindromicSubsequenceMemo(s, 0, n-1, dp)<<"\n";
    cout<<longestPalindromicSubsequenceTab(s)<<"\n";
}

// Count(All/Distinct)PalindromicSubsequence
/* count how many palindromic subsequences are there in the given string */
int countPalindromicSubsequences(string s) {
    int n=(int) s.size();
    vector<vector<int>> dp(n,vector<int> (n,0));
    for(int gap=0;gap<n;gap++) {
        for(int i=0,j=gap; j<n; i++, j++) {
            if(i==j) dp[i][j]=1;
            else if(gap==1 && s[i]==s[j]) dp[i][j]=3;
            else if(s[i]!=s[j]) dp[i][j]=dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1];
            else dp[i][j]=dp[i][j-1] + dp[i+1][j] + 1;
        }
    }
    return dp[0][n-1];
}

int countDistinctPalindromicSubsequences(string s) {
    int m=1000000007;
    int n=(int) s.size();
    vector<vector<int>> dp(n,vector<int> (n,0));
    for(int gap=0;gap<n;gap++) {
        for(int i=0,j=gap; j<n; i++, j++) {
            if(gap<=1) dp[i][j]=gap+1;
            else if(s[i]!=s[j]) dp[i][j]=dp[i][j-1]%m + dp[i+1][j]%m - dp[i+1][j-1];
            else {
                // x  __  __  __  __  __  __  __  x
                // i  i+1                     j-1 j
                int l=i+1, r=j-1;
                while(l<=r && s[l]!=s[i]) l++;
                while(l<=r && s[r]!=s[i]) r--;
                if(l<r) // more than one x in x____x
                    dp[i][j]=2*dp[i+1][j-1] - dp[l+1][r-1];
                else if(l==r) dp[i][j]=2*dp[i+1][j-1] + 1; // one x in x____x
                else dp[i][j]=2*dp[i+1][j-1] + 2; // no x in x____x
            }
            dp[i][j]=dp[i][j]<0?dp[i][j]+m : dp[i][j]%m;
        }
    }
    return dp[0][n-1];
}

void countPalindromicSubsequences() {
    string s="cbabc";
//    cout<<countPalindromicSubsequences(s)<<"\n";
    cout<<countDistinctPalindromicSubsequences(s)<<"\n";
}

int longestCommonSubstringTab(string x, string y) {
    int n=(int) x.size(),m=(int) y.size();
    vector<vector<int>> dp(n+1, vector<int> (m+1,0));
    int ans=0;
    for(int i=n-1;i>=0;i--) {
        for(int j=m-1;j>=0;j--) {
            if(x[i]==y[j]) {
                dp[i][j]=dp[i+1][j+1] + 1;
                ans=max(ans, dp[i][j]);
            }
        }
    }
    return ans;
}

int longestCommonSubsequence(string x, string y) {
    int n=(int) x.size(),m=(int) y.size();
    vector<vector<int>> dp(n+1, vector<int> (m+1,0));
    int ans=0;
    for(int i=n-1;i>=0;i--) {
        for(int j=m-1;j>=0;j--) {
            if(x[i]==y[j]) {
                dp[i][j]=dp[i+1][j+1] + 1;
            } else {
                dp[i][j]=max(dp[i][j+1], dp[i+1][j]);
            }
            ans=max(ans, dp[i][j]);
        }
    }
    return ans;
}

// Delete Operation for Two Strings LC 583
int deleteOperationForTwoStrings(string word1, string word2) {
    int n=(int) word1.size(), m=(int) word2.size();
    int x=longestCommonSubsequence(word1, word2);
    return n+m-(2*x);
}

// Edit Distance LC 72
int editDistance(string word1, string word2) {
    int n=(int) word1.size(), m=(int) word2.size();
    vector<vector<int>> dp(n+1, vector<int> (m+1,0));
    for(int i=n;i>=0;i--) {
        for(int j=m;j>=0;j--) {
            if(i==n) {
                dp[i][j]=m-j;
            } else if(j==m) {
                dp[i][j]=n-i;
            } else if(word1[i]==word2[j]) {
                dp[i][j]=dp[i+1][j+1];
            } else {
                dp[i][j]=min(dp[i+1][j+1], min(dp[i][j+1], dp[i+1][j])) + 1;
            }
        }
    }
    return dp[0][0];
}

// GFG - Coin Change
int coinChangeInfiniteCombination(vector<int> coins, int amount) {
    vector<int> dp(amount+1,0);
    dp[0]=1;
    for(int coin: coins) {
        for(int target=coin;target<=amount;target++) {
            dp[target]+=dp[target-coin];
        }
    }
    return dp[amount];
}

// GFG - Find number of solutions of a linear equation of n variables
int linearEquationOfNvariables(vector<int> coeffs, int rhs) {
    return coinChangeInfiniteCombination(coeffs, rhs);
}

// LC 322 - Coin Change
/* min coins for change of an amount, each coin is infitely available */
int minCoinChange(vector<int>& coins, int amount) {
    int n=(int) coins.size();
    sort(coins.begin(),coins.end());
    vector<int> dp(amount+1, -1);
    dp[0]=0;
    for(int target=coins[0];target<=amount;target++) {
        int i=0, coin, Min=INT_MAX;
        while(i<n && target>=coins[i]) {
            coin=coins[i++];
            if(dp[target-coin]!=-1) {
                Min=min(Min, dp[target-coin] + 1);
            }
        }
        if(Min!=INT_MAX) dp[target]=Min;
    }
    return dp[amount];
}

// LC 377 - Combination Sum IV
/* coinChangeInfinitePermutation */
int combinationSum4(vector<int>& nums, int target) {
    int n=(int) nums.size();
    if(n==0) return 0;
    sort(nums.begin(),nums.end());
    vector<unsigned int> dp(target+1,0);
    dp[0]=1;
    for(int t=nums[0];t<=target;t++)
        for(int num: nums)
            if(t-num>=0) dp[t]+=dp[t-num];
    return dp[target];
}

// LC 494 - Target Sum
/* coinChange - have to use all coins, each coin has to be assigned +ve or -ve sign */
/* find no of ways to achieve the target */
int targetSumTab2(vector<int>& nums, int S) {
    /*
     so the nums array has to divided into two subsets P and N,
     where elements of P will pe assigned +ve sign and that of N will be assigned -ve sign.
     Now let the the sum of all elements of nums be 'sum' and
     sum of all elemets of P and N pe 'x' and 'y' respectivelt.
     ATQ x-y=S and x+y=sum; => 2x=sum+S; =>x=(sum+S)/2.
     Now the question has been reduced to find a target of 'x' from nums array, which is a
     coin change - only one coin of a denomination type problem.
     */
    int n=(int) nums.size();
    int sum=0;
    for(int num: nums) sum+=num;
    if(S>sum || (sum+S)%2==1) return 0;
    int target=(sum+S)/2;
    vector<vector<int>> dp(n+1, vector<int> (target+1, 0));
    dp[0][0]=1;
    for(int i=1;i<=n;i++) {
        for(int j=0;j<=target;j++) {
            if(j-nums[i-1]<0) dp[i][j]=dp[i-1][j];
            else dp[i][j]=dp[i-1][j-nums[i-1]] + dp[i-1][j];
        }
    }
    return dp[n][target];
}

int targetSumTab1(vector<int>& nums, int S) {
    int n=(int) nums.size();
    unsigned int totalSum=0, range;
    for(int num: nums) totalSum+=num;
    range=2*totalSum + 1 ;
    if(totalSum+S<0 || totalSum+S>=range) return 0;
    vector<vector<unsigned int>> dp(n+1, vector<unsigned int> (range, 0));
    dp[0][totalSum]=1;
    for(int i=0;i<n;i++) {
        for(int j=0;j<range;j++) {
            if(dp[i][j]>0) {
                if(j-nums[i]>=0 && j-nums[i]<range)
                    dp[i+1][j-nums[i]]+=dp[i][j];
                if(j+nums[i]>=0 && j+nums[i]<range)
                    dp[i+1][j+nums[i]]+=dp[i][j];
            }
        }
    }
    return dp[n][totalSum+S];
}

int findTargetSumWaysMemo(vector<int>& nums, int S, int idx, int sum, int totalSum, vector<vector<unsigned int>>& dp) {
    if(idx==nums.size()) return dp[idx][sum+totalSum]=sum==S?1:0;
    if(dp[idx][sum+totalSum]!=1001) return dp[idx][sum+totalSum];
    int pve=findTargetSumWaysMemo(nums, S, idx+1, sum+nums[idx], totalSum, dp);
    int nve=findTargetSumWaysMemo(nums, S, idx+1, sum-nums[idx], totalSum, dp);
    return dp[idx][sum+totalSum]=pve+nve;
}


int targetSumMemo(vector<int>& nums, int S) {
    int n=(int) nums.size();
    unsigned int totalSum=0, range;
    for(int num: nums) totalSum+=num;
    range=2*totalSum + 1 ;
    if(totalSum+S<0 || totalSum+S>=range) return 0;
    vector<vector<unsigned int>> dp(n+1, vector<unsigned int> (range, 1001));
    return findTargetSumWaysMemo(nums, S, 0, 0, totalSum, dp);
}

int findTargetSumWays(vector<int>& nums, int S) {
    // return targetSumMemo(nums, S);
    // return targetSumTab1(nums, S);
    return targetSumTab2(nums, S);
}

/* coinChangeCombination - can use a coin only once */
/* find no of ways to achieve the target */
int targetSumPepcoding(vector<int>& nums, int S) {
    int n=(int) nums.size();
    vector<vector<int>> dp(n+1, vector<int> (S+1,0));
    dp[0][0]=1;
    for (int i=1; i<=n; i++) {
        for (int j=0; j<=S; j++) {
            if (j==0 || j-nums[i-1]<0) {
                dp[i][j]=dp[i-1][j];
            } else {
                dp[i][j]+=dp[i-1][j]/*dont include*/ + dp[i-1][j-nums[i-1]]/*include*/;
            }
        }
    }
    return dp[n][S];
}

void coinChangeTargetSum() {
    int target=10;
    vector<int> nums={2, 3, 1, 5, 6};
    cout<<targetSumPepcoding(nums, target)<<"\n";
}

// GFG - 0 - 1 Knapsack Problem
int zeroOneKnapSackMemoBottomUp(vector<int>& v, vector<int>& w, int W, vector<vector<int>>& dp, int idx) {
    if (W==0 || idx==(int) v.size()) {
        return 0;
    }
    
    if (dp[idx][W]!=0) {
        return dp[idx][W];
    }
    
    int x=0,y=0;
    if (W-w[idx]>=0) {
        x=zeroOneKnapSackMemoBottomUp(v, w, W-w[idx], dp, idx + 1) + v[idx];
    }
    y=zeroOneKnapSackMemoBottomUp(v, w, W, dp, idx + 1);
    return dp[idx][W]=max(x, y);
}

int zeroOneKnapSackMemoTopDown(vector<int>& v, vector<int>& w, int W, vector<vector<int>>& dp, int n) {
    if (W==0 || n==0) {
        return 0;
    }
    
    if (dp[n][W]!=0) {
        return dp[n][W];
    }
    
    int x=0,y=0;
    if (W-w[n-1]>=0) {
        x=zeroOneKnapSackMemoTopDown(v, w, W-w[n-1], dp, n-1) + v[n-1];
    }
    y=zeroOneKnapSackMemoTopDown(v, w, W, dp, n-1);
    return dp[n][W]=max(x, y);
}

int zeroOneKnapSackTab(vector<int>& v, vector<int>& w, int W) {
    int n=(int) v.size();
    vector<vector<int>> dp(n+1, vector<int> (W+1, 0));
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=W; j++) {
            if (j-w[i-1]<0) {
                dp[i][j]=dp[i-1][j];
            } else {
                dp[i][j]=max(dp[i-1][j-w[i-1]] + v[i-1], dp[i-1][j]);
            }
        }
    }
    return dp[n][W];
}

// GFG - Knapsack with Duplicate Items
int unboundedKnapSackTab(vector<int>& v, vector<int>& w, int W) {
    int n=(int) v.size();
    vector<vector<int>> dp(n+1, vector<int> (W+1, 0));
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=W; j++) {
            if (j-w[i-1]<0) {
                dp[i][j]=dp[i-1][j];
            } else {
                dp[i][j]=max(dp[i][j-w[i-1]] + v[i-1], dp[i-1][j]);
            }
        }
    }
    return dp[n][W];
}

void knapSack() {
    vector<int> value={1,4,5,7};
    vector<int> weight={1,3,4,5};
    int W=8;
//    int n=(int) value.size();
//    vector<vector<int>> dp(n+1, vector<int> (W+1));
    
//    cout<<zeroOneKnapSackMemoTopDown(value, weight, W, dp, 0)<<"\n";
//    cout<<zeroOneKnapSackMemoTopDown(value, weight, W, dp, n)<<"\n";
//    cout<<zeroOneKnapSackTab(value, weight, W)<<"\n";
    cout<<unboundedKnapSackTab(value, weight, W)<<"\n";
}

// GFG - Find number of times a string occurs as a subsequence
int subsequenceCount(string S, string T) {
    int M=1000000007;
    int n=(int) S.size(), m=(int) T.size();
    vector<vector<int>> dp(m+1, vector<int> (n+1, 0));
    dp[m][n]=1;
    for(int i=m;i>=0;i--) {
        for(int j=n-1;j>=0;j--) {
            if(i==m) dp[i][j]=1;
            else if(T[i]==S[j])
                dp[i][j]=dp[i+1][j+1]+dp[i][j+1];
            else
                dp[i][j]=dp[i][j+1];
            dp[i][j]=dp[i][j]<0?dp[i][j]+M : dp[i][j]%M;
        }
    }
    return dp[0][0];
}

// GFG , LC 300 - Longest Increasing Subsequence
int longestIncreasingSubsequence1(vector<int>& nums) {
    int n=(int) nums.size(), ans=0;
    if (n<=1) return n;
    vector<int> dp(n,1);
    for (int i=1; i<n; i++) {
        for (int j=0; j<i; j++) {
            if (nums[j]<nums[i]) {
                dp[i]=max(dp[i], dp[j]+1);
            }
        }
        ans=max(ans, dp[i]);
    }
    return ans;
}

int longestIncreasingSubsequence2(vector<int>& nums) {
    // this is the longest common subsequence algorithm
    /*
     The longest increasing subsequence of any sequence is the subsequence of the sorted
     sequence of itself. The approach is the same as the classical LCS problem but instead of
     the second sequence, given sequence is taken again in its sorted form.
     */
    int n=(int) nums.size(), ans=0;
    if (n<=1) return n;
    vector<int> arr(nums);
    sort(arr.begin(), arr.end());
    vector<vector<int>> dp(n+1,vector<int>(n+1,0));
    dp[n][n]=1;
    for (int i=n-1; i>=0; i--) {
        for (int j=n-1; j>=0; j--) {
            if (nums[i]==nums[j]) {
                dp[i][j]=dp[i+1][j+1] + 1;
            } else {
                dp[i][j]=max(dp[i+1][j], dp[i][j+1]);
            }
            ans=max(ans, dp[i][j]);
        }
    }
    return dp[0][0];
}

// GFG - Longest Decreasing Subsequence
int longestDecreasingSubsequence1(vector<int>& nums) {
    int n=(int) nums.size(), ans=0;
    if (n<=1) return n;
    vector<int> dp(n,1);
    for (int i=1; i<n; i++) {
        for (int j=0; j<i; j++) {
            if (nums[j]>nums[i]) {
                dp[i]=max(dp[i], dp[j]+1);
            }
        }
        ans=max(ans, dp[i]);
    }
    return ans;
}

int longestDecreasingSubsequence2(vector<int>& nums) {
    int n=(int) nums.size(), ans=0;
    if (n<=1) return n;
    vector<int> dp(n,1);
    for (int i=n-2; i>=0; i--) {
        for (int j=n-1; j>i; j--) {
            if (nums[j]<nums[i]) {
                dp[i]=max(dp[i], dp[j]+1);
            }
        }
        ans=max(ans, dp[i]);
    }
    return ans;
}

// GFG - Longest Bitonic subsequence
int longestBitonicSequence(vector<int>& nums) {
    int n=(int) nums.size(), ans=0;
    if (n<=1) return n;
    vector<int> lis(n,1), lds(n,1);
    for (int i=1; i<n; i++)
        for (int j=0; j<i; j++)
            if (nums[j]<nums[i]) lis[i]=max(lis[i], lis[j]+1);
    for (int i=n-2; i>=0; i--)
        for (int j=n-1; j>i; j--)
            if (nums[j]<nums[i]) lds[i]=max(lds[i], lds[j]+1);
    for (int i=0; i<n; i++) ans=max(ans, lis[i]+lds[i]-1);
    return ans;
}

// GFG - Maximum sum increasing subsequence
int maxSumIncreasingSubsequence(vector<int>& nums) {
    int n=(int) nums.size(), ans=0;
    if (n==1) return nums[0];
    vector<int> dp(n,0);
    for (int i=0; i<n; i++) {
        dp[i]=nums[i];
        for (int j=0; j<i; j++) {
            if (nums[j]<nums[i]) {
                dp[i]=max(dp[i], dp[j]+nums[i]);
            }
        }
        ans=max(ans, dp[i]);
    }
    return ans;
}

// GFG - Maximum Sum Decreasing Subsequence
int maxSumDecreasingSubsequence(vector<int>& nums) {
    int n=(int) nums.size(), ans=0;
    if (n==1) return nums[0];
    vector<int> dp(n,0);
    for (int i=0; i<n; i++) {
        dp[i]=nums[i];
        for (int j=0; j<i; j++) {
            if (nums[j]>nums[i]) {
                dp[i]=max(dp[i], dp[j]+nums[i]);
            }
        }
        ans=max(ans, dp[i]);
    }
    return ans;
}

// GFG - Maximum Sum Subsequence of length k // TODO - Write its Memoization
int maxSumIncreasingSubsequenceOfLengthK(vector<int>& nums, int k) {
    int n=(int) nums.size(), ans=-1;
    if (n==1) return nums[0];
    vector<vector<int>> dp(n, vector<int>(k+1, -1));
    for (int i=0; i<n; i++) {
        dp[i][1]=nums[i];
        for (int j=0; j<i; j++) {
            if (nums[j]<nums[i]) {
                for (int l=2; l<=k; l++) {
                    if (dp[j][l-1]!=-1) {
                        dp[i][l]=max(dp[i][l], dp[j][l-1] + nums[i]);
                    }
                }
            }
        }
        ans=max(ans, dp[i][k]);
    }
    return ans;
}

// LC 673 - Number of Longest Increasing Subsequence
int noOfLongestIncreasingSubsequence(vector<int>& nums) {
    int n=(int) nums.size(), maxLen=0, count=0;
    if(n<=1) return n;
    vector<int> lisLen(n,1);
    vector<int> lisCount(n,1);
    for(int i=0;i<n;i++) {
        for(int j=0;j<i;j++) {
            if(nums[j]<nums[i]){
                if(lisLen[j]+1 > lisLen[i]) {
                    lisLen[i]=lisLen[j]+1;
                    lisCount[i]=lisCount[j];
                }else if(lisLen[j]+1 == lisLen[i]) {
                    lisCount[i]+=lisCount[j];
                }
            }
        }
        if(maxLen<lisLen[i]) {
            maxLen=lisLen[i];
            count=lisCount[i];
        } else if(maxLen==lisLen[i]) {
            count+=lisCount[i];
        }
    }
    return count;
}

// LC - 76 Minimum Window Substring
string minWindowSubstring(string s, string t) {
    vector<int> map(128,0);
    for(auto c: t) map[c]++;
    int counter=(int) t.size(), begin=0, end=0, d=INT_MAX, head=0;
    while(end<s.size()){
        if(map[s[end++]]-->0) counter--; //in t
        while(counter==0){ //valid
            if(end-begin<d)  d=end-(head=begin);
            if(map[s[begin++]]++==0) counter++;  //make it invalid
        }
    }
    return d==INT_MAX? "":s.substr(head, d);
}

// LC - 354 Russian Doll Envelopes
static bool comp(vector<int>& a, vector<int>& b) {
    return a[0]<b[0] || (a[0]==b[0] && a[1]>b[1]);
}
int maxEnvelopes(vector<vector<int>>& envelopes) {
    int n=(int) envelopes.size(), ans=1;
    if(n<=1) return n;
    vector<int> dp(n,1);
    sort(envelopes.begin(), envelopes.end(), comp);
    for(int i=1;i<n;i++) {
        for(int j=0;j<i;j++) {
            if(envelopes[j][1]<envelopes[i][1]) {
                dp[i]=max(dp[i], dp[j]+1);
            }
        }
        ans=max(ans, dp[i]);
    }
    return ans;
}

// LC - 1235 Maximum Profit in Job Scheduling
int maxProfitJobScheduling
(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
    int n=(int) profit.size(), ans=0;
    if(n==0) return 0;
    if(n==1) return profit[0];
    vector<vector<int>> job(n, vector<int>());
    for(int i=0; i<n;i++)
        job[i]={endTime[i], startTime[i], profit[i]};
    sort(job.begin(), job.end());
    vector<int> dp(n);
    dp[0]=job[0][2];
    for(int i=1;i<n;i++) {
        dp[i]=job[i][2];
        for(int j=0;j<i;j++) {
            // if no job overlap
            if(job[j][0]<=job[i][1]) {
                dp[i]=max(dp[i], dp[j]+job[i][2]);
            }
        }
        ans=max(ans, dp[i]);
    }
    return ans;
}

// GFG - Box Stacking
int boxStacking(vector<int> height,vector<int> width,vector<int> length,int n) {
    vector<vector<int>> box(6*n, vector<int>());
    for(int i=0;i<6*n;i++) {
        if(i<n) {
            box[i]={length[i], width[i], height[i]};
        } else if(i<2*n) {
            box[i]={width[i-n], length[i-n], height[i-n]};
        } else if(i<3*n) {
            box[i]={width[i-2*n], height[i-2*n], length[i-2*n]};
        } else if(i<4*n) {
            box[i]={height[i-3*n], width[i-3*n], length[i-3*n]};
        } else if(i<5*n) {
            box[i]={height[i-4*n], length[i-4*n], width[i-4*n]};
        } else if(i<6*n) {
            box[i]={length[i-5*n], height[i-5*n], width[i-5*n]};
        }
    }
    sort(box.begin(), box.end(), comp);
    vector<int> dp(6*n);
    int ans=0;
    for(int i=0;i<6*n;i++) {
        dp[i]=box[i][2];
        for(int j=0;j<i;j++) {
            if(box[j][0]<box[i][0] && box[j][1]<box[i][1]) {
                dp[i]=max(dp[i], dp[j]+box[i][2]);
            }
        }
        ans=max(ans, dp[i]);
    }
    return ans;
}

// LC - 91 Decode Ways
int decodeWays(string s) {
    int n=(int) s.size();
    if(n==0) return 0;
    vector<int>dp(n+1,0);
    dp[n]=1;
    dp[n-1]=(s[n-1]-'0')==0?0:1;
    for(int i=n-2;i>=0;i--) {
        if(s[i]=='1' || (s[i]=='2' && (s[i+1]-'0')<=6) ) {
            dp[i]=dp[i+1]+dp[i+2];
        } else if(s[i]!='0') {
            dp[i]=dp[i+1];
        }
    }
    return dp[0];
}

// LC - 639 Decode Ways II
int decodeWays2(string s) {
    int m=1000000007;
    int n=(int) s.size();
    if(n==0) return 0;
    vector<long long int> dp(n+1,0);
    dp[n]=1;
    dp[n-1]=s[n-1]=='*'?9:s[n-1]=='0'?0:1;
    for(int i=n-2;i>=0;i--) {
        if(s[i]=='*') {
            dp[i]+=9*dp[i+1];
            dp[i]=dp[i]<0?dp[i]+m:dp[i]%m;
            if(s[i+1]=='*') dp[i]+=15*dp[i+2];
            else if((s[i+1]-'0')<=6) dp[i]+=2*dp[i+2];
            else dp[i]+=dp[i+2];
            dp[i]=dp[i]<0?dp[i]+m:dp[i]%m;
        } else if(s[i]!='0') {
            dp[i]+=dp[i+1];
            if(s[i+1]=='*') {
                if(s[i]=='1') dp[i]+=9*dp[i+2];
                else if(s[i]=='2') dp[i]+=6*dp[i+2];
            }
            else if(s[i]=='1'|| (s[i]=='2' && (s[i+1]-'0')<=6))
                dp[i]+=dp[i+2];
            dp[i]=dp[i]<0?dp[i]+m:dp[i]%m;
        }
    }
    return (int) dp[0];
}

// GFG - Matrix Chain Multiplication
int matrixChainMultiplication(vector<int>& arr) {
    int n=(int) arr.size();
    vector<vector<int>> dp(n, vector<int> (n,INT_MAX));
    for(int gap=1;gap<n;gap++)
        for(int i=0, j=gap; j<n;i++, j++)
            if(gap==1) dp[i][j]=0;
            else
                for(int k=i+1;k<j;k++)
                    dp[i][j]=min(dp[i][j], dp[i][k]+arr[i]*arr[k]*arr[j]+dp[k][j]);
    return dp[0][n-1];
}

// LC 132 - Palindrome Partitioning II
int palindromePartitioning1(string s) {
    int n=(int) s.size();
    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
    for(int gap=0;gap<n;gap++) {
        for(int i=0,j=gap;j<n;i++,j++) {
            if(gap==0) dp[i][j]=0;
            else if(gap==1) dp[i][j]=s[i]==s[j]?0:1;
            else if(s[i]==s[j] && dp[i+1][j-1]==0) dp[i][j]=0;
            else {
                for(int k=i;k<j;k++) {
                    dp[i][j]=min(dp[i][j], dp[i][k]+dp[k+1][j]+1);
                }
            }
        }
    }
    return dp[0][n-1];
}

int palindromePartitioning2(string s) { // approach similar to word break;
    int n=(int) s.size();
    vector<vector<bool>> isPalindrome(n, vector<bool> (n, false));
    vector<int> dp(n+1);
    for(int i=0;i<=n;i++) dp[i]=i-1;
    isPalindromicSubstringTab(s, isPalindrome);
    for(int i=1;i<=n;i++) {
        for(int j=i-1;j>=0;j--) {
            if(isPalindrome[j][i-1]){
                dp[i]=min(dp[i], dp[j]+1);
            }
        }
    }
    return dp[n];
}

// GFG - Optimal Binary Search Tree
int optimalBinarySearchTree(vector<int>& keys, vector<int>& freqs) {
    int n=(int) keys.size();
    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
    for(int gap=0;gap<n;gap++) {
        for(int i=0,j=gap;j<n;i++,j++) {
            if(gap==0) dp[i][j]=freqs[i];
            else {
                int sum=accumulate(freqs.begin()+i, freqs.begin()+j, 0);
                for(int k=i;k<=j;k++) {
                    dp[i][j]=min(dp[i][j], (k==i?0:dp[i][k-1]) + (k==i?0:dp[k+1][j]) + sum);
                }
            }
        }
    }
    return dp[0][n-1];
}

// Lc 312 - Burst Balloons
int burstBalloons(vector<int>& nums) {
    int n=(int) nums.size();
    vector<vector<int>> dp(n+2, vector<int>(n+2,0));
    nums.push_back(1);
    nums.insert(nums.begin(),1);
    for(int gap=0;gap<n;gap++) {
        for(int i=1, j=gap+1;j<=n;i++, j++) {
            for(int last=i;last<=j;last++) {
                dp[i][j]=max(dp[i][j],
                             dp[i][last-1] +
                             nums[i-1] * nums[last] * nums[j+1] +
                             dp[last+1][j]);
            }
        }
    }
    return dp[1][n];
}

// LC 139 - Word Break
bool wordBreak(string s, vector<string>& wordDict) {
    if(wordDict.size()==0) return false;
    vector<bool> dp(s.size()+1,false);
    unordered_set<string> dict;
    for(string word: wordDict) dict.insert(word);
    dp[0]=true;
    for(int i=1;i<=s.size();i++) {
        for(int j=i-1;j>=0;j--) {
            if(dp[j]){
                string word = s.substr(j,i-j);
                if(dict.find(word)!= dict.end()){
                    dp[i]=true;
                    break;
                }
            }
        }
    }
    return dp[s.size()];
}

// LC 44 - Wildcard Matching
bool wildcardMatching(string s, string p) {
    // trim
    int len=(int) p.size();
    for(int i=0;i<len-1;i++) {
        if(p[i]=='*' && p[i+1]=='*') {
            len--;
            i--;
        }
    }
    int n=(int) p.size(), m=(int) s.size();
    vector<vector<bool>> dp(n+1, vector<bool> (m+1,false));
    dp[n][m]=true;
    for(int i=n-1;i>=0;i--) {
        for(int j=m;j>=0;j--) {
            if(j==m) dp[i][j]=p[i]=='*'?dp[i+1][j]:false;
            else if(p[i]=='?' || (p[i]!='*' && p[i]==s[j]))
                dp[i][j]=dp[i+1][j+1];
            else if(p[i]=='*') {
                dp[i][j]=dp[i][j+1] || dp[i+1][j];
            }
        }
    }
    return dp[0][0];
}

// GFG - Boolean Parenthesization
int booleanParenthesization(string s) {
    int n=(int) s.size(), m=1003;
    int dp[n][n][2];
    memset(dp,0,sizeof(dp));
    for(int gap=0; gap<n; gap+=2) {
        for(int i=0, j=gap; j<n; i+=2, j+=2) {
            if(gap==0) {
                dp[i][j][0]=s[i]=='T'?1:0;
                dp[i][j][1]=s[i]=='F'?1:0;
            } else {
                for(int k=i+1;k<j;k+=2) {
                    if(s[k]=='&') {
                        dp[i][j][0]+=dp[i][k-1][0] * dp[k+1][j][0];
                        dp[i][j][1]+=dp[i][k-1][0] * dp[k+1][j][1] +
                                    dp[i][k-1][1] * dp[k+1][j][0] +
                                    dp[i][k-1][1] * dp[k+1][j][1];
                    } else if(s[k]=='|') {
                        dp[i][j][0]+=dp[i][k-1][0] * dp[k+1][j][0] +
                                    dp[i][k-1][0] * dp[k+1][j][1] +
                                    dp[i][k-1][1] * dp[k+1][j][0];
                        dp[i][j][1]+=dp[i][k-1][1] * dp[k+1][j][1];
                    } else if(s[k]=='^') {
                        dp[i][j][0]+=dp[i][k-1][0] * dp[k+1][j][1] +
                                    dp[i][k-1][1] * dp[k+1][j][0];
                        dp[i][j][1]+=dp[i][k-1][0] * dp[k+1][j][0] +
                                    dp[i][k-1][1] * dp[k+1][j][1];
                    }
                    dp[i][j][0]=dp[i][j][0]<0?dp[i][j][0]+m : dp[i][j][0]%m;
                    dp[i][j][1]=dp[i][j][1]<0?dp[i][j][1]+m : dp[i][j][1]%m;
                }
            }
        }
    }
    return dp[0][n-1][0];
}

// GFG - Count subsequences of type a^i b^j c^k
int subsequenceOfTypeAiBjCk(string s) {
    // trim
    int len=(int) s.size(), i=len-1;
    while(len>0) {
        if(s[i]=='c') break;
        len--;
        i--;
    }
    int n=(int) s.size();
    if(n==0) return 0;
    int abc=0, bc=0, c=0;
    for(i=n-1;i>=0;i--) {
        if(s[i]=='c') c=c==0?1:2*c+1;
        else if(s[i]=='b') bc=c+2*bc;
        else if(s[i]=='a') abc=bc+2*abc;
    }
    return abc;
}

// LC 940 - Distinct Subsequences II
int distinctSubseqII(string S) {
    int n=(int) S.size(), m=1000000007;
    vector<int> dp(n+1, 0);
    vector<int> last(26, -1);
    dp[0]=1;
    for(int i=1;i<=n;i++) {
        dp[i]=2*dp[i-1];
        if(last[S[i-1]-'a']!=-1)
            dp[i]-=last[S[i-1]-'a']==-1?0:dp[last[S[i-1]-'a']];
        dp[i]=dp[i]<0?dp[i]+m:dp[i]%m;
        last[S[i-1]-'a']=i-1;
    }
    return dp[n]-1;
}

// LC 121 - Best Time to Buy and Sell Stock
int bestTimeToBuyAndSellStock(vector<int>& prices) {
    int maxPro = 0;
    int minPrice = INT_MAX;
    for(int i = 0; i < prices.size(); i++){
        minPrice = min(minPrice, prices[i]);
        maxPro = max(maxPro, prices[i] - minPrice);
    }
    return maxPro;
}

// LC 123 - Best Time to Buy and Sell Stock III
int bestTimeToBuyAndSellStockIII(vector<int>& prices) {
    int n=(int) prices.size(), ans=0;
    if(n<=1) return 0;
    vector<int> l(n, 0), r(n, 0);
    /*
     Logic - At any given day i, the maximum profit of one transaction (starting
     from day 0 to day i) is prices[i] - minPrice.
     Note that the minPrice is the minimum price from day 0 to i (including day i).
     */
    int minPrice=INT_MAX, lProfit=0;
    for(int i=0;i<n;i++) {
        minPrice=min(minPrice, prices[i]);
        l[i]=lProfit=max(lProfit, prices[i]-minPrice);
    }
    /*
     Logic - At any given day i, the maximum profit of one transaction (starting
     from day i to day n-1) is maxPrice - prices[i].
     Note that the maxPrice is the maximum price from day n-1 to i (including day i).
     */
    int maxPrice=prices[n-1], rProfit=0;
    for(int i=n-2;i>=0;i--) {
        maxPrice=max(maxPrice, prices[i]);
        r[i]=rProfit=max(rProfit, maxPrice-prices[i]);
        ans=max(ans, l[i]+r[i+1]); // calculating final answer
    }
    return max(ans, r[0]);
}

// LC 188 - Best Time to Buy and Sell Stock IV
int bestTimeToBuyAndSellStockIV(int k, vector<int>& prices) {
    /**
     * dp[i, j] represents the max profit up until prices[j] using at most i transactions.
     * dp[i, j] = max(dp[i, j-1], prices[j] - prices[jj] + dp[i-1, jj]) { jj in range of [0, j-1] } //O(k(n^2))
     *          = max(dp[i, j-1], prices[j] + max(dp[i-1, jj] - prices[jj])) //O(kn)
     * dp[0, j] = 0; 0 transactions makes 0 profit
     * dp[i, 0] = 0; if there is only one price data point you can't make any transaction.
     */
    
    int n=(int) prices.size();
    if(n<=1) return 0;
    if(k>=n/2) {
        int profit=0;
        for(int i=1;i<n;i++) {
            if(prices[i]>prices[i-1]) profit+=prices[i]-prices[i-1];
        }
        return profit;
    }
    vector<vector<int>> dp(k+1, vector<int>(n,0));
    //O(kn)
    for(int i=1;i<=k;i++) {
        int localMax=dp[i-1][0]-prices[0];
        for(int j=1;j<n;j++) {
            dp[i][j]=max(dp[i][j-1], prices[j]+localMax);
            localMax=max(localMax, dp[i-1][j]-prices[j]);
        }
    }
    //O(k(n^2))
    /*
     for(int i=1;i<=k;i++) {
     int localMax=dp[i-1][0]-prices[0];
     for(int j=1;j<n;j++) {
     int not_sell=dp[i][j-1], sell=0;
     for(int m=0;m<j;m++) {
     sell=max(sell, prices[j]-prices[m]+dp[i-1][m]);
     }
     dp[i][j]=max(not_sell, sell);
     }
     }
     */
    return dp[k][n-1];
}

// LC 368 - Largest Divisible Subset
vector<int> largestDivisibleSubset(vector<int>& nums) {
    int n=(int) nums.size(), maxCount=1, maxIdx=0;
    if(n<=1) return nums;
    sort(nums.begin(), nums.end());
    vector<int> count(n,1), parent(n, -1);
    for(int i=n-1;i>=0;i--) {
        for(int j=i+1;j<n;j++) {
            if(nums[j]%nums[i]==0 && count[i]<count[j]+1) {
                count[i]=count[j]+1;
                parent[i]=j;
            }
        }
        if(maxCount<count[i]) {
            maxCount=count[i];
            maxIdx=i;
        }
    }
    if(maxCount==1) return {nums[0]};
    vector<int> ans(maxCount);
    int i=maxIdx, j=0;
    while(j<maxCount) {
        ans[j++]=nums[i];
        i=parent[i];
    }
    return ans;
}

// LC 309 - Best Time to Buy and Sell Stock with Cooldown
int bestTimeToBuyAndSellStockWithCooldown(vector<int>& prices) {
    int n=(int) prices.size();
    if(n<=1) return 0;
    vector<vector<int>> dp(n, vector<int> (2));
    
    // base cases
    dp[0][0]=0;             // day 0, 0 stock in hand
    dp[0][1]=-prices[0];    // day 0, 1 stock in hand, buy on day 0;
    
    // day 1, 0 stock in hand, do nothing or sell the stock bought on day 0;
    dp[1][0]=max(0, prices[1]-prices[0]);
    // day 1, 1 stock in hand, do nothing or buy on day 1;
    dp[1][1]=max(dp[0][1], -prices[1]);
    
    // dp
    for(int i=2;i<n;i++) {
        dp[i][0]=max(dp[i-1][0]/*do nothing*/, dp[i-1][1]+prices[i]/*sell yesterday stock*/);
        dp[i][1]=max(dp[i-1][1]/*do nothing*/, dp[i-2][0]-prices[i]/*buy with cooldown*/);
    }
    return dp[n-1][0];
}

// LC 714 - Best Time to Buy and Sell Stock with Transaction Fee
int bestTimeToBuyAndSellStockWithTransactionFee(vector<int>& prices, int fee) {
    int n=(int) prices.size();
    if(n<=1) return 0;
    vector<vector<int>> dp(n, vector<int> (2));
    
    // base cases
    dp[0][0]=0;             // day 0, 0 stock in hand
    dp[0][1]=-prices[0];    // day 0, 1 stock in hand, buy on day 0;
    
    // dp
    for(int i=1;i<n;i++) {
        dp[i][0]=max(dp[i-1][0]/*do nothing*/, dp[i-1][1]+prices[i]-fee/*sell*/);
        dp[i][1]=max(dp[i-1][1]/*do nothing*/, dp[i-1][0]-prices[i]/*buy*/);
    }
    return dp[n-1][0];
}

// LC 689 - Maximum Sum of 3 Non-Overlapping Subarrays
vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
    int n=(int) nums.size();
    vector<int> subsetSum(n-k+1), lPos(n-k+1), rPos(n-k+1), ans(3,-1);
    int sum=0;
    for(int i=0;i<k;i++) sum+=nums[i];  // first subset;
    subsetSum[0]=sum;
    for(int i=k;i<n;i++) {
        sum+=nums[i]-nums[i-k];
        subsetSum[i+1-k]=sum;
    }
    int idx=0; // index with max subsetSum to the left;
    for(int i=0;i<=n-k;i++) {
        if(subsetSum[i]>subsetSum[idx]) idx=i;
        lPos[i]=idx;
    }
    idx=n-k; // index with max subsetSum to the right;
    for(int i=n-k;i>=0;i--) {
        if(subsetSum[i]>=subsetSum[idx]) idx=i;
        rPos[i]=idx;
    }
    for(int i=k;i<=n-(2*k);i++) {
        int l=lPos[i-k], r=rPos[i+k];
        if(ans[0]==-1 ||subsetSum[l]+subsetSum[i]+subsetSum[r]>
           subsetSum[ans[0]]+subsetSum[ans[1]]+subsetSum[ans[2]]) {
            ans={l,i,r};
        }
    }
    return ans;
}

// GFG - Dice Throw
long long int diceThrow(int m/*noOfFaces*/, int n/*noOfDices*/, int target) {
    if(n*m<target) return 0;
    if(n*m==target) return 1;
    vector<vector<long long int>> dp(n, vector<long long int> (target, 0));
    for(int i=0;i<n;i++) {
        for(int j=i;j<(i+1)*m && j<target; j++) {
            if(i==0) dp[i][j]=j+1<=m?1:0;
            else {
                for(int k=1;k<=m && j-k>=i-1; k++) {
                    dp[i][j]+=dp[i-1][j-k];
                }
            }
        }
    }
    return dp[n-1][target-1];
}

// GFG - Maximize The Cut Segments
int maximizeTheCutSegements(int n,int x, int y, int z) {
    vector<int> dp(n+1, -1);
    dp[0]=0;
    for(int i=1;i<=n;i++) {
        if(i-x>=0 && dp[i-x]!=-1) dp[i]=max(dp[i], dp[i-x]+1);
        if(i-y>=0 && dp[i-y]!=-1) dp[i]=max(dp[i], dp[i-y]+1);
        if(i-z>=0 && dp[i-z]!=-1) dp[i]=max(dp[i], dp[i-z]+1);
    }
    return dp[n];
}

// GFG - Maximum Product Cutting
int maximumProductCutting(int n) {
    vector<int> dp(n+1);
    dp[0]=dp[1]=0;
    for(int i=1;i<=n;i++) {
        for (int j=1; j<=i/2; j++) {
            dp[i]=max(dp[i], max(j*dp[i-j], (i-j)*dp[j]));
        }
    }
    return dp[n];
}

// GFG - Minimum sum partition
int minimumSumPartition(vector<int> nums) {
    int n=(int) nums.size(), diff=INT_MAX;
    int sum=accumulate(nums.begin(), nums.end(), 0);
    vector<vector<int>> dp(n+1, vector<int> (sum+1, 0));
    dp[0][0]=1;
    for (int i=1; i<=n; i++) {
        for (int j=0; j<=sum; j++) {
            if (j==0 || j-nums[i-1]<0) {
                dp[i][j]=dp[i-1][j];
            } else {
                dp[i][j]+=dp[i-1][j]/*dont include*/ + dp[i-1][j-nums[i-1]]/*include*/;
            }
        }
    }
    for(int i=0;i<=sum/2;i++) {
        if(dp[n][i]!=0 && dp[n][sum-i]!=0) {
            diff=min(diff, sum-(2*i));
        }
    }
    return diff;
}

// GFG - Optimal Strategy For A Game
int optimalStrategyForAGame(vector<int>& arr) {
    int n=(int) arr.size();
    vector<vector<int>> p1(n, vector<int> (n, 0));
    vector<vector<int>> p2(n, vector<int> (n, 0));
    for(int gap=0;gap<n;gap++) {
        for(int i=0, j=gap; j<n; i++, j++) {
            if(gap==0) p1[i][j]=arr[i];
            else {
                p1[i][j]=max(arr[i]+p2[i+1][j], arr[j]+p2[i][j-1]);
                p2[i][j]=min(p1[i+1][j], p1[i][j-1]);
            }
        }
    }
    return p1[0][n-1];
}

// GFG - Shortest Common Supersequence
int shortestCommonSupersequence(string s1, string s2) {
    int n=(int) s1.size(), m=(int) s2.size();
    vector<vector<int>> dp(n+1, vector<int> (m+1,0));
    int lcs=0;
    for(int i=n-1;i>=0;i--) {
        for(int j=m-1;j>=0;j--) {
            if(s1[i]==s2[j]) {
                dp[i][j]=dp[i+1][j+1] + 1;
            } else {
                dp[i][j]=max(dp[i][j+1], dp[i+1][j]);
            }
            lcs=max(lcs, dp[i][j]);
        }
    }
    return n+m-lcs;
}

// LC 1092 - Shortest Common Supersequence
string longestCommonSubsequenceString(string& A, string& B) {
    int n=(int) A.size(), m=(int) B.size();
    vector<vector<string>> dp(n+1, vector<string>(m+1, ""));
    for (int i=0; i<n; ++i)
        for (int j=0; j<m; ++j)
            if (A[i]==B[j])
                dp[i+1][j+1]=dp[i][j]+A[i];
            else
                dp[i+1][j+1]=dp[i+1][j].size() > dp[i][j+1].size() ? dp[i+1][j]: dp[i][j+1];
    return dp[n][m];
}

string shortestCommonSupersequence1(string& A, string& B) {
    int i=0, j=0;
    string res="";
    string lcs=longestCommonSubsequenceString(A, B);
    for (char c :lcs) {
        while (A[i]!= c)
            res+= A[i++];
        while (B[j]!=c)
            res+=B[j++];
        res+=c; i++; j++;
    }
    return res+A.substr(i)+B.substr(j);
}

string shortestCommonSupersequence2(string str1, string str2) {
    int n =(int) str1.size(), m=(int) str2.size();
    vector<vector<int>> dp(n+1, vector<int> (m+1, 0));
    for(int i=1; i<n+1; i++) {
        for(int j=1; j<m+1; j++) {
            if(str1[i-1] == str2[j-1]){
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    int i=n, j=m;
    string res;
    while(i>0 && j>0) {
        if(str1[i-1] == str2[j-1]) {
            res.push_back(str1[i-1]);
            i--;
            j--;
        } else if(dp[i-1][j] > dp[i][j-1]) {
            res.push_back(str1[i-1]);
            i--;
        } else {
            res.push_back(str2[j-1]);
            j--;
        }
    }
    while(i>0) {
        res.push_back(str1[i-1]);
        i--;
    }
    while(j>0) {
        res.push_back(str2[j-1]);
        j--;
    }
    reverse(res.begin(), res.end());
    return res;
}

// GFG - Minimum number of jumps
int minimumNoOfJumps(vector<int>& nums) {
    int n=(int) nums.size();
    vector<int> dp(n, INT_MAX);
    dp[n-1]=0;
    for(int i=n-2;i>=0;i--) {
        if(nums[i]==0) continue;
        for(int jump=1; i+jump<n && jump<=nums[i]; jump++) {
            if((i+jump)==n-1 || (nums[i+jump]!=0 && dp[i+jump]!=INT_MAX)) {
                dp[i]=min(dp[i], dp[i+jump]+1);
            }
        }
    }
    return dp[0]==INT_MAX?-1:dp[0];
}



int main() {
//    fibonacci();
//    uniquePaths();
//    countBoardPath();
//    numberOfWaysToPartitionASetIntoKSubsets();
//    isPalindromicSubstring();
//    palindromicSubstring();
//    longestPalindromicSubstring();
//    longestPalindromicSubsequence();
//    countPalindromicSubsequences();
//    coinChangeTargetSum();
//    knapSack();
    return 0;
}
