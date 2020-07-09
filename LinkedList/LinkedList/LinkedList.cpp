//
//  LinkedList.cpp
//  LinkedList
//
//  Created by Noor Mohd on 05/07/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(NULL) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

ListNode* getMid(ListNode* head) {
    ListNode *slow=head, *fast=head;
    while (fast->next!=NULL && fast->next->next!=NULL) {
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;
}

int getMidInt(ListNode* head) {
    int mid=0;
    ListNode *slow=head, *fast=head;
    while (fast!=NULL && fast->next!=NULL) {
        mid++;
        slow=slow->next;
        fast=fast->next->next;
    }
    return mid;
}

static ListNode *sNode;         // static node
void reverseLLDataRecursive(ListNode *node, int level, int mid) {
    if(node==NULL) return;
    reverseLLDataRecursive(node->next, level+1, mid);
    if (level>mid) {
        ListNode *temp=node;    // swap
        node=sNode;
        sNode=temp;
        
        sNode=sNode->next;      // increment static node
    }
}

// LC 206 - Reverse Linked List
ListNode* reverseList(ListNode *head) {
    ListNode *prev=NULL, *curr=head;
    while (curr!=NULL) {
        ListNode *next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    return prev;
}

// LC 234 - Palindrome Linked List
bool isPalindrome(ListNode* head) {
    if(head==NULL || head->next==NULL) return true;
    ListNode *mid=getMid(head);
    ListNode *rev=reverseList(mid->next);
    mid->next=NULL;
    while(rev!=NULL && head!=NULL) {
        if(rev->val!=head->val) return false;
        rev=rev->next;
        head=head->next;
    }
    return true;
}

// LC 143 - Reorder List
void reorderList(ListNode* head) {
    if(head==NULL || head->next==NULL || head->next->next==NULL) return;
    ListNode *mid=getMid(head);
    ListNode *h2=reverseList(mid->next);
    mid->next=NULL;
    ListNode *h1=head;
    while(h1!=NULL && h2!=NULL) {
        ListNode *n1=h1->next, *n2=h2->next;
        h1->next=h2;
        h2->next=n1;
        h1=n1;
        h2=n2;
    }
}

// LC 61 - Rotate List
ListNode* rotateRight(ListNode* head, int k) {
    if(head==NULL || head->next==NULL) return head;
    int size=0;
    ListNode *node=head, *tail=head;
    while(tail->next!=NULL) {
        size++;
        tail=tail->next;
    }
    k%=size+1;
    tail->next=head;
    size-=k;
    while(size--) node=node->next;
    head=node->next;
    node->next=NULL;
    return head;
}

// LC 141 - Linked List Cycle
bool hasCycle(ListNode *head) {
    if(head==NULL) return false;
    ListNode *slow=head, *fast=head;
    while(fast!=NULL && fast->next!=NULL) {
        slow=slow->next;
        fast=fast->next->next;
        if(slow==fast) return true;
    }
    return false;
}

// LC 142 - Linked List Cycle II
ListNode *detectCycle(ListNode *head) {
    if(head==NULL || head->next==NULL) return NULL;
    ListNode *slow=head, *fast=head;
    while(fast!=NULL && fast->next!=NULL) {
        slow=slow->next;
        fast=fast->next->next;
        if(slow==fast) break;
    }
    if(slow!=fast) return NULL;
    slow=head;
    while(slow!=fast) {
        slow=slow->next;
        fast=fast->next;
    }
    return slow;
}

// LC 160 - Intersection of Two Linked Lists
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode *nodeA=headA, *nodeB=headB;
    while(nodeA!=nodeB) {
        nodeA=nodeA!=NULL?nodeA->next:headB;
        nodeB=nodeB!=NULL?nodeB->next:headA;
    }
    return nodeA;
}

// LC 876 - Middle of the Linked List
ListNode* middleNode(ListNode* head) {
    ListNode *slow=head, *fast=head;
    while (fast!=NULL && fast->next!=NULL) {
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;
}

// LC 21 - Merge Two Sorted Lists
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if(l1==NULL) return l2;
    if(l2==NULL) return l1;
    ListNode* head=new ListNode();
    ListNode *node=head;
    while(l1!=NULL && l2!=NULL) {
        if(l1->val<=l2->val) {
            node->next=l1;
            l1=l1->next;
        } else {
            node->next=l2;
            l2=l2->next;
        }
        node=node->next;
    }
    if(l2==NULL) node->next=l1;
    if(l1==NULL) node->next=l2;
    return head->next;
}

// LC 23 - Merge k Sorted Lists
struct compare {
    bool operator()(const ListNode* a, const ListNode* b) {
        return a->val>b->val;
    }
};

ListNode* mergeKLists1(vector<ListNode*>& lists) {
    // Heap - O(Nlogk)
    priority_queue<ListNode*, vector<ListNode*>, compare> pq;
    for(ListNode* list: lists) {
        if(list!=NULL) pq.push(list);
    }
    ListNode* head=new ListNode(), *node=head;
    while(!pq.empty()) {
        node->next=pq.top();
        pq.pop();
        node=node->next;
        if(node->next!=NULL) pq.push(node->next);
    }
    return head->next;
}

ListNode* mergeKLists2(vector<ListNode*>& lists, int l, int r) {
    if(l==r) return lists[l];
    else if(l+1==r)
        return mergeTwoLists(lists[l], lists[r]);
    int m=(l+r)/2;
    ListNode* l1=mergeKLists2(lists, l, m);
    ListNode* l2=mergeKLists2(lists, m+1, r);
    return mergeTwoLists(l1, l2);
}

ListNode* mergeKLists2(vector<ListNode*>& lists) {
    // Divide and Conquer - O(Nlogk)
    int k=(int) lists.size();
    if(k==0) return NULL;
    if(k==1) return lists[0];
    return mergeKLists2(lists, 0, k-1);
}

// LC 83 - Remove Duplicates from Sorted List
ListNode* deleteDuplicates(ListNode* head) {
    if(head==NULL) return head;
    ListNode *node=head->next, *prev=head;
    while(node!=NULL) {
        if(prev->val==node->val) {
            prev->next=node->next;
            node=prev->next;
            continue;
        }
        node=node->next;
        prev=prev->next;
    }
    return head;
}

// LC 82 - Remove Duplicates from Sorted List II
ListNode* deleteDuplicatesII(ListNode* head) {
    if(head==NULL) return head;
    ListNode *node=head, *prev=NULL;
    while(node!=NULL) {
        if(node->next!=NULL && node->val==node->next->val) {
            int val=node->val;
            while(node!=NULL && node->val==val) node=node->next;
            if(prev!=NULL) prev->next=node;
            else head=node;
            continue;
        }
        prev=node;
        node=node->next;
    }
    return head;
}

// LC 92 - Reverse Linked List II
ListNode* reverseBetween1(ListNode* head, int m, int n) {
    /*
     let the list be 10->20->30->40->50->60->70->NULL
     and m=3 and n=5
     then prev=20, start=30, end=50 and next=60
     I) 0(res)->10(head)->20(prev)->NULL , 30(start)->40->50(end)->NULL , 60(next)->70->NULL
     II) 0(res)->10(head)->20(prev)->NULL , 50(start)->40->30(end)->NULL , 60(next)->70->NULL
     III) 0(res)->10(head)->20->50->40->30->60->70->NULL
     */
    if(head==NULL) return NULL;
    if(m==n) return head;
    int len=n-m+1;
    ListNode *res=new ListNode(0, head), *prev=res, *start, *end, *next;
    // find prev of the list to be reversed
    while(m--!=1) prev=prev->next;
    // start and end of the list to be reversed
    start=end=prev->next;
    prev->next=NULL;
    while(len--!=1) end=end->next;
    // next of the list to be reversed and detach
    next=end->next;
    end->next=NULL;
    // reverse
    start=reverseList(start);
    //find end of reversed list
    end=start;
    while(end->next!=NULL) end=end->next;
    //join two lists
    prev->next=start;
    end->next=next;
    // return ans
    return res->next;
}

ListNode* reverseBetween2(ListNode* head, int m, int n) {
    if(head==NULL) return NULL;
    if(m==n) return head;
    int len=n-m+1;
    ListNode *res=new ListNode(0, head), *beforeStart=res;
    // find beforeStart of the list to be reversed
    while(m--!=1) beforeStart=beforeStart->next;
    // start and end of the list to be reversed and reverse it inplace
    ListNode *start=beforeStart->next, *prev=start, *curr=start->next;
    while(len--!=1) {
        ListNode *next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    // join
    beforeStart->next=prev;
    start->next=curr;
    return res->next;
}

// LC 24 - Swap Nodes in Pairs
ListNode* swapPairs(ListNode* head) {
    if(head==NULL) return head;
    ListNode *res=new ListNode(0, head), *beforeStart=res, *start=head;
    while(start!=NULL && start->next!=NULL) {
        ListNode *curr=start->next, *next=start->next->next;
        curr->next=start;
        start->next=next;
        beforeStart->next=curr;
        beforeStart=start;
        start=start->next;
    }
    return res->next;
}

// LC 25 - Reverse Nodes in k-Group
ListNode* reverseKGroup(ListNode* head, int k) {
    if(head==NULL || k==1) return head;
    ListNode *res=new ListNode(0, head), *beforeStart=res, *start=head, *node=head;
    int size=0;
    while(node!=NULL) {
        size++;
        node=node->next;
    }
    size/=k;    // no of times the loop will run
    while(size--) {
        ListNode *prev=start, *curr=start->next;
        for(int i=1;i<k;i++) {
            ListNode *next=curr->next;
            curr->next=prev;
            prev=curr;
            curr=next;
        }
        beforeStart->next=prev;
        beforeStart=start;
        start->next=curr;
        start=curr;
    }
    return res->next;
}

// LC 86 - Partition List
ListNode* partition(ListNode* head, int x) {
    ListNode *a=new ListNode(), *b=new ListNode();
    ListNode *one=a, *two=b;
    while(head!=NULL) {
        if(head->val<x) {
            one->next=head;
            one=one->next;
        } else {
            two->next=head;
            two=two->next;
        }
        head=head->next;
        one->next=NULL;
        two->next=NULL;
    }
    one->next=b->next;
    return a->next;
}

// LC 2 - Add Two Numbers
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if(l1==NULL) return l2;
    if(l2==NULL) return l1;
    ListNode *res=new ListNode(), *node=res;
    int carry=0;
    while(l1!=NULL || l2!=NULL) {
        int x=l1!=NULL?l1->val:0;
        int y=l2!=NULL?l2->val:0;
        int val=x+y+carry;
        carry=val/10;
        node->next=new ListNode(val%10);
        node=node->next;
        l1=l1!=NULL?l1->next:l1;
        l2=l2!=NULL?l2->next:l2;
    }
    if(carry==1) node->next=new ListNode(1);
    return res->next;
}

// LC 19 - Remove Nth Node From End of List
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode *p1=head, *p2=head;
    while(n--) p2=p2->next;
    if(p2==NULL) return head->next;
    while(p2->next!=NULL) {
        p1=p1->next;
        p2=p2->next;
    }
    p1->next=p1->next->next;
    return head;
}

