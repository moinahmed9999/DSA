import java.util.NoSuchElementException;

public class linkedlist {

    public class Node {
        int data = 0;
        Node next = null;

        public Node(int data) {
            this.data = data;
        }

        public String toString() {
            return (this.data + "");
        }
    }

    private Node head = null;
    private Node tail = null;
    private int size = 0;

    // general functions -----------------------------------------------------

    public int size() {
        return this.size;
    }

    public boolean isEmpty() {
        return this.size == 0;
    }

    private Node getNodeAt(int index) {
        if(index<0 || index>=size) {
            System.out.println("Null Pointer Exception !!");
            throw new NullPointerException();
        }
        Node temp = head;
        int i = 0;
        while (temp != null && i != index) {
            temp = temp.next;
            i++;
        }
        return temp;
    }

    public String toString() {
        if(size==0) {
            return "Linked List is Empty";
        }
        StringBuilder sb = new StringBuilder();
        Node node= head;
        
        while(node.next!=null) {
            sb.append(node + " -> ");
            node=node.next;
        }
        sb.append(node);
        return sb.toString();
    }

    // add functions -----------------------------------------------------

    public void addFirstNode(Node node) {
        if (size==0) {
            tail=node;
        }
        node.next = head;
        head = node;
        size++;
    }

    public void addFirst(int data) {
        Node node = new Node(data);
        addFirstNode(node);
    }

    public void addLastNode(Node node) {
        if(size==0) {
            head=tail=node;
            size++;
            return;
        }
        tail.next = node;
        tail = node;
        size++;
    }

    public void addLast(int data) {
        Node node = new Node(data);
        addLastNode(node);
    }

    public void addAtNode(int index, Node node) {
        Node node1 = getNodeAt(index - 1);
        node.next = node1.next;
        node1.next = node;
        size++;
    }

    public void addAt(int index, int data) {
        if (index==0) {
            addFirst(data);
        } else if (index==size) {
            addLast(data);
        } else {
            Node node = new Node(data);
            addAtNode(index, node);
        }
    }

    // remove functions -----------------------------------------------------

    public Node removeFirstNode() {
        if (size==0) {
            System.out.println("Underflow !!");
            throw new NoSuchElementException();
        }
        Node node=head;
        head=head.next;
        if (size==1) {
            tail=null;
        }
        size--;
        return node;
    }

    public int removeFirst() {
        return removeFirstNode().data;
    }

    public Node removeLastNode() {
        if (size==0) {
            System.out.println("Underflow !!");
            throw new NoSuchElementException();
        } else if (size==1) {
            return removeFirstNode();
        }
        Node node=tail;
        tail=getNodeAt(size-2);
        tail.next=null;
        size--;
        return node;
    }

    public int removeLast() {
        return removeLastNode().data;
    }

    public Node removeAtNode(int index) {
        if (size==0) {
            System.out.println("Underflow !!");
            throw new NoSuchElementException();
        } else if (index==0) {
            return removeFirstNode();
        } else if (index==size-1) {
            return removeLastNode();
        } else {
            Node node1 = getNodeAt(index - 1);
            Node node2 = getNodeAt(index);
            Node node3 = node2.next;
            node1.next=node3;
            node2.next=null;
            size--;
            return node2;
        }
    }

    public int removeAt(int index) {
        return removeAtNode(index).data;
    }

    // get functions -----------------------------------------

    public int getFirst() {
        if(size==0) return -1;
        return head.data;
    }

    public int getLast() {
        if (size==0) return -1;
        return tail.data;
    }

    public int getAt(int index) {
        if (size==0) return -1;
        return getNodeAt(index).data;
    }

    // --------------------------------------------------------
 
    public static void main(String[] args) throws Exception {
        linkedlist ll = new linkedlist();
        ll.addFirst(10);
        ll.removeLast();
        System.out.println(ll);
    }

}