import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;

public class BTree {

	public static void main(String[] args) {
		// int[] arr = { -15, 5, -8, 2, -1, -1, 6, -1, -1, 3, -1, -1, 6, 3, -1, -1, 9,
		// -1, 0, 4, -1, -1, 7, 10, -1, -1,-1 };
		// int[] arr = { -15, 10, 4, -10, -1, -1, -1, -2, -1, 4, -1, -1, 2, 1, -1, -1,
		// 100, -50, -1, -1, -1 };
		// int[] arr = {-2,-5,-1,-1,100,-3,-1,-1,-4,-1,-1};
		// int[] arr = { 30, 28, 15, -1, -1, 25, 22, -1, -1, 20, -1, -1, 45, 40, -1, -1,
		// 50, -1, -1 };
		// int[] arr = { 50, 25, 20, 30, 75, 65 };
		// int[] arr = { 10, 20, 40, 50, -1, -1, 60, -1, -1, 50, 70, -1, -1, 80, 140,
		// -1, -1, -1, 30, 60, -1, 90, -1, -1,
		// 70, 100, -1, -1, 110, -1, -1 };
		// int[] arr = { 10, 20, 40, -1, 20, -1, -1, -1, 30, 50, -1, -1, 60, -1, 70, 80,
		// -1, -1, -1 };
		int[] arr = { 1, 2, 4, -1, -1, 5, -1, -1, 3, 6, 8, -1, -1, 9, -1, 10, -1, -1, 7, -1, -1 };
		Node rootNode;
		rootNode = creatNode(arr);
		// display(rootNode);
		/*
		 * // System.out.println(height(rootNode)); //
		 * System.out.println(size(rootNode)); // System.out.println(find(rootNode,
		 * 60)); // ArrayList<Node> arrayList=rootToNodePath(rootNode, 100); //
		 * displayPath(arrayList); // LCA(rootNode, 30, 40); //
		 * System.out.println(diameter1(rootNode)); // int[] array=diameter2(rootNode);
		 * // System.out.println(array[0]); // levelOrder(rootNode); // kaway(rootNode,
		 * 2, null); // kfar_01(rootNode, 3, 70); // kfar_02(rootNode, 3, 70); //
		 * linearize(rootNode); // display(rootNode); // BSTPair pair =
		 * BSTSol(rootNode); // System.out.println(pair.isBST + " " + pair.countOfBST +
		 * " " + pair.lBSTSize + // " " + pair.lBSTRoot.data); // DLL(rootNode); //
		 * while (head_ != null) { // System.out.print(head_.data + " "); // head_ =
		 * head_.right; // } // maxSumLeafToLeaf(rootNode); //
		 * System.out.println(maxPathSum); // maxSumNodeToNode_01(rootNode); //
		 * System.out.println(maxPathSum); // maxSumNodeToNode_02(rootNode); //
		 * System.out.println(maxPathSum); recoverBST(rootNode);
		 * System.out.println(Node1.data + " " + Node2.data);
		 */
		// for (int i = 0; i < arrayList.length; i++) {
		// arrayList[i] = new LinkedList<>();
		// }
		// verticalOrder(rootNode, 3, 0);
		// displayVerticalOrder();
		// System.out.println(PathSumI(rootNode, 90, ""));
		// System.out.println(PathSumII_01(rootNode, 90));

		// int[] arr = { 10, 20, 30, 40, 50, 60, 70, 80, 90};
		// rootNode = createBstFromSortedArray(arr, 0, 8);
		// rootNode = insertInBST(rootNode, 35);
		// rootNode = removeFromBST(rootNode, 50);
		// display(rootNode);

		// int[] arr = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };
		// rootNode = createBstFromSortedArray(arr, 0, 8);
		// Node node = LCA_BST(rootNode, 40, 60);
		// System.out.println(node.data);

		// int[] arr = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };
		// rootNode = createBstFromSortedArray(arr, 0, 8);
		// printInRange(rootNode, 30, 60);

		// verticalOrderSum(rootNode, 2);
		// for (int i : verticalSumArray) {
		// System.out.print(i + " ");
		// }

		// System.out.println("");

		// diagonalOrderSum(rootNode, 2);
		// for (int i : diagonalSumArray) {
		// System.out.print(i + " ");
		// }

		// InorderMorrisTraversal(rootNode);
		// PreorderMorrisTraversal(rootNode);

		preorderIteratively(new NodeForStack(rootNode));
	}

