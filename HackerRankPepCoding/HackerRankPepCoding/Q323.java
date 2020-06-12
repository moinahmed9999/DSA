import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;

public class Q323 {

    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);

        int n = scn.nextInt();
        int[][] arr = new int[n][n];
        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j < arr[i].length; j++) {
                arr[i][j] = scn.nextInt();
            }
        }
        scn.close();

        System.out.println(solve(arr));
    }

    public static int powerOf2(int x) {
        int a = 1;
        while ((x--) > 0) {
            a *= 2;
        }
        return a;
    }

    public static int solve(int[][] arr) {
        int pow = 0;
        for (int i = 0; i < arr.length; i++) {
            int flag = 0;
            for (int j = 0; j < arr[i].length; j++) {
                if (arr[i][j] == 1)
                    flag++;
            }
            if (flag > 0) {
                pow++;
            }
        }
        return powerOf2(pow);
    }
}