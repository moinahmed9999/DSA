import java.util.Scanner;

public class Q320 {
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

        // display(nodes[0]);
        solve(nodes[0]);
    }

    // static int maxLeftLevel=-1;

    // public static void printLeftBoundary(Node node, int leftLevel) {
    //     if (node == null) {
    //         return;
    //     }
    //     if (leftLevel> maxLeftLevel) {
    //         maxLeftLevel=leftLevel;
    //     }
    //     if (!(node.left == null && node.right == null)) { // not a leaf node
    //         System.out.print(node.data + " ");
    //     }
    //     printLeftBoundary(node.left, leftLevel + 1);
    //     printLeftBoundary(node.right, leftLevel - 1);
    // }

    public static void printLeftBoundary(Node node) {
        if (node == null) {
            return;
        }
        if (node.left != null) { 
            System.out.print(node.data + " ");
            printLeftBoundary(node.left);
        }
        else if (node.right != null) {
            System.out.print(node.data + " ");
            printLeftBoundary(node.right);
        }
    }

    public static void printLeafs(Node node) {
        if (node == null) {
            return;
        }
        printLeafs(node.left);
        if (node.left == null && node.right == null) { // leaf node
            System.out.print(node.data + " ");
            return;
        }
        printLeafs(node.right);
    }

    public static void printRightBoundary(Node node) {
        if (node == null) {
            return;
        }
        if (node.right != null) { 
            printRightBoundary(node.right);
            System.out.print(node.data + " ");
        }
        else if (node.left != null) { 
            printRightBoundary(node.left);
            System.out.print(node.data + " ");
        }
    }

    private static void solve(Node node) {
        printLeftBoundary(node);
        printLeafs(node);
        printRightBoundary(node);
    }
}