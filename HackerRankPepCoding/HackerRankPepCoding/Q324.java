import java.util.ArrayList;
import java.util.Scanner;

public class Q324 {
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
	
	public static void displayAncestorMatrix(boolean[][] am){
		for(int row = 0; row < am.length; row++){
			for(int col = 0; col < am[row].length; col++){
				System.out.print(am[row][col] + " ");
			}
			System.out.println();
		}
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
		int size = 0;
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
				
				size++;
			}
		}

		// display(nodes[0]);
		boolean[][] am = new boolean[size][size];
		solve(nodes[0], am, new ArrayList<>());
		displayAncestorMatrix(am);
	}
	
	private static ArrayList<Integer> solve(Node node, boolean[][] am, ArrayList<Integer> pathFromRoot){
		if (node==null) {
			return pathFromRoot;
		}
		ArrayList<Integer> leftChildren=solve(node.left, am, new ArrayList<>());
		ArrayList<Integer> rightChildren=solve(node.right, am, new ArrayList<>());
		for (Integer integer : leftChildren) {
			am[node.data][integer]=true;
			pathFromRoot.add(integer);
		}
		for (Integer integer : rightChildren) {
			am[node.data][integer]=true;
			pathFromRoot.add(integer);
		}
		pathFromRoot.add(node.data);
		return pathFromRoot;
	}
}