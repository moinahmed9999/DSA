//
//  QueueUsingStack.cpp
//  StackQueue
//
//  Created by Noor Mohd on 22/03/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include <iostream>
#include <stack>
using namespace std;

class Queue1 {
    stack<int> stack1;
    stack<int> stack2;
    
    int Front=-1,Rear=-1;
public:
    // TODO
    // Manage Front and Rear
    
    void push(int val) {        //  O(1)
        if (Front==-1) {
            Front=val;
        }
        Rear=val;
        stack1.push(val);
    }
    void pop() {                //  O(n)
        if (stack2.size()!=0) {
            stack2.pop();
        } else if (stack1.size()!=0) {
            while (stack1.size()!=0) {
                stack2.push(stack1.top());
                stack1.pop();
            }
            stack2.pop();
        } else {
            Rear=-1;
            cout<<"Underflow"<<"\n";
        }
        Front=stack2.top();
    }
    int front() {               //  O(n)
        if (stack2.size()!=0) {
            return stack2.top();
        } else if (stack1.size()!=0) {
            while (stack1.size()!=0) {
                stack2.push(stack1.top());
                stack1.pop();
            }
            return stack2.top();
        } else {
            return -1;
        }
    }
};

class Queue2 {
    stack<int> stack1;
    stack<int> stack2;
    
    int Front=-1,Rear=-1;
public:
    
    void push(int val) {        //  O(n)
        Rear=val;
        if (Front==-1) {
            Front=val;
        }
        while (stack1.size()!=0) {
            stack2.push(stack1.top());
            stack1.pop();
        }
        stack2.push(val);
        while (stack2.size()!=0) {
            stack1.push(stack2.top());
            stack2.pop();
        }
    }
    void pop() {                //  O(1)
        if (stack1.size()!=0) {
            stack1.pop();
            if (stack1.size()==0) {
                Front=Rear=-1;
            } else {
                Front=stack1.top();
            }
        } else {
            cout<<"Underflow"<<"\n";
        }
    }
    int front() {               //  O(1)
        return Front;
    }
    int rear() {               //  O(1)
        return Rear;
    }
};

int main() {
    Queue1 q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);
    q1.pop();
    cout<<q1.front()<<"\n";
    q1.pop();
    q1.pop();
    q1.pop();
    return 0;
}
