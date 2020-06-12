import java.util.LinkedList;
import java.util.Scanner;

public class Q338 {
    private static class Node {
        int data;
        Node left;
        Node right;
        Node nextRight;

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
        str += "[" + (node.nextRight != null ? node.nextRight.data : "null") + "]";

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

        setNextRight(root);
        display(root);
    }

    static Node prev;

    private static void setNextRight(Node node) {
        LinkedList<Node> queue = new LinkedList<>();
        queue.addLast(node);
        queue.addLast(null);
        while (!queue.isEmpty()) {
            Node x;
            x = queue.removeFirst();
            if (x == null) {
                if (!queue.isEmpty())
                    queue.addLast(null);
            } else {
                x.nextRight = queue.get(0);
                if (x.left != null) {
                    queue.addLast(x.left);
                }
                if (x.right != null) {
                    queue.addLast(x.right);
                }
            }
        }
    }
}