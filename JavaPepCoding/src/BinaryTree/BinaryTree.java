package BinaryTree;

public class BinaryTree {

	public static void main(String[] args) {
		int[] arr= {10,20,30,-1,-1,40,-1,-1,50,60,80,
				-1,-1,-1,70,90,-1,100,-1,-1,-1};
		Node rootNode=creatNode(arr);
		display(rootNode);
	}
	
	public static int idx=0;
	
	public static Node creatNode(int[] arr) {
		if(idx==arr.length || arr[idx]==-1) {
			idx++;
			return null;
		}
		Node node=new Node(arr[idx],null,null);
		idx++;
		node.left=creatNode(arr);
		node.right=creatNode(arr);
		return node;
	}
	
	public static void display(Node node) {
		if(node==null)
			return;
		String string = "";
		string+=node.left==null?" . ":node.left.data;
		string+=" -> " + node.data + " <- ";
		string+=node.right==null?" . ":node.right.data;
		System.out.println(string);
		display(node.left);
		display(node.right);
	}

}
