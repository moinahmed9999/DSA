public class Queue {
    protected int[] queue;
    protected int front = 0;
    protected int end = 0;
    protected int size = 0;

    protected void resize(int size) {
        this.queue = new int[size];
        this.front = 0;
        this.end = 0;
        this.size = 0;
    }

    public Queue() {
        resize(10);
    }

    public Queue(int size) {
        resize(size);
    }

    protected int maxSize() {
        return this.queue.length;
    }

    public int size() {
        return this.size;
    }

    public boolean isEmpty() {
        return this.size == 0;
    }

    public int front_() {
        return this.queue[this.front];
    }

    public int front() throws Exception {
        if (this.size == 0) {
            throw new Exception("Underflow !!");
        }
        return front_();
    }

    protected void push_(int val) {
        this.queue[this.end] = val;
        this.end = (this.end + 1) % this.queue.length;
        this.size++;
    }

    public void push(int val) throws Exception {
        if (this.size == this.queue.length) {
            throw new Exception("Overflow !!");
        }
        push_(val);
    }

    protected void pop_() {
        this.queue[this.front] = -1;
        this.front = (this.front + 1) % this.queue.length;
        this.size--;
        if (this.size == 0) {
            this.front = this.end = 0;
        }

    }

    public void pop() throws Exception {
        if (this.size == 0) {
            throw new Exception("Underflow !!");
        }
        pop_();
    }

    public void display() {
        int fIdx = this.front; // index of front
        for (int i = 0; i < this.size; i++) {
            System.out.print(this.queue[fIdx] + " ");
            fIdx = (fIdx + 1) % this.queue.length;
        }
    }

    public String toString() {
        StringBuilder sb= new StringBuilder();
        sb.append("[");
        int fIdx = this.front; // index of front
        for (int i = 0; i < this.size; i++) {
            sb.append(this.queue[fIdx] + ",");
            fIdx = (fIdx + 1) % this.queue.length;
        }
        sb.deleteCharAt(sb.length()-1);
        sb.append("]");
        return sb.toString(); // string builder to string
    }
}