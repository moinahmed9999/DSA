import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;

public class Q318 {
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

	public static int leftWidth(Node node) {
		if (node == null) {
			return 0;
		}

		int left = leftWidth(node.left);
		int right = leftWidth(node.right) - 1;

		return Math.max(left, right) + 1;
	}

	// public static class queueElement {
	// 	Node node;
	// 	int diagonalLevel;

	// 	queueElement(Node node, int diagonalLevel) {
	// 		this.node = node;
	// 		this.diagonalLevel = diagonalLevel;
	// 	}
	// }

	public static void diagonalTraversal(Node node, int diagonalLevel, LinkedList<Integer>[] answer) {
		if (node == null) {
			return;
		}
		answer[diagonalLevel].addLast(node.data);
		diagonalTraversal(node.left, diagonalLevel +1, answer);
		diagonalTraversal(node.right, diagonalLevel , answer);
	}

	public static void printDiagonalTraversal(Node node, int diagonalLevel, LinkedList<Integer>[] answer) {
		if (node == null) {
			return;
		}

		// Commented code is for Level Order wise printing of elements and non commented one is for preorder wise

		// LinkedList<queueElement> queue = new LinkedList<>();
		// queueElement element = new queueElement(node, diagonalLevel);
		// queue.addLast(element);
		// while (!queue.isEmpty()) {
		// 	element = queue.removeFirst();
		// 	Node x = element.node;
		// 	int level = element.diagonalLevel;
			
		// 	answer[level].addLast(x.data);
		// 	if (x.left != null) {
		// 		queue.addLast(new queueElement(x.left, level + 1));
		// 	}
		// 	if (x.right != null) {
		// 		queue.addLast(new queueElement(x.right, level));
		// 	}
		// }

		diagonalTraversal(node, diagonalLevel, answer);

		for (int i = 0; i < answer.length; i++) {
			for(int j=0;j<answer[i].size();j++) {
				System.out.print(answer[i].get(j) + " ");
			}
			System.out.println();
		}
	}

	private static void solve(Node node) {
		int width = leftWidth(node);
		LinkedList<Integer>[] answer = new LinkedList[width];
		for(int i=0;i<width;i++) {
			answer[i]=new LinkedList<>();
		}
		printDiagonalTraversal(node, 0, answer);
	}

}