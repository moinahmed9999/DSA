import java.util.Scanner;

public class Q330 {
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

        createCircularDLL(root);
        
        head.left=tail;
        tail.right=head;
        
		displayDLL(head);
    }

    // method to display the linked list
	private static void displayDLL(Node node) {
		Node head = node;
		Node tail = node.left;

		Node temp;
		for (temp = head; temp != tail; temp = temp.right) {
			System.out.print(temp.data + " -> ");
		}
		System.out.println(tail.data + " -> " + ".");

		for (temp = tail; temp != head; temp = temp.left) {
			System.out.print(temp.data + " -> ");
		}
		System.out.println(head.data + " -> " + ".");
	}

	static Node head=null;
    static Node tail=null;

    // method to create a doubly linked list
    private static void createCircularDLL(Node treeNode) {
        if (treeNode == null) {
            return;
        }

        if (treeNode.left == null && head == null) {
            head = tail = treeNode;
            createCircularDLL(treeNode.right);
            return;
        } else
            createCircularDLL(treeNode.left);

        tail.right = treeNode;
        treeNode.left = tail;
        tail = treeNode;

        createCircularDLL(treeNode.right);
    }
}