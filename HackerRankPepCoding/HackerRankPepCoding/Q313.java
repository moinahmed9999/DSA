import java.util.Scanner;

public class Q313 {
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

        int tar = scn.nextInt();
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

        // display(nodes[0]);
        solve(nodes[0], tar);
        System.out.println(count);
    }

    // count of subtrees with sum equal to tar
    static int count = 0;

    private static int solve(Node node, int tar) {
        if (node == null) {
            return 0;
        }
        int left = solve(node.left, tar);
        int right = solve(node.right, tar);
        int ans = node.data + left + right;
        if (ans==tar) {
            count++;
        }
        return ans;
    }

}