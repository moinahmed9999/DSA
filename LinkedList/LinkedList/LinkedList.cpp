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
    ListNode(int x) : val(x), next(NULL) {}
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

int main() {
    
    return 0;
}
