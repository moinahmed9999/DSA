import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;

public class Q340 {
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
//		display(root);

		int width1 = solveLevelWay(root);
        solvePreorderWay(root, 0);
        for (int i = 0; i < lwmap.size(); i++) {
            if (lwmap.get(i)>width) {
                width=lwmap.get(i);
            }
        }
		System.out.println(width1 + " " + width);
	}

	private static int solveLevelWay(Node root){
        if (root==null) {
            return 0;
        }
        LinkedList<Node> queue = new LinkedList<>();
        int maxWidth=0;
        queue.addLast(root);
        while (!queue.isEmpty()) {
            int size = queue.size();
            if (size>maxWidth) {
                maxWidth=size;
            }
            while (size-- > 0) {
                Node x = queue.removeFirst();
                if (x.left != null) {
                    queue.addLast(x.left);
                }
                if (x.right != null) {
                    queue.addLast(x.right);
                }
            }
        }
        return maxWidth;
	}

    static int width = Integer.MIN_VALUE;
    static HashMap<Integer, Integer> lwmap=new HashMap<>();
	private static void solvePreorderWay(Node node, int level){
        if (node==null) {
            return;
        }
        lwmap.put(level, lwmap.getOrDefault(level, 0) +1);
        solvePreorderWay(node.left, level+1);
        solvePreorderWay(node.right, level+1);
	}

}