// LC 203 - Remove Linked List Elements
ListNode* removeElements(ListNode* head, int val) {
    ListNode *res=new ListNode(0, head), *prev=res, *curr=head;
    while(curr!=NULL) {
        if(curr->val==val) prev->next=curr->next;
        else prev=prev->next;
        curr=curr->next;
    }
    return res->next;
}

// LC 138 - Copy List with Random Pointer
Node* copyRandomList(Node* head) {
    if(head==NULL) return NULL;
    Node *node=head, *res=new Node(0);
    // make copy
    while(node!=NULL) {
        Node *next=node->next;
        node->next=new Node(node->val);
        node->next->next=next;
        node=node->next->next;
    }
    node=head;
    // set random pointer
    while(node!=NULL) {
        node->next->random=node->random==NULL?NULL:node->random->next;
        node=node->next->next;
    }
    res->next=head->next;
    node=head;
    Node *copy=head->next;
    // detach
    while(copy->next!=NULL) {
        node->next=copy->next;
        copy->next=copy->next->next;
        node=node->next;
        copy=copy->next;
    }
    node->next=NULL;
    return res->next;
}

// LC 148 - Sort List
ListNode* sortList(ListNode* head) {
    if(head==NULL || head->next==NULL) return head;
    ListNode *slow=head, *fast=head, *next;
    while (fast->next!=NULL && fast->next->next!=NULL) {
        slow=slow->next;
        fast=fast->next->next;
    }
    next=slow->next;
    slow->next=NULL;
    ListNode *l1=sortList(head);
    ListNode *l2=sortList(next);
    return mergeTwoLists(l1, l2);
}