	public static class Node {

		int data = 0;
		Node left = null;
		Node right = null;

		Node() {

		}

		Node(int data, Node left, Node right) {
			this.data = data;
			this.left = left;
			this.right = right;
		}
	}

	public static int idx = 0;

	public static Node creatNode(int[] arr) {
		if (idx == arr.length || arr[idx] == -1) {
			idx++;
			return null;
		}
		Node node = new Node(arr[idx], null, null);
		idx++;
		node.left = creatNode(arr);
		node.right = creatNode(arr);
		return node;
	}

	public static void display(Node node) {
		if (node == null)
			return;
		String string = "";
		string += node.left == null ? " . " : node.left.data;
		string += " -> " + node.data + " <- ";
		string += node.right == null ? " . " : node.right.data;
		System.out.println(string);
		display(node.left);
		display(node.right);
	}

	public static int height(Node node) {
		if (node == null)
			return 0;
		return Math.max(height(node.left), height(node.right)) + 1;
	}

	public static int size(Node node) {
		if (node == null)
			return 0;
		return size(node.left) + size(node.right) + 1;
	}

	public static boolean find(Node node, int data) {
		if (node == null)
			return false;
		if (node.data == data)
			return true;
		boolean res = false;
		res = res || find(node.left, data);
		res = res || find(node.right, data);
		return res;
	}

	public static ArrayList<Node> rootToNodePath(Node node, int data) {
		if (node == null)
			return null;
		if (node.data == data) {
			ArrayList<Node> arrayList = new ArrayList<>();
			arrayList.add(node);
			return arrayList;
		}
		ArrayList<Node> left = rootToNodePath(node.left, data);
		if (left != null) {
			left.add(node);
			return left;
		}
		ArrayList<Node> right = rootToNodePath(node.right, data);
		if (right != null) {
			right.add(node);
			return right;
		}
		return null;
	}

	public static void displayPath(ArrayList<Node> arrayList) {
		for (int i = 0; i < arrayList.size(); i++) {
			System.out.print(arrayList.get(i).data + " ");
		}
		System.out.println("");
	}

	public static void LCA(Node root, int data1, int data2) {
		ArrayList<Node> list1 = rootToNodePath(root, data1);
		ArrayList<Node> list2 = rootToNodePath(root, data2);
		int prev = -1;
		for (int i = list1.size() - 1, j = list2.size() - 1; i >= 0 && j >= 0; i--, j--) {
			if (list1.get(i) == list2.get(j)) {
				prev = list1.get(i).data;
			} else
				break;
		}
		System.out.println(prev);
	}

	public static int diameter1(Node node) {
		if (node == null)
			return 0;
		int dl = diameter1(node.left);
		int dr = diameter1(node.right);

		int hl = height(node.left);
		int hr = height(node.right);

		return Math.max(Math.max(dl, dr), hl + hr + 1);
	}

	public static int[] diameter2(Node node) {
		if (node == null) {
			int[] arr = new int[2];
			return arr;
		}

		int[] left = diameter2(node.left);
		int[] right = diameter2(node.right);

		int[] myAns = new int[2];
		myAns[0] = Math.max(Math.max(left[0], right[0]), left[1] + right[1] + 1);// diameter
		myAns[1] = Math.max(left[1], right[1]) + 1; // height

		return myAns;
	}

	static int dia = 0;

	public static int diameter3(Node node) {
		if (node == null) {
			return 0;
		}

		int left = diameter3(node.left);
		int right = diameter3(node.right);

		dia = Math.max(dia, left + right + 1);
		return Math.max(left, right) + 1;

	}

