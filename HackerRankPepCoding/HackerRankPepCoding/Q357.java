import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;

public class Q357 {
    private static class Node {
        char data;
        Node left;
        Node right;

        Node(char data, Node left, Node right) {
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
        String postfix = scn.nextLine();
        scn.close();
        i=postfix.length();
        Node root = construct(postfix);
        display(root);
    }

    public static boolean isOperator(char ch) {
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            return true;
        }
        return false;
    }
    
    static int i;

	private static Node construct(String postfix){
        i--;
        Node myNode=new Node(postfix.charAt(i),null, null);
        if (isOperator(postfix.charAt(i))){
            myNode.right=construct(postfix);
            myNode.left=construct(postfix);
            
        }
        return myNode;
	}
}