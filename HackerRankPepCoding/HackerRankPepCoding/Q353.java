import java.util.Scanner;

public class Q353 {
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
		// Node root = null;

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

//		 display(nodes[0]);
		Pair pair = solve2(nodes[0]);
		System.out.println(pair.tilt);
	}

	private static class Pair {
		int sum;
        int tilt;
        Pair (int sum,int tilt) {
            this.sum=sum;
            this.tilt=tilt;
        }
	}

	// return two things at a time
	public static Pair solve2(Node node){
        if (node==null) {
            return new Pair(0,0);
        }
        Pair leftPair=solve2(node.left);
        Pair rightPair=solve2(node.right);
        int myTilt=leftPair.sum -rightPair.sum;
        myTilt=Math.abs(myTilt);
        Pair ans=new Pair(leftPair.sum + rightPair.sum + node.data, myTilt + leftPair.tilt + rightPair.tilt);
        return ans;
	}

}