	public static void levelOrder(Node node) {
		LinkedList<Node> list = new LinkedList<>();
		int level = 0;
		list.addLast(node);
		while (!list.isEmpty()) {
			int size = list.size();
			System.out.print("Level " + level + " : ");
			while (size-- > 0) {
				Node newNode = list.removeFirst();
				System.out.print(newNode.data + " ");

				if (newNode.left != null)
					list.addLast(newNode.left);

				if (newNode.right != null)
					list.addLast(newNode.right);
			}
			level++;
			System.out.println("");
		}
	}

	public static void kaway(Node node, int k, Node rnode) {
		if (node == null) {
			return;
		}
		if (node == rnode) {
			return;
		}
		if (k == 0) {
			System.out.print(node.data + " ");
			return;
		}
		kaway(node.left, k - 1, rnode);
		kaway(node.right, k - 1, rnode);
	}

	public static void kfar_01(Node node, int k, int data) {
		ArrayList<Node> arrayList = rootToNodePath(node, data);
		Node rnode = null;
		for (int i = 0; i < arrayList.size(); i++) {
			kaway(arrayList.get(i), k - i, rnode);
			rnode = arrayList.get(i);
		}
	}

	public static int kfar_02(Node node, int k, int data) {
		if (node == null) {
			return -1;
		}
		if (node.data == data) {
			kaway(node, k, null);
			return 1;
		}

		int left = kfar_02(node.left, k, data);
		if (left != -1) {
			if (left == k) {
				System.out.print(node.data + " ");
			} else
				kaway(node, k - left, node.left);
			return left + 1;
		}

		int right = kfar_02(node.right, k, data);
		if (right != -1) {
			if (right == k) {
				System.out.print(node.data + " ");
			} else
				kaway(node, k - right, node.right);
			return right + 1;
		}

		return -1;
	}

	static int prev = (int) -1e8;

	public static boolean isBST(Node node) {
		if (node == null) {
			return true;
		}

		if (!isBST(node.left)) {
			return false;
		}

		if (prev > node.data) {
			return false;
		}
		prev = node.data;

		if (!isBST(node.right)) {
			return false;
		}

		return true;
	}

	public static class BSTPair {
		boolean isBST = true;
		int countOfBST = 0;
		int lBSTSize = 0;
		Node lBSTRoot = null;

		int max = (int) -1e8;
		int min = (int) 1e8;
	}

	public static BSTPair BSTSol(Node node) {
		if (node == null) {
			return new BSTPair();
		}

		BSTPair lp = BSTSol(node.left);
		BSTPair rp = BSTSol(node.right);

		BSTPair myPair = new BSTPair();
		myPair.countOfBST = lp.countOfBST + rp.countOfBST;
		if (lp.isBST && rp.isBST && node.data > lp.max && node.data < rp.min) {
			myPair.countOfBST++;
			myPair.lBSTSize = lp.lBSTSize + rp.lBSTSize + 1;
			myPair.lBSTRoot = node;
		} else {
			myPair.isBST = false;
			myPair.lBSTSize = Math.max(lp.lBSTSize, rp.lBSTSize);
			if (lp.lBSTSize > rp.lBSTSize) {
				myPair.lBSTRoot = lp.lBSTRoot;
			} else
				myPair.lBSTRoot = rp.lBSTRoot;
		}

		myPair.min = Math.min(Math.min(lp.min, rp.min), node.data);
		myPair.max = Math.max(Math.max(lp.max, rp.max), node.data);

		return myPair;
	}

	public static Node linearize(Node node) {
		if (node == null)
			return null;
		if (node.left == null && node.right == null) {
			return node;
		}
		Node leftTail = linearize(node.left);
		Node rightTail = linearize(node.right);
		if (leftTail == null) {
			node.left = node.right;
		} else {
			leftTail.left = node.right;
		}
		node.right = null;
		return rightTail != null ? rightTail : leftTail;
	}

	static Node prev_ = null, head_ = null;

	public static void DLL(Node node) {
		if (node == null)
			return;

		DLL(node.left);

		if (prev_ == null)
			head_ = node;
		else {
			node.left = prev_;
			prev_.right = node;
		}
		prev_ = node;
		DLL(node.right);
	}

