import java.util.LinkedList;
import java.util.Scanner;

public class Q316 {
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

		solve(nodes[0]);
	}

	private static void solve(Node root) {
        Node currNode=root;
        while(currNode!=null) {
            Node next=currNode.left;
            if(next!=null) {
                Node nextRight=leftsRightmost(next,currNode);
                if(nextRight.right!=currNode) {
                    nextRight.right=currNode;
                    System.out.print(currNode.data + " ");
                    currNode=next;
                }else {
                    nextRight.right=null;
                    currNode=currNode.right;
                }
            }else {
                System.out.print(currNode.data + " ");
                currNode=currNode.right;
            }
        }
    }

    private static Node leftsRightmost(Node node,Node currNode) {
        Node temp=node;
        while(temp.right!=null && temp.right!=currNode) {
            temp=temp.right;
        }
        return temp;
    }
}