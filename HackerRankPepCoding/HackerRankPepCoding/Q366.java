import java.util.Collections;
import java.util.LinkedList;
import java.util.Scanner;

public class Q366 {
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

		root = convertBSTToMinHeap(root);
		display(root);
	}

	private static Node convertBSTToMinHeap(Node node) {
        convertBSTToSortedCircularLL(node);
		return convertSortedCircularLLToMinHeap();
    }
    
    static Node head=null;
    static Node tail=null;

	private static void convertBSTToSortedCircularLL(Node node) {
        if (node==null) {
            return;
        }

        if (node.left==null && head==null) {
            head=tail=node;
            tail.left=null;
            convertBSTToSortedCircularLL(node.right);
            return;
        } else {
            convertBSTToSortedCircularLL(node.left);
        }

        tail.right=node;
        node.left=tail;
        tail=node;

        convertBSTToSortedCircularLL(node.right);
    }

	private static Node convertSortedCircularLLToMinHeap() {
		Node root=head;
		head=head.right;
		root.right=null;
		head.left=null;
		LinkedList<Node> queue=new LinkedList<>();
		queue.addLast(root);
		while (head!=null) {
			Node node=queue.removeFirst();

			Node leftNode=head;
			head=head.right;
			leftNode.right=null;
			head.left=null;
			node.left=leftNode;
			queue.addLast(leftNode);

			Node rightNode=head;
			head=head.right;
			rightNode.right=null;
			node.right=rightNode;
			queue.addLast(rightNode);
		}
		queue.clear();
		return root;
	}

}