import java.util.Scanner;

public class Q346 {
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
		// display(root);

		root = extractLeavesDLL(root);
		displayDLL();
		display(root);
	}

	// method to display the linked list
	private static void displayDLL() {
		Node temp;
		for (temp = head; temp != null; temp = temp.right) {
			System.out.print(temp.data + " -> ");
		}
		System.out.println(".");

		for (temp = tail; temp != null; temp = temp.left) {
			System.out.print(temp.data + " -> ");
		}
		System.out.println(".");
	}

	private static Node head=null;
	private static Node tail=null;

	// extract leaves in a doubly linked list
	private static Node extractLeavesDLL(Node node) {
        if (node==null) {
            return null;
        }
        if (node.left==null && node.right==null) {
            if (head==null) {
                head=tail=node;
            } else {
                tail.right=node;
                node.left=tail;
                tail=node;
            }
            return null;
        }
        node.left=extractLeavesDLL(node.left);
        node.right=extractLeavesDLL(node.right);
        return node;
	}
}