	public static boolean PathSumI(Node node, int target, String ans) {
		if (node == null)
			return false;

		if (node.left == null && node.right == null && target == node.data) {
			System.out.println(ans + node.data);
			return true;
		}

		boolean res = false;
		res = res || PathSumI(node.left, target - node.data, ans + node.data + " ");
		res = res || PathSumI(node.right, target - node.data, ans + node.data + " ");

		return res;
	}

	public static ArrayList<ArrayList<Integer>> PathSumII_01(Node node, int target) {
		if (node == null) {
			return new ArrayList<ArrayList<Integer>>();
		}

		ArrayList<ArrayList<Integer>> myAns = new ArrayList<>();

		if (node.left == null && node.right == null && target == node.data) {
			ArrayList<Integer> ans = new ArrayList<>();
			ans.add(0, node.data);
			myAns.add(ans);
			return myAns;
		}

		ArrayList<ArrayList<Integer>> leftAns = PathSumII_01(node.left, target - node.data);
		if (leftAns.size() > 0) {
			for (ArrayList<Integer> arrayList : leftAns) {
				arrayList.add(0, node.data);
				myAns.add(arrayList);
			}
		}

		ArrayList<ArrayList<Integer>> rightAns = PathSumII_01(node.right, target - node.data);
		if (rightAns.size() > 0) {
			for (ArrayList<Integer> arrayList : rightAns) {
				arrayList.add(node.data);
				myAns.add(arrayList);
			}
		}

		return myAns;
	}

	public static int PathSumIII(Node node, int prefixSum, int target, HashMap<Integer, Integer> map) {
		if (node == null) {
			return 0;
		}

		prefixSum += node.data;
		int count = map.getOrDefault(prefixSum - target, 0);

		map.put(prefixSum, map.getOrDefault(prefixSum, 0) + 1);

		count += PathSumIII(node.left, prefixSum, target, map);
		count += PathSumIII(node.right, prefixSum, target, map);

		if (map.get(prefixSum) == 1) {
			map.remove(prefixSum);
		} else {
			map.put(prefixSum, map.get(prefixSum) - 1);
		}
		return count;
	}

	static int maxPathSum = 0;

	public static int maxSumLeafToLeaf(Node node) {
		if (node == null)
			return 0;

		int leftNodeToLeafMax = maxSumLeafToLeaf(node.left);
		int rightNodeToLeafMax = maxSumLeafToLeaf(node.right);

		int ans = node.data + leftNodeToLeafMax + rightNodeToLeafMax;

		if (node.left != null && node.right != null) {
			if (ans > maxPathSum)
				maxPathSum = ans;
			return Math.max(leftNodeToLeafMax, rightNodeToLeafMax) + node.data;
		}

		return (node.left == null ? rightNodeToLeafMax : leftNodeToLeafMax) + node.data;
	}

	// single node not allowed
	public static int maxSumNodeToNode_01(Node node) {
		if (node == null)
			return 0;

		int leftNodeToNodeMax = maxSumNodeToNode_01(node.left);
		int rightNodeToNodeMax = maxSumNodeToNode_01(node.right);

		int ans = Math.max(node.data, Math.max(leftNodeToNodeMax, rightNodeToNodeMax) + node.data);

		if (node.left != null && node.right != null) {
			maxPathSum = Math.max(maxPathSum, leftNodeToNodeMax + rightNodeToNodeMax + node.data);
		}
		maxPathSum = Math.max(maxPathSum, Math.max(leftNodeToNodeMax, rightNodeToNodeMax) + node.data);

		return ans;
	}

	// single node allowed
	public static int maxSumNodeToNode_02(Node node) {
		if (node == null)
			return 0;

		int leftNodeToNodeMax = maxSumNodeToNode_02(node.left);
		int rightNodeToNodeMax = maxSumNodeToNode_02(node.right);

		int ans = Math.max(node.data, Math.max(leftNodeToNodeMax, rightNodeToNodeMax) + node.data);

		maxPathSum = Math.max(maxPathSum, Math.max(leftNodeToNodeMax, rightNodeToNodeMax));
		maxPathSum = Math.max(maxPathSum, Math.max(ans, node.data + leftNodeToNodeMax + rightNodeToNodeMax));

		return ans;
	}

