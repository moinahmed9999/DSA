import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Q350 {
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
		Node root = null;

		Scanner scn = new Scanner(System.in);
		int k = scn.nextInt();
		int data = scn.nextInt();

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
		printKAway(nodes[0], k, data);
	}

	private static int printKAway(Node node, int k, int data) {
        if (node==null) {
            return -1;
        }
        if (node.data==data) {
            printKDown(node, k);
            return 1;
        }
        int left=printKAway(node.left, k, data);
        if (left!=-1) {
            if (left==k) {
                System.out.print(node.data + " ");
            } else if (left<k) {
                printKDown(node.right, k-left-1);
            }
            return left+1;
        }
        int right=printKAway(node.right, k, data);
        if (right!=-1) {
            if (right==k) {
                System.out.print(node.data + " ");
            } else if (right<k) {
                printKDown(node.left, k-right-1);
            }
            return right+1;
        }
        return -1;
	}

	private static void printKDown(Node node, int k) {
        if (node==null) {
            return;
        }
        if (k==0) {
            System.out.print(node.data + " ");
        }
        printKDown(node.left, k-1);
        printKDown(node.right, k-1);
    }

}