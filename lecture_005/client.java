public class client {
    public static void main(String[] args) throws Exception {
        simpleQueue();
    }

    public static void simpleQueue() throws Exception {
        dynamicQueue queue = new dynamicQueue();
        queue.push(1);
        queue.push(2);
        queue.push(3);
        queue.push(4);
        queue.pop();
        queue.pop();
        queue.display();
        System.out.println(queue);
    }

    void nextGreaterOnRight() {
        
    }
}