	static Node LCA_NODE = null;

	public static boolean LCA_02(Node node, int data1, int data2) {
		if (node == null) {
			return false;
		}

		boolean selfDone = (node.data == data1) || (node.data == data2);

		boolean left = LCA_02(node.left, data1, data2);
		if (LCA_NODE != null) {
			return true;
		}

		boolean right = LCA_02(node.right, data1, data2);
		if (LCA_NODE != null) {
			return true;
		}

		if (left && right || left && selfDone || right && selfDone) {
			LCA_NODE = node;
			return true;
		}

		return left || right || selfDone;
	}

	static Node prevNode = null, Node1 = null, Node2 = null;

	public static void recoverBST(Node node) {
		if (node == null)
			return;
		recoverBST(node.left);
		if (prevNode != null) {
			if (prevNode.data > node.data && Node1 == null) {
				Node1 = prevNode;
				Node2 = node;
			} else if (prevNode.data > node.data && Node1 != null && Node2 != null) {
				Node2 = node;
			}
		}
		prevNode = node;
		recoverBST(node.right);
	}

	public static Node BSTFromPreOrder(int[] arr, int lb, int ele, int ub) {
		if (ele < lb || ele > ub || idx == arr.length)
			return null;

		Node node = new Node(arr[idx], null, null);
		idx++;

		if (idx < arr.length) {
			node.left = BSTFromPreOrder(arr, lb, arr[idx], node.data);
		}
		if (idx < arr.length) {
			node.right = BSTFromPreOrder(arr, node.data, arr[idx], ub);
		}
		return node;
	}

	public static int HeightOfBSTFromPreOrder(int[] arr, int lb, int ele, int ub) {
		if (ele < lb || ele > ub || idx == arr.length)
			return 0;

		int element = arr[idx];
		idx++;
		int lh = -1, rh = -1;
		if (idx < arr.length)
			lh = HeightOfBSTFromPreOrder(arr, lb, arr[idx], element);
		if (idx < arr.length)
			rh = HeightOfBSTFromPreOrder(arr, element, arr[idx], ub);
		return Math.max(lh, rh) + 1;
	}

	static int leftLevel = -1;

	public static void leftView(Node node, int level) {
		if (node == null)
			return;

		if (leftLevel < level) {
			System.out.print(node.data + " ");
			leftLevel = level;
		}
		leftView(node.left, level + 1);
		leftView(node.right, level + 1);
	}

	static int rightLevel = -1;

	public static void rightView(Node node, int level) {
		if (node == null)
			return;

		if (rightLevel < level) {
			System.out.print(node.data + " ");
			rightLevel = level;
		}
		rightView(node.right, level + 1);
		rightView(node.left, level + 1);
	}

	public static void leftRightView(Node node, int level) {

	}

	static LinkedList<int[]>[] arrayList = new LinkedList[7];

	static int[] verticalSumArray = new int[5];

	public static void verticalOrderSum(Node node, int verticalLevel) {
		if (node == null) {
			return;
		}

		verticalSumArray[verticalLevel] += node.data;
		verticalOrderSum(node.left, verticalLevel - 1);
		verticalOrderSum(node.right, verticalLevel + 1);
	}

	static int[] diagonalSumArray = new int[3];

	public static void diagonalOrderSum(Node node, int diagonalLevel) {
		if (node == null) {
			return;
		}

		diagonalSumArray[diagonalLevel] += node.data;
		diagonalOrderSum(node.left, diagonalLevel - 1);
		diagonalOrderSum(node.right, diagonalLevel);
	}

	public static void verticalOrder(Node node, int verticalLevel, int horizontalLevel) {
		if (node == null) {
			return;
		}

		int[] queueNode = new int[2];
		queueNode[0] = node.data;
		queueNode[1] = horizontalLevel;

		arrayList[verticalLevel].addLast(queueNode);
		verticalOrder(node.left, verticalLevel - 1, horizontalLevel + 1);
		verticalOrder(node.right, verticalLevel + 1, horizontalLevel + 1);
	}

	// public static void displayVerticalOrder() {
	// // sorting
	// for (LinkedList<int[]> linkedList : arrayList) {
	// }

