public class dynamicQueue extends Queue{
    public dynamicQueue() {
        resize(10);
    }

    public dynamicQueue(int size) {
        resize(size);
    }

    @Override
    public void push(int val) throws Exception {
        if (this.size == this.queue.length) {
            int[] temp= new int[this.size];
            for(int i=0;i<temp.length;i++) {
                temp[i]=front_();
                pop_();
            }
            resize(2*temp.length);
            for(int i=0;i<temp.length;i++) {
                push_(temp[i]);
            }
        }
        super.push(val);
    }
}