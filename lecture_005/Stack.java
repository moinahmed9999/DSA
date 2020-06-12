public class Stack {

    private int[] stack;
    private int size = 0;
    private int capacity = 10;

    public Stack() {
        stack = new int[capacity];
    }

    public Stack(int capacity) {
        this.capacity = capacity;
        stack = new int[capacity];
    }

    public int getSize() {
        return size;
    }
    
    public boolean isEmpty() {
        return size == 0;
    }

    public int top() {
        if (size == 0) {
            System.out.println("Stack is Empty !! ");
            return -1;
        }
        return stack[size - 1];
    }

    public void push(int val) {
        if (size == capacity) {
            System.out.println("Stack Overflow !! ");
        }
        stack[size++] = val;
    }

    public int pop() {
        if (size == 0) {
            System.out.println("Stack Overflow !! ");
            return -1;
        }
        return stack[--size];
    }

    // public class st {

    // }

    // public static void main(String[] args) {

    // }
}