	// // display
	// for (LinkedList<int[]> linkedList : arrayList) {
	// for (int[] is : linkedList) {
	// System.out.print(is[0] + " ");
	// }
	// System.out.println("");
	// }
	// }

	public static Node createBstFromSortedArray(int[] arr, int fi, int li) {
		if (fi > li) {
			return null;
		}
		if (fi == li) {
			Node node = new Node(arr[fi], null, null);
			return node;
		}
		int mid = (fi + li) / 2;

		Node node = new Node(arr[mid], null, null);
		node.left = createBstFromSortedArray(arr, fi, mid - 1);
		node.right = createBstFromSortedArray(arr, mid + 1, li);
		return node;
	}

	public static Node insertInBST(Node root, int data) {
		if (root == null) {
			Node node = new Node(data, null, null);
			return node;
		}

		if (data == root.data) {
			return root;
		} else if (data < root.data) {
			root.left = insertInBST(root.left, data);
		} else
			root.right = insertInBST(root.right, data);

		return root;
	}

	public static Node InorderPredeccessor(Node root) {
		Node node = root;
		while (node != null && node.right != null) {
			node = node.right;
		}
		return node;
	}

	public static Node removeFromBST(Node root, int data) {
		if (root == null) {
			return null;
		}

		if (data < root.data) {
			root.left = removeFromBST(root.left, data);
		} else if (data > root.data) {
			root.right = removeFromBST(root.right, data);
		} else {
			if (root.left == null && root.right == null) {
				return null;
			} else if (root.left == null) {
				return root.right;
			} else if (root.right == null) {
				return root.left;
			} else {
				Node node = InorderPredeccessor(root.left);
				root.data = node.data;
				root.left = removeFromBST(root.left, node.data);
			}
		}
		return root;
	}

	public static Node LCA_BST(Node node, int data1, int data2) {// data1 < data2
		if (data1 < node.data && data2 < node.data) {
			return LCA_BST(node.left, data1, data2);
		}
		if (data1 > node.data && data2 > node.data) {
			return LCA_BST(node.right, data1, data2);
		}
		return node; // make sure data1 and data2 are present in bst
	}

	public static void printInRange(Node node, int data1, int data2) {
		if (node == null) {
			return;
		}
		if (data1 < node.data && data2 < node.data) {
			printInRange(node.left, data1, data2);
		} else if (data1 > node.data && data2 > node.data) {
			printInRange(node.right, data1, data2);
		} else {
			printInRange(node.left, data1, data2);
			System.out.print(node.data + " ");
			printInRange(node.right, data1, data2);
		}
	}

	static int maxLen = 1;

	public static void longestConsecutiveSequence(Node node, int potentialValue, int currLen) {
		if (node == null)
			return;
		if (node.data == potentialValue) {
			currLen++;
			maxLen = Math.max(maxLen, currLen);
		} else
			currLen = 1;
		longestConsecutiveSequence(node.left, node.data + 1, currLen);
		longestConsecutiveSequence(node.right, node.data + 1, currLen);
	}

	static HashMap<Integer, Integer> map = new HashMap<>();
	static int maxFrequency = 0;

	public static int[] mostFrequentSumAnswer(Node node) {
		if (node == null) {

		}
		mostFrequentSum(node);
		int size = 0;
		for (Integer key : map.keySet()) {
			if (map.get(key) == maxFrequency) {
				size++;
			}
		}
		int[] ans = new int[size];
		int i = 0;
		for (Integer key : map.keySet()) {
			if (map.get(key) == maxFrequency) {
				ans[i++] = key;
			}
		}
		return ans;
	}

	public static int mostFrequentSum(Node node) {
		if (node == null) {
			return 0;
		}
		int sum = mostFrequentSum(node.left) + mostFrequentSum(node.right) + node.data;
		map.put(sum, map.getOrDefault(sum, 0) + 1);
		maxFrequency = Math.max(maxFrequency, map.get(sum));
		return sum;
	}

	static int camera = 0;

	public static int minCameraCover(Node node) {
		if (node.left == null && node.right == null) {
			return -1;
		}
		int left = minCameraCover(node.left);
		int right = minCameraCover(node.right);
		if (left == -1 || right == -1) {
			camera++;
			return 1;
		}
		if (left == 1 || right == 1) {
			return 0;
		} else
			return -1;
	}

	public static Node getNextRight(Node root, Node currNode) {
		Node temp = root;
		while (temp.right != null && temp.right != currNode) {
			temp = temp.right;
		}
		return temp;
	}

	public static void InorderMorrisTraversal(Node root) {
		Node currNode = root;
		while (currNode != null) {
			Node next = currNode.left;
			if (next != null) {
				Node nextRight = getNextRight(next, currNode);
				if (nextRight.right != currNode) {
					nextRight.right = currNode;
					currNode = next;
				} else {
					nextRight.right = null;
					System.out.print(currNode.data + " ");
					currNode = currNode.right;
				}
			} else {
				System.out.print(currNode.data + " ");
				currNode = currNode.right;
			}
		}
	}

	public static void PreorderMorrisTraversal(Node root) {
		Node currNode = root;
		while (currNode != null) {
			Node next = currNode.left;
			if (next != null) {
				Node nextRight = getNextRight(next, currNode);
				if (nextRight.right != currNode) {
					System.out.print(currNode.data + " ");
					nextRight.right = currNode;
					currNode = next;
				} else {
					nextRight.right = null;
					currNode = currNode.right;
				}
			} else {
				System.out.print(currNode.data + " ");
				currNode = currNode.right;
			}
		}
	}

	public static class NodeForStack {

		Node node;
		boolean selfDone = false;
		boolean leftDone = false;
		boolean rightDone = false;

		NodeForStack(Node node) {
			this.node = node;
			this.selfDone = false;
			this.leftDone = false;
			this.rightDone = false;
		}
	}

	public static void preorderIteratively(NodeForStack root) {
		LinkedList<NodeForStack> stack = new LinkedList<>();
		stack.addFirst(root);
		while (!stack.isEmpty()) {
			NodeForStack temp = stack.getFirst();
			if (temp.selfDone == false) {
				System.out.print(temp.node.data + " ");
				temp.selfDone = true;
			} else if (temp.leftDone == false) {
				temp.leftDone = true;
				if (temp.node.left != null) {
					stack.addFirst(new NodeForStack(temp.node.left));
				}
			} else if (temp.rightDone == false) {
				temp.rightDone = true;
				if (temp.node.right != null) {
					stack.addFirst(new NodeForStack(temp.node.right));
				}
			} else {
				stack.removeFirst();
			}
		}
	}

	public static void inorderIteratively(NodeForStack root) {
		LinkedList<NodeForStack> stack = new LinkedList<>();
		stack.addFirst(root);
		while (!stack.isEmpty()) {
			NodeForStack temp = stack.getFirst();
			if (temp.leftDone == false) {
				temp.leftDone = true;
				if (temp.node.left != null) {
					stack.addFirst(new NodeForStack(temp.node.left));
				}
			} else if (temp.selfDone == false) {
				System.out.print(temp.node.data + " ");
				temp.selfDone = true;
			} else if (temp.rightDone == false) {
				temp.rightDone = true;
				if (temp.node.right != null) {
					stack.addFirst(new NodeForStack(temp.node.right));
				}
			} else {
				stack.removeFirst();
			}
		}
	}

	public static void postorderIteratively(NodeForStack root) {
		LinkedList<NodeForStack> stack = new LinkedList<>();
		stack.addFirst(root);
		while (!stack.isEmpty()) {
			NodeForStack temp = stack.getFirst();
			if (temp.leftDone == false) {
				temp.leftDone = true;
				if (temp.node.left != null) {
					stack.addFirst(new NodeForStack(temp.node.left));
				}
			} else if (temp.rightDone == false) {
				temp.rightDone = true;
				if (temp.node.right != null) {
					stack.addFirst(new NodeForStack(temp.node.right));
				}
			} else if (temp.selfDone == false) {
				System.out.print(temp.node.data + " ");
				temp.selfDone = true;
			} else {
				stack.removeFirst();
			}
		}
	}

}
