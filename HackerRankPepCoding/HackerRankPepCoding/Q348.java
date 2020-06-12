import java.util.HashMap;
import java.util.Scanner;

import javax.print.DocFlavor.CHAR_ARRAY;

public class Q348 {
	private static class Node {
		char data;
		Node left;
		Node right;
		boolean isRoot = true;

		Node(char data, Node left, Node right, boolean isRoot) {
			this.data = data;
			this.left = left;
            this.right = right;
            this.isRoot=isRoot;
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

		String str1 = scn.nextLine();
        String str2 = scn.nextLine();
        
        scn.close();

		solve(str1, str2);
	}

	private static void solve(String str1, String str2){
		HashMap<Character, Node> map = new HashMap<>();
		populateMap(str1, map);
		populateMap(str2, map);

        for (int i = 0; i < str2.length(); i++) {
            Node node1=map.get(str1.charAt(i));
            Node node2=map.get(str2.charAt(i));
            node2.isRoot=false;
            if (node1.left==null) {
                node1.left=node2;
            } else {
                node1.right=node2;
            }
        }

        for (int i = 0; i < str1.length(); i++) {
            if (map.get(str1.charAt(i)).isRoot==true) {
                display(map.get(str1.charAt(i)));
                map.get(str1.charAt(i)).isRoot=false;
                System.out.println();
            }
        }

	}

	// a node against each unique char
	private static void populateMap(String str, HashMap<Character, Node> map){
        for (int i = 0; i < str.length(); i++) {
            map.put(str.charAt(i), map.getOrDefault(str.charAt(i), new Node(str.charAt(i), null, null, true)));
        }
	}

}