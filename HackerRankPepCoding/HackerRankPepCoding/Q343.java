import java.util.Scanner;

public class Q343 {
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

		head = tail = new Node(0, null, null);
		createVerticalSumDLL(root, head);
		displayDLL();
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

	private static Node head;
	private static Node tail;

	private static void createVerticalSumDLL(Node node, Node dll) {
        if (node==null) {
            return;
        }
        dll.data+=node.data;
        if (node.left!=null) {
            if (dll.left==null) {
                dll.left=new Node(0, null, null);
                dll.left.right=dll;
                head=dll.left;
            }
            createVerticalSumDLL(node.left, dll.left);
        }
        if (node.right!=null) {
            if (dll.right==null) {
                dll.right=new Node(0, null, null);
                dll.right.left=dll;
                tail=dll.right;
            }
            createVerticalSumDLL(node.right, dll.right);
        }
	}
}