import java.util.LinkedList;
import java.util.Scanner;

public class Q344 {
    private static class Node {
        int data;
        Node left;
        Node right;
        Node nextRight;

        Node(int data, Node left, Node right, Node nextRight) {
            this.data = data;
            this.left = left;
            this.right = right;
            this.nextRight = nextRight;
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
                nodes[i] = new Node(arr[i], null, null, null);

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

        int data = scn.nextInt();
        // display(root);

        solve(root, data);
    }

    public static Node getNextRight(Node node) {
        Node temp = node.nextRight;
        while (temp != null) {
            if (temp.left != null) {
                return temp.left;
            }
            if (temp.right != null) {
                return temp.right;
            }
            temp = temp.nextRight;
        }
        return null;
    }

    public static boolean setNextRightNode(Node node, int data) {
        if (node == null) {
            return false;
        }
        boolean res = false;
        if (node.data==data) {
            System.out.println(node.nextRight!=null?node.nextRight.data:"Not Found");
            return true;
        }
        if (node.nextRight != null) {
            res = setNextRightNode(node.nextRight, data);
            if (res==true) {
                return true;
            }
        }
        if (node.left != null) {
            if (node.right != null) {
                node.left.nextRight = node.right;
                node.right.nextRight=getNextRight(node);
            } else {
                node.left.nextRight=getNextRight(node);
            }
            res = setNextRightNode(node.left, data);
            if (res==true) {
                return true;
            }
        } else if (node.right!=null) {
            node.right.nextRight=getNextRight(node);
            res = setNextRightNode(node.right, data);
            if (res==true) {
                return true;
            }
        } else {
            res = setNextRightNode(getNextRight(node),data);
            if (res==true) {
                return true;
            }
        }
        return false;
    }

    private static void solve(Node root, int data) {
        root.nextRight=null;
        boolean res=setNextRightNode(root, data);
        if (!res) {
            System.out.println("Not Found");
        }
    }

}