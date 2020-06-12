public class AVLTree {

    public static void main(String[] args) {

    }

    public static class Node {

        int data = 0;
        Node left = null;
        Node right = null;
        int height = -1;
        int balance = 0;

        Node() {

        }

        Node(int data, Node left, Node right, int height, int balance) {
            this.data = data;
            this.left = left;
            this.right = right;
            this.height = height;
            this.balance = balance;
        }
    }

    public static void updateHeight(Node node) {
        int lh = -1;
        int rh = -1;

        if (node.left != null) {
            lh = node.left.height;
        }

        if (node.right != null) {
            rh = node.right.height;
        }

        node.height = Math.max(lh, rh) + 1;
    }

    public static void updateBalance(Node node) {
        int lh = -1;
        int rh = -1;

        if (node.left != null) {
            lh = node.left.height;
        }

        if (node.right != null) {
            rh = node.right.height;
        }

        node.balance = lh - rh;
    }

    public static void updateHeightBalance(Node node) {
        updateHeight(node);
        updateBalance(node);
    }

    public static Node LL_Rotation(Node x) {
        Node y = x.left;
        Node yr = y.right;
        y.right = x;
        x.left = yr;

        updateHeightBalance(x);

        updateHeightBalance(y);

        return y;
    }

    public static Node RR_Rotation(Node x) {
        Node y = x.right;
        Node yl = y.left;
        y.left = x;
        x.right = yl;

        updateHeightBalance(x);

        updateHeightBalance(y); 

        return y;
    }

    public static Node Rotate(Node node) {
        if (node.balance == 2) {
            if (node.left.balance == 1) { // LL ROTATION
                return LL_Rotation(node);
            } else { // LR ROTATION
                node.left = RR_Rotation(node.left);
                return LL_Rotation(node);
            }
        } else if (node.balance == -2) {
            if (node.right.balance == -1) { // RR ROTATION
                return RR_Rotation(node);
            } else { // RL ROTATION
                node.right = LL_Rotation(node.right);
                return RR_Rotation(node);
            }
        } else
            return node;
    }

    public static Node insertInAVL(Node root, int data) {
		if (root == null) {
			Node node = new Node(data, null, null);
			return node;
		}

		if (data == root.data) {
			return root;
		} else if (data < root.data) {
			root.left = insertInAVL(root.left, data);
		} else
            root.right = insertInAVL(root.right, data);
        
        updateHeightBalance(root);
        root=Rotate(root);

		return root;
	}

}