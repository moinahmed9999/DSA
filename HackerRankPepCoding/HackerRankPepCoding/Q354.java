import java.util.HashMap;
import java.util.Scanner;

import javax.print.DocFlavor.CHAR_ARRAY;

public class Q354 {
	public static void main(String[] args) {
		Scanner scn = new Scanner(System.in);
		int[] parr = new int[scn.nextInt()];
		for (int i = 0; i < parr.length; i++) {
			parr[i] = scn.nextInt();
        }
        scn.close();

		int height = solve(parr);
		System.out.println(height);
	}

	private static int solve(int[] parr) {
        int[] harr = new int[parr.length];
        for (int i = 0; i < harr.length; i++) {
            harr[i]=0;
        }
        int level=0;
        for (int i = 0; i < parr.length; i++) {
            if (parr[i]==-1) {
                level=getLevel(parr, harr, i);
                break;
            }
        }
        return level;
	}

	private static int getLevel(int[] parr, int[] harr, int i) {
        int flag=0;
        for (int j = 0; j < parr.length && flag<2; j++) {
            if (parr[j]==i) {
                flag++;
                int level=getLevel(parr, harr, j);
                if (harr[i]==0) {
                    harr[i]+=level+1;
                }
                else {
                    harr[i]=Math.max(harr[i], level+1);
                }
            }
        }
        return harr[i];
	}
}