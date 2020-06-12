import java.util.LinkedList;
import java.util.Scanner;

public class Q317 {
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

	public static void IterativePreOrder(LinkedList<Node> processStack, LinkedList<Integer> resultStack) {
		
	}

	private static void solve(Node root) {
		LinkedList<Node> processStack = new LinkedList<>();
		LinkedList<Integer> resultStack = new LinkedList<>();

		processStack.addLast(root);

	// 	while (!processStack.isEmpty()) {
	// 		Node node=processStack.getLast();
	// 		if (node.data!=-1 && node.data!=-2) {
	// 			resultStack.addLast(node.data);
	// 			node.data=-1;
	// 			if (node.right != null) {
	// 				processStack.addLast(node.right);
	// 			}
	// 		}
	// 		else if (node.data==-1) {
	// 			node.data=-2;
	// 			if (node.left != null) {
	// 				processStack.addLast(node.left);
	// 			}
	// 		}
	// 		else if (node.data==-2) {
	// 			processStack.removeLast();
	// 		}
	// 	}

		while (!processStack.isEmpty()) {
			Node node=processStack.getLast();
			processStack.removeLast();
			resultStack.addLast(node.data);
			if (node.left!=null) {
				processStack.addLast(node.left);
			}
			if (node.right!=null) {
				processStack.addLast(node.right);
			}
		}	

		while (!resultStack.isEmpty()) {
			int res=resultStack.getLast();
			System.out.print(res + " ");
			resultStack.removeLast();
		}

	}

}