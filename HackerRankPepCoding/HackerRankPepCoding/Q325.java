import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Scanner;

public class Q325 {
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
        Scanner scn = new Scanner(System.in);
        int[] arr = new int[scn.nextInt()];
        for (int i = 0; i < arr.length; i++) {
            arr[i] = scn.nextInt();
        }
        scn.close();

        Node root = construct(arr);
        if (root == null) {
            System.out.println("Invalid");
        } else {
            display(root);
        }
    }

    private static Node construct(int[] arr) {
        Node rootNode = null;
        Node[] nodes = new Node[arr.length];
        for (int i = 0; i < nodes.length; i++) {
            nodes[i] = new Node(i, null, null);
        }
        for (int i = 0; i < nodes.length; i++) {
            if (arr[i] == -1) {
                rootNode = nodes[i];
            } else if (nodes[arr[i]].left == null) {
                nodes[arr[i]].left = nodes[i];
            } else if (nodes[arr[i]].right == null) {
                nodes[arr[i]].right = nodes[i];
            } else {
                rootNode=null;
                return rootNode;
            }
        }
        return rootNode;
    }

}
