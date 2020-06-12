import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Scanner;

public class Q364 {
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
        int[] pre = new int[Integer.parseInt(scn.next())];
        for (int i = 0; i < pre.length; i++) {
            pre[i] = Integer.parseInt(scn.next());
        }
        scn.close();

        Node root = construct(pre, Integer.MIN_VALUE, Integer.MAX_VALUE);
        display(root);
    }

    static int i = 0;

    private static Node construct(int[] pre, int min, int max) {
        if (i >= pre.length || pre[i] < min || pre[i] > max) {
            return null;
        }
        Node myNode = new Node(pre[i], null, null);
        i++;
        myNode.left = construct(pre, min, myNode.data);
        myNode.right = construct(pre, myNode.data, max);
        return myNode;
    }
}