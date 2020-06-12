import java.io.*;
import java.util.*;

public class Q314 {
    
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
//        display(root);

        inorderIteratively(new NodeForStack(root));
    }
    
    public static class NodeForStack {

        Node node;
        boolean selfDone = false;
        boolean leftDone = false;
        boolean rightDone = false;

        NodeForStack(Node node) {
            this.node = node;
            this.selfDone = false;
            this.leftDone = false;
            this.rightDone = false;
        }
    }
    
    public static void inorderIteratively(NodeForStack root) {
        LinkedList<NodeForStack> stack = new LinkedList<>();
        stack.addFirst(root);
        while (!stack.isEmpty()) {
            NodeForStack temp = stack.getFirst();
            if (temp.leftDone == false) {
                temp.leftDone = true;
                if (temp.node.left != null) {
                    stack.addFirst(new NodeForStack(temp.node.left));
                }
            } else if (temp.selfDone == false) {
                System.out.print(temp.node.data + " ");
                temp.selfDone = true;
            } else if (temp.rightDone == false) {
                temp.rightDone = true;
                if (temp.node.right != null) {
                    stack.addFirst(new NodeForStack(temp.node.right));
                }
            } else {
                stack.removeFirst();
            }
        }
    }
}