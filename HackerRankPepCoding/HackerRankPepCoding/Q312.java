import java.util.Arrays;
import java.util.HashMap;
import java.util.Scanner;

public class Q312 {
	private static class Node {
		int data;
		Node left;
		Node right;
		Node random;

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
		str += " => " + node.data + "[R:" + node.random.data + "] <= ";
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

		int size = 0;
		HashMap<Integer, Node> randomMap = new HashMap<>();

		Node[] nodes = new Node[arr.length];
		for (int i = 0; i < nodes.length; i++) {
			if (arr[i] != -1) {
				size++;
				nodes[i] = new Node(arr[i], null, null);

				if (i > 0) {
					int pi = (i - 1) / 2;

					if (i == 2 * pi + 1) {
						nodes[pi].left = nodes[i];
					} else {
						nodes[pi].right = nodes[i];
					}
				}

				randomMap.put(nodes[i].data, nodes[i]);
			}
		}

		for (int i = 0; i < size; i++) {
			int from = scn.nextInt();
			int to = scn.nextInt();
			randomMap.get(from).random = randomMap.get(to);
		}

		Node cloneRoot = clone(nodes[0]);
		display(cloneRoot);
	}

	private static Node clone(Node node) {
		// created copies of nodes between themselves and their left children
		createCloneNodesInTheTree(node);
		// using the structure, traversed and set randoms for clones
		setRandomsInClone(node);
		// cleaned the tree back, removed and collected cloned nodes.
		return clearOriginalTree(node);
	}

	private static Node createCloneNodesInTheTree(Node onode) {
		
	}

	private static void setRandomsInClone(Node onode) {
		// work
		

		// left
		
		// right
		
	}

	private static Node clearOriginalTree(Node onode) {
		// work
		
		
		// left
		

		// right
		
		
		// work
		
	}
}