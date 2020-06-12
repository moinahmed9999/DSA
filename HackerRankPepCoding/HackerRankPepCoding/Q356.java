import java.util.Scanner;

public class Q356 {
    private static class Node {
        int data;
        Node left;
        Node right;

        Node(int data, Node left, Node right) {
            this.data = data;
            this.left = left;
            this.right = right;
        }
    }

    public static void display(Node node) {
        if (node == null) {
            return;
        }

        String str = "";

        str += node.left == null ? "." : node.left.data;
        str += " => " + node.data + " <= ";
        str += node.right == null ? "." : node.right.data;

        System.out.println(str);

        display(node.left);
        display(node.right);
    }

    public static void main(String[] args) {
        // Node root = null;

        Scanner scn = new Scanner(System.in);

        int[] arr = new int[scn.nextInt()];
        for (int i = 0; i < arr.length; i++) {
            arr[i] = scn.nextInt();
        }
        scn.close();
        Node[] nodes = new Node[arr.length];
        for (int i = 0; i < nodes.length; i++) {
            if (arr[i] != -1) {
                nodes[i] = new Node(arr[i], null, null);

                if (i > 0) {
                    int pi = (i - 1) / 2;

                    if (i == 2 * pi + 1) {
                        nodes[pi].left = nodes[i];
                    } else {
                        nodes[pi].right = nodes[i];
                    }
                }
            }
        }

        // Pair pair = maxPathSum(nodes[0]);
        // System.out.println(mpspath);
        maxPathSum(nodes[0]);
        System.out.println(mps);
    }

    // private static class Pair {
    // int mpsrooted = 0;
    // String mpsrootedpath = "";
    // }

    static int mps = Integer.MIN_VALUE;
    // static String mpspath = "";

    private static int maxPathSum(Node node) {
        if (node == null) {
            return 0;
        }
        int left = maxPathSum(node.left);
        int right = maxPathSum(node.right);
        int ans = Math.max(node.data, node.data + Math.max(left, right));
        mps=Math.max(mps, Math.max(node.data + left + right, ans));
        return ans;
    }
}