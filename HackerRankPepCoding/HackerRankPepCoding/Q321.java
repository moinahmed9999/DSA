import java.util.LinkedList;
import java.util.Scanner;

public class Pep_JavaIP_10BinaryTrees_321SpecialLevelOrder_PBT {

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
		int[] arr = new int[scn.nextInt()];
		for (int i = 0; i < arr.length; i++) {
			arr[i] = scn.nextInt();
		}

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
		solve(nodes[0],arr);
	}

	public static int powerOf2(int x) {
		int a=1;
		while ((x--)>0) {
			a*=2;
		}
		return a;
	}

	public static int findLevels(int arrayLength) {
		int i=0;
		while (arrayLength>0) {
			if (powerOf2(i+1)-1 == arrayLength) {
				return i+1;
			}
			i++;
		}
		return 1;
	}

	public static void printLevel(int start,int end, int[] arr) {
		if (start==0) {
			System.out.print(arr[start] + " ");
			return;
		}
		while (start < end) {
			System.out.print(arr[start] + " " + arr[end] + " ");
			start++;
			end--;
		}
	}

	private static void solve(Node root,int[] arr) {
		int levels=findLevels(arr.length);
		for (int i = 0; i < levels; i++) {
			int start=powerOf2(i)-1;
			int end=start*2;
			printLevel(start, end, arr);
		}
	}

}