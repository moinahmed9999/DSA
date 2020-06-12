public class dp {

    // fibonacci ----------------------------------------------------

    public static int fibonacciRecursion(int n) {
        if (n<=1) {
            return n;
        }
        return fibonacciRecursion(n-1) + fibonacciRecursion(n-2);
    }

    public static int fibonacciMemoization(int n, int dp[]) {
        if (n<=1) {
            dp[n] = n;
            return n;
        }
        if (dp[n]!=0) {
            return dp[n];
        }
        dp[n] = fibonacciMemoization(n-1, dp) + fibonacciMemoization(n-2, dp);
        return dp[n];
    }

    public static int fibonacciTabulation(int n, int dp[]) {
        for (int i = 0; i < n; i++) {
            if (i<=1) {
                dp[i] = i;
                continue;
            }
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }

    public static void fibonacci() {
        int n = 9;
        System.out.println(fibonacciRecursion(n));
        int[] dp = new int[n+1];
        System.out.println(fibonacciMemoization(n, dp));
        System.out.println(fibonacciTabulation(n, dp));
    }

    // maze path ----------------------------------------------------

    public static int mazePathThreeMovesRecursion(int r, int c, int n) {
        if (r==n-1 && c==n-1) {
            return 1;
        }
        int count = 0;
        if (c+1<n) {
            count+=mazePathThreeMovesRecursion(r, c+1, n);
        }
        if (r+1<n) {
            count+=mazePathThreeMovesRecursion(r+1, c, n);
        }
        if (r+1<n && c+1<n) {
            count+=mazePathThreeMovesRecursion(r+1, c+1, n);
        }
        return count;
    }

    public static int mazePathThreeMovesMemoization(int r, int c, int n, int[][] dp) {
        if(r==n-1 && c==n-1) {
            dp[r][c] = 1;
            return dp[r][c];
        }
        if (dp[r][c]!=0) {
            return dp[r][c];
        }
        if (c+1<n) {
            dp[r][c]+=mazePathThreeMovesMemoization(r, c+1, n, dp);
        }
        if (r+1<n) {
            dp[r][c]+=mazePathThreeMovesMemoization(r+1, c, n, dp);
        }
        if (r+1<n && c+1<n) {
            dp[r][c]+=mazePathThreeMovesMemoization(r+1, c+1, n, dp);
        }
        return dp[r][c];
    }

    public static int mazePathThreeMovesTabulation(int n, int[][] dp) {
        for (int i = n-1; i >=0; i--) {
            for (int j = n-1; j >=0; j--) {
                if (i==n-1 && j==n-1) {
                    dp[i][j]=1;
                    continue;
                }
                if (j+1<n) {
                    dp[i][j] += dp[i][j+1];
                }
                if (i+1<n) {
                    dp[i][j] += dp[i+1][j];
                }
                if (i+1<n && j+1<n) {
                    dp[i][j] += dp[i+1][j+1];
                }
            }
        }
        return dp[0][0];
    }

    public static void mazePath() {
        int n=4;
        int sr=0, sc=0;
        System.out.println(mazePathThreeMovesRecursion(sr, sc, n));
        int[][] dp = new int[n][n];
        // System.out.println(mazePathThreeMovesMemoization(sr, sc, n, dp));
        System.out.println(mazePathThreeMovesTabulation(n, dp));
    }

    public static void main(String[] args) {
        // fibonacci();
        mazePath();
    }
}