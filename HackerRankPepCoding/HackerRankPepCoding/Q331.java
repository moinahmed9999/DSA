import java.util.Scanner;

public class Q331 {
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
        str += " <= " + node.data + " => ";
        str += node.right == null ? "." : node.right.data;

        System.out.println(str);

        display(node.left);
        display(node.right);
    }

    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);
        int[] arr = new int[scn.nextInt()];
        for (int i = 0; i < arr.length; i++) {
            arr[i] = scn.nextInt();
        }
        scn.close();

        // creation using the level order, seeing it like a heap
        // -1 says there is no node
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
        Node root = nodes[0];
        // display(root);

        Pair pair = countMaximumEdgeRemovalForEvenNodesForest(root);
        System.out.println(pair.edgeRemovals);
    }

    private static class Pair {
        int edgeRemovals;
        int countNodes;

        Pair(int edgeRemovals, int countNodes) {
            this.edgeRemovals = edgeRemovals;
            this.countNodes = countNodes;
        }
    }

    private static Pair countMaximumEdgeRemovalForEvenNodesForest(Node node) {
        Pair pair=new Pair(0, 0);
        if (node==null) {
            return pair;
        }
        pair.countNodes++;
        if (node.left!=null) {
            Pair left=countMaximumEdgeRemovalForEvenNodesForest(node.left);
            pair.edgeRemovals+=left.edgeRemovals;
            if (left.countNodes%2==0) {
                pair.edgeRemovals++;
            }else
                pair.countNodes+=left.countNodes;
        }
        if (node.right!=null) {
            Pair right=countMaximumEdgeRemovalForEvenNodesForest(node.right);
            pair.edgeRemovals+=right.edgeRemovals;
            if (right.countNodes%2==0) {
                pair.edgeRemovals++;
            }else
                pair.countNodes+=right.countNodes;
        }
        return pair;
    }

}