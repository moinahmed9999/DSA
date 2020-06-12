//
//  Stack.cpp
//  StackQueue
//
//  Created by Noor Mohd on 16/03/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void nextGreaterOnRight(vector<int>& arr) {
    int n=(int)arr.size();
    vector<int> ngor(n,-1);
    stack<int> st;
    for (int i=0; i<n; i++) {
        while (st.size()!=0 && arr[st.top()]<arr[i]) {
            int idx=st.top();
            st.pop();
            ngor[idx]=arr[i];
        }
        st.push(i);
    }
    for (int ele : ngor) {
        cout<<ele<<" ";
    }
    cout<<"\n";
}

void nextGreaterOnLeft(vector<int>& arr) {
    int n=(int)arr.size();
    vector<int> ngol(n,-1);
    stack<int> st;
    for (int i=n-1; i>=0; i--) {
        while (st.size()!=0 && arr[st.top()]<arr[i]) {
            int idx=st.top();
            st.pop();
            ngol[idx]=arr[i];
        }
        st.push(i);
    }
    for (int ele : ngol) {
        cout<<ele<<" ";
    }
    cout<<"\n";
}

void nextSmallerOnRight(vector<int>& arr) {
    int n=(int)arr.size();
    vector<int> nsor(n,-1);
    stack<int> st;
    for (int i=0; i<n; i++) {
        while (st.size()!=0 && arr[st.top()]>arr[i]) {
            int idx=st.top();
            st.pop();
            nsor[idx]=arr[i];
        }
        st.push(i);
    }
    for (int ele : nsor) {
        cout<<ele<<" ";
    }
    cout<<"\n";
}

void nextSmallerOnLeft(vector<int>& arr) {
    int n=(int)arr.size();
    vector<int> nsol(n,-1);
    stack<int> st;
    for (int i=n-1; i>=0; i--) {
        while (st.size()!=0 && arr[st.top()]>arr[i]) {
            int idx=st.top();
            st.pop();
            nsol[idx]=arr[i];
        }
        st.push(i);
    }
    for (int ele : nsol) {
        cout<<ele<<" ";
    }
    cout<<"\n";
}

bool isValidParentheses(string s) {     //  LC 20
    if(s.size()==0) {
        return true;
    }
    if(s.size()%2==1) {
        return false;
    }
    stack<char> st;
    for(int i=0;i<s.size();i++) {
        char ch=s[i];
        if(ch=='(' || ch=='[' || ch=='{') {
            st.push(ch);
        } else {
            if (st.size()==0) {
                return false;   //  extra closing bracket
            }
            char top=st.top();
            if((top=='('&&ch==')') || (top=='['&&ch==']') || (top=='{'&&ch=='}')) {
                st.pop();
            } else {
                return false;   //  not a perfect match
            }
        }
    }
    return st.size()==0;    //  extra opening bracket
}

vector<string> primitiveDecomposition(string S) {
    vector<string> ds;  //  dedomposed string
    stack<char> st;
    int i=0;
    while(i<S.size()) {
        string ps={""};
        st.push(S[i]);
        ps+=S[i];
        i++;
        while(st.size()!=0) {
            char ch=S[i];
            if(ch=='(') {
                st.push(ch);
            } else {
                st.pop();
            }
            ps+=ch;
            i++;
        }
        ds.push_back(ps);
    }
    return ds;
}

string removeOuterParentheses(string S) {   //  LC 1021
    string s;
    vector<string> ds=primitiveDecomposition(S);
    //  remove outer parantheses
    for(string x:ds) {
        if(x.size()>2) {
            for(int i=1;i<x.size()-1;i++) {
                s+=x[i];
            }
        }
    }
    return s;
}

int longestValidParentheses(string s) {     //  LC 32
    stack<int> st;
    int maxLength=0;
    st.push(-1);
    for (int i=0; i<s.size(); i++) {
        if (st.top()!=-1 && s[i]==')' && s[st.top()]=='(') {
            st.pop();
            int len=i-st.top();
            if (maxLength<len) {
                maxLength=len;
            }
        } else st.push(i);
    }
    return maxLength;
}

vector<int> nextSmallerOnRightLRA(vector<int>& arr) {
    int n=(int)arr.size();
    vector<int> nsor(n,n);
    stack<int> st;
    for (int i=0; i<n; i++) {
        while (st.size()!=0 && arr[st.top()]>arr[i]) {
            int idx=st.top();
            st.pop();
            nsor[idx]=i;
        }
        st.push(i);
    }
    return nsor;
}

vector<int> nextSmallerOnLeftLRA(vector<int>& arr) {
    int n=(int)arr.size();
    vector<int> nsol(n,-1);
    stack<int> st;
    for (int i=n-1; i>=0; i--) {
        while (st.size()!=0 && arr[st.top()]>arr[i]) {
            int idx=st.top();
            st.pop();
            nsol[idx]=i;
        }
        st.push(i);
    }
    return nsol;
}

int largestRectangleArea_01(vector<int>& heights) {    //  LC 84
    if(heights.size()==0) return 0;
    if(heights.size()==1) return heights[0];
    int n=(int)heights.size();
    vector<int> nsor=nextSmallerOnRightLRA(heights);
    vector<int> nsol=nextSmallerOnLeftLRA(heights);
    int maxArea=0;
    for(int i=0;i<n;i++) {
        int h=heights[i];
        int w=nsor[i]-nsol[i]-1;
        int area=h*w;
        maxArea=max(maxArea,area);
    }
    return maxArea;
}

int largestRectangleArea_02(vector<int>& heights) {
    if(heights.size()==0) return 0;
    if(heights.size()==1) return heights[0];
    int n=(int)heights.size();
    stack<int> st;
    st.push(-1);
    int maxArea=0;
    for(int i=0;i<n;i++) {
        while(st.top()!=-1 && heights[st.top()]>heights[i]) {
            int h=heights[st.top()];
            st.pop();
            int w=i-st.top()-1;
            int area=h*w;
            maxArea=max(maxArea,area);
        }
        st.push(i);
    }
    while(st.top()!=-1) {
        int h=heights[st.top()];
        st.pop();
        int w=n-st.top()-1;
        int area=h*w;
        maxArea=max(maxArea,area);
    }
    return maxArea;
}

int main() {
    vector<int> arr={1,-2,3,2,4,2,3,6,7,8};
    nextGreaterOnRight(arr);
    return 0;
}
