import java.util.LinkedList;
import java.util.Scanner;

public class Q339 {
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

        // if left is a mirror of right, it is foldable
        boolean isfoldable = IsMirrorImage(root.left,root.right);
        System.out.println(isfoldable);
    }

    public static boolean isLevelMirror(LinkedList<Integer> levelList) {
        if (levelList.size() == 1) {
            return true;
        }
        for (int i = 0, j = levelList.size() - 1; i < j; i++, j--) {
            if (levelList.get(i) != levelList.get(j)) {
                return false;
            }
        }
        return true;
    }

    // one moving on euler and other on reverse euler
    // private static boolean IsMirrorImage(Node node) {
    //     if (node == null) {
    //         return false;
    //     }
    //     LinkedList<Node> queue = new LinkedList<>();
    //     queue.addLast(node);
    //     while (!queue.isEmpty()) {
    //         int size = queue.size();
    //         LinkedList<Integer> levelList = new LinkedList<>();
    //         while (size-- > 0) {
    //             Node x = queue.removeFirst();
    //             if (x.left != null) {
    //                 queue.addLast(x.left);
    //                 levelList.addLast(1);
    //             } else {
    //                 levelList.addLast(-1);
    //             }

    //             if (x.right != null) {
    //                 queue.addLast(x.right);
    //                 levelList.addLast(1);
    //             } else {
    //                 levelList.addLast(-1);
    //             }
    //         }
    //         if (!isLevelMirror(levelList)) {
    //             return false;
    //         }
    //     }
    //     return true;
    // }


    private static boolean IsMirrorImage(Node n1,Node n2) {
        if (n1==null && n2==null) {
            return true;
        }
        if (n1==null || n2==null) {
            return false;
        }
        return IsMirrorImage(n1.left, n2.right) && IsMirrorImage(n1.right, n2.left);
    }
    

}