//
//  Stack.cpp
//  StackQueue
//
//  Created by Noor Mohd on 16/03/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//

#include <bits/stdc++.h>
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

//  LC 20 - Valid Parentheses
bool isValidParentheses(string s) {
    if(s.size()==0) return true;
    if(s.size()%2==1) return false;
    stack<char> st;
    for(int i=0;i<s.size();i++) {
        char ch=s[i];
        if(ch=='(' || ch=='[' || ch=='{') st.push(ch);
        else {
            if (st.size()==0) return false;   //  extra closing bracket
            char top=st.top();
            if((top=='('&&ch==')') || (top=='['&&ch==']') || (top=='{'&&ch=='}'))
                st.pop();
            else return false;   //  not a perfect match
        }
    }
    return st.size()==0;    //  extra opening bracket
}

// LC 1021 - Remove Outermost Parentheses
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

string removeOuterParentheses(string S) {
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

string removeOuterParentheses2(string S) {
    string s;
    int diff=0;
    for(int i=0;i<(int) S.size();i++) {
        if(S[i]=='(' && diff++>0) s+=S[i];
        else if(S[i]==')' && diff-->1) s+=S[i];
    }
    return s;
}

// LC 32 - Longest Valid Parentheses
int longestValidParentheses(string s) {
    int len=0;
    stack<int> st;
    st.push(-1);
    for(int i=0;i<(int) s.size(); i++)
        if(st.top()!=-1 && s[i]==')' && s[st.top()]=='(') {
            st.pop();
            len=max(len, i-st.top());
        } else st.push(i);
    return len;
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

// LC 1003 - Check If Word Is Valid After Substitutions
bool isValid(string S) {
    int n=(int) S.size();
    if(n==0) return true;
    if(n<3 || S[0]!='a' || S[n-1]!='c') return false;
    stack<char> st;
    for(char c: S) {
        switch(c) {
            case 'a': {
                st.push(c);
                break;
            }
            case 'b': {
                if(st.empty() || st.top()!='a') return false;
                st.push(c);
                break;
            }
            case 'c': {
                if(st.empty() || st.top()!='b') return false;
                st.pop();
                if(st.empty() || st.top()!='a') return false;
                st.pop();
            }
        }
    }
    return st.size()==0;
}

// LC 496 - Next Greater Element I
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    int n1=(int) nums1.size(), n2=(int) nums2.size();
    unordered_map<int, int> map;
    stack<int> st;
    for(int i=0;i<n2;i++) {
        while(st.size()!=0 && nums2[st.top()]<nums2[i]) {
            int top=nums2[st.top()];
            st.pop();
            map[top]=nums2[i];
        }
        st.push(i);
    }
    vector<int> ngor(n1, -1);
    for(int i=0;i<n1;i++)
        if(map.find(nums1[i])!=map.end())
            ngor[i]=map[nums1[i]];
    return ngor;
}

// LC 503 - Next Greater Element II
vector<int> nextGreaterElements(vector<int>& nums) {
    int n=(int) nums.size();
    vector<int>nge(n,-1);
    stack<int> st;
    st.push(-1);
    for(int i=0;i<n;i++) {
        while(st.top()!=-1 && nums[st.top()]<nums[i]) {
            int idx=st.top();
            st.pop();
            nge[idx]=nums[i];
        }
        st.push(i);
    }
    for(int i=0;i<n;i++) {
        while(nums[st.top()]<nums[i]) {
            int idx=st.top();
            st.pop();
            nge[idx]=nums[i];
        }
    }
    return nge;
}

// LC 739 - Daily Temperatures
vector<int> dailyTemperatures(vector<int>& T) {
    int n=(int) T.size();
    vector<int> ans(n, 0);
    stack<int> st;
    for(int i=0;i<n;i++) {
        while(st.size()!=0 && T[st.top()]<T[i]) {
            int idx=st.top();
            st.pop();
            ans[idx]=i-idx;
        }
        st.push(i);
    }
    return ans;
}

// LC 1249 - Minimum Remove to Make Valid Parentheses
string minRemoveToMakeValid(string s) {
    stack<int> st;
    for(int i=0;i<(int) s.size(); i++)
        if(s[i]=='(') st.push(i);
        else if(s[i]==')' && !st.empty()) st.pop();
        else if(s[i]==')') s[i]='*';    // starting ))) open brackets
    while(!st.empty()) {
        s[st.top()]='*';
        st.pop();
    }
    string ans="";
    for(int i=0;i<(int) s.size();i++)
        if(s[i]!='*') ans+=s[i];
    return ans;
}

// LC 636 - Exclusive Time of Functions
void convert(string& str, int& id, int& time, int& operation){
    int i=0;
    while(str[i]!=':') id=id*10+(str[i++]-'0');
    if(str[++i]=='e') operation=1;
    while(str[i]!=':') i++;
    string s(str.begin()+i+1, str.end());
    time=stoi(s);
    if(operation==1) time++;
}

vector<int> exclusiveTime(int n, vector<string>& logs) {
    int prev = 0;
    string s, type;
    stack<int> st;
    vector<int> time(n, 0);
    for(string log: logs) {
        int id=0, timestamp=0, operation=0;
        convert(log, id, timestamp, operation);
        if(!st.empty()) time[st.top()]+=timestamp-prev;
        prev=timestamp;
        if(operation==0) st.push(id);
        else st.pop();
    }
    return time;
}

// LC 856 - Score of Parentheses
int scoreOfParentheses(string S) {
    stack<int> st;
    st.push(0);
    for(char c: S) {
        if(c=='(') st.push(0);
        else {
            int a=st.top(); st.pop();
            int b=st.top(); st.pop();
            int score_a=max(2*a, 1), score_aplusb=score_a+b;
            st.push(score_aplusb);
        }
    }
    return st.top();
}

int main() {
    vector<int> arr={1,-2,3,2,4,2,3,6,7,8};
    nextGreaterOnRight(arr);
    return 0;
}