// LC 147 - Insertion Sort List
ListNode* insertionSortList(ListNode* head) {
    if(head==NULL || head->next==NULL) return head;
    ListNode *res=new ListNode(INT_MIN, head);
    ListNode *curr=head->next, *tail=head;
    while(curr!=NULL) {
        if(tail->val>curr->val) {
            ListNode *next=curr->next, *prev=res;
            while(prev->next!=curr && prev->next->val<curr->val)
                prev=prev->next;
            curr->next=prev->next;
            prev->next=curr;
            tail->next=next;
            curr=next;
        } else {
            tail=tail->next;
            curr=curr->next;
        }
    }
    return res->next;
}

// LC 146 - LRU Cache
class DLLNode {
public:
    int key, value;
    DLLNode *prev=NULL, *next=NULL;
    DLLNode() : key(0), value(0) {}
    DLLNode(int key, int value) : key(key), value(value) {}
    DLLNode(int key, int value, DLLNode* prev, DLLNode* next) : key(key), value(value), prev(prev), next(next) {}
};

class LRUCache {
public:
    // front = most recently used, last = least recently used
    int capacity;
    unordered_map<int, DLLNode*> map;
    DLLNode *head, *tail;
    
    void remove(DLLNode *node) {
        map.erase(node->key);
        DLLNode *prev=node->prev, *next=node->next;
        prev->next=next;
        next->prev=prev;
        node->prev=node->next=NULL;
    }
    
    void push_front(DLLNode *node) {
        map[node->key]=node;
        DLLNode *next=head->next;
        node->prev=head;
        node->next=next;
        head->next=node;
        next->prev=node;
    }
    
    LRUCache(int capacity) {
        this->capacity=capacity;
        head=new DLLNode(0, 0, NULL, NULL);
        tail=new DLLNode(0, 0, head, NULL);
        head->next=tail;
    }
    
    int get(int key) {
        if(map.find(key)==map.end()) return -1;
        DLLNode *node=map[key];
        remove(node);
        push_front(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if(map.find(key)!=map.end()) remove(map[key]);
        else if(map.size()==capacity) remove(tail->prev);
        push_front(new DLLNode(key, value));
    }
};

// LC 1019 - Next Greater Node In Linked List
vector<int> nextLargerNodes(ListNode* head) {
    if(head==NULL) return {};
    vector<int> ans;
    stack<pair<int, int>> st;
    int i=0;
    ListNode *node=head;
    for(;node!=NULL;node=node->next, i++) {
        while(!st.empty() && st.top().second<node->val) {
            ans[st.top().first]=node->val;
            st.pop();
        }
        ans.push_back(0);
        st.push({i, node->val});
    }
    return ans;
}

// LC 1290 - Convert Binary Number in a Linked List to Integer
int getDecimalValue(ListNode* head) {
    int num=0;
    for(ListNode *node=head;node!=NULL;node=node->next) {
        num<<=1;
        num=num|(node->val);
    }
    return num;
}

int main() {
    
    return 0;
}
