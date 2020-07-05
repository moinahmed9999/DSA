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

// LC 84 - Largest Rectangle in Histogram
int largestRectangleArea(vector<int>& heights) {
    int n=(int) heights.size(), ans=0;
    stack<int> st;
    st.push(-1);
    for(int i=0;i<n;i++) {
        while(st.top()!=-1 && heights[i]<=heights[st.top()]) {
            int h=heights[st.top()];
            st.pop();
            int w=i-st.top()-1;
            ans=max(ans, h*w);
        }
        st.push(i);
    }
    while(st.top()!=-1) {
        int h=heights[st.top()];
        st.pop();
        int w=n-st.top();
        ans=max(ans, h*w);
    }
    return ans;
}

// LC 85 - Maximal Rectangle
int maximalRectangle(vector<vector<char>>& matrix) {
    int n=(int) matrix.size();
    if(n==0) return 0;
    int m=(int) matrix[0].size(), ans=0;
    vector<int> heights(m, 0);
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++)
            heights[j]=matrix[i][j]=='0'?0:heights[j]+1;
        ans=max(ans, largestRectangleArea(heights));
    }
    return ans;
}

// LC 42 - Trapping Rain Water
int trap(vector<int>& heights) {
    if(heights.size()==0) return 0;
    int n=(int) heights.size();
    stack<int> st;
    st.push(-1);
    int water=0;
    for(int i=0;i<n;i++) {
        while(st.top()!=-1 && heights[st.top()]<=heights[i]) {
            int j=st.top();
            st.pop();
            int lb=st.top();
            lb=lb==-1?j:lb;
            int rb=i;
            int lh=heights[lb];
            int rh=heights[rb];
            int waterHeiht=min(lh,rh)-heights[j];
            int waterWidth=rb-lb-1;
            waterWidth=waterWidth==-1?0:waterWidth;
            water+=waterHeiht*waterWidth;
        }
        st.push(i);
    }
    return water;
}

// LC 735 - Asteroid Collision
vector<int> asteroidCollision(vector<int>& asteroids) {
    int n=(int) asteroids.size();
    if(n==0) return asteroids;
    stack<int> st;
    st.push(-1);
    for(int i=0;i<n;i++) {
        int flag=0;
        while(st.top()!=-1 && asteroids[st.top()]>0 && asteroids[i]<0) {
            int a=asteroids[st.top()];
            int b=asteroids[i];
            if(abs(a)>abs(b)) {
                flag++;
                break;
            } else if(abs(a)<abs(b)) {
                st.pop();
            } else {
                st.pop();
                flag++;
                break;
            }
        }
        if(flag==0) {
            st.push(i);
        }
    }
    vector<int> ans(st.size()-1,0);
    for(int i=(int) st.size()-2;i>=0;i--) {
        ans[i]=asteroids[st.top()];
        st.pop();
    }
    return ans;
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

// LC 1047 - Remove All Adjacent Duplicates In String
string removeDuplicates(string S) {
    stack<int> st;
    for(int i=0;i<(int) S.size();i++) {
        if(st.size()==0 || S[st.top()]!=S[i]) {
            st.push(i);
            continue;
        }
        while(st.size()!=0 && S[st.top()]==S[i])
            st.pop();
    }
    string ans="";
    while(!st.empty()) {
        ans+=S[st.top()];
        st.pop();
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

// LC 1209 - Remove All Adjacent Duplicates in String II
string removeDuplicates(string s, int k) {
    stack<pair<char, int>> st;
    for(char c: s)
        if(st.size()==0 || st.top().first!=c) st.push({c,1});
        else if(st.size()!=0 && st.top().first==c) {
            if(st.top().second==k-1) st.pop();
            else st.top().second++;
        }
    string ans="";
    while(!st.empty()) {
        while(st.top().second--) ans+=st.top().first;
        st.pop();
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

// LC 316 - Remove Duplicate Letters
string removeDuplicateLetters(string s) {
    vector<int> freq(26, 0);
    for(char c: s) freq[c-'a']++;
    stack<char> st;
    vector<bool> visited(26, false);
    for(char c: s) {
        freq[c-'a']--;
        if(visited[c-'a']) continue;
        while(st.size()!=0 && st.top()>c && freq[st.top()-'a']!=0) {
            visited[st.top()-'a']=false;
            st.pop();
        }
        st.push(c);
        visited[c-'a']=true;
    }
    string ans="";
    while(!st.empty()) {
        ans+=st.top();
        st.pop();
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

// LC 394 - Decode String
string decodeString(string s) {
    int n=(int) s.size();
    stack<string> st;
    stack<int> kst;
    for(int i=0;i<n;i++) {
        char c=s[i];
        if(isalpha(c) || c=='[') {
            st.push(string(1, c));
        } else if(isdigit(c)) {
            string digit="";
            while(isdigit(s[i])) digit+=s[i++];
            kst.push(stoi(digit));
            i--;
        } else if(c==']') {
            int k=kst.top(); kst.pop();
            string encoded_string="";
            while(st.top()!="[") {
                encoded_string+=st.top();
                st.pop();
            }
            st.pop();
            string decoded_string="";
            while(k--!=0) decoded_string+=encoded_string;
            st.push(decoded_string);
        }
    }
    string decoded_string="";
    while(!st.empty()) {
        decoded_string+=st.top();
        st.pop();
    }
    reverse(decoded_string.begin(), decoded_string.end());
    return decoded_string;
}

// LC 844 - Backspace String Compare
bool backspaceCompare(string S, string T) {
    stack<char> st;
    for(char c: S)
        if(c!='#') st.push(c);
        else if(!st.empty()) st.pop();
    S="";
    while(!st.empty()) {
        S+=st.top();
        st.pop();
    }
    for(char c: T)
        if(c!='#') st.push(c);
        else if(!st.empty()) st.pop();
    T="";
    while(!st.empty()) {
        T+=st.top();
        st.pop();
    }
    return S==T;
}

// LC 946 - Validate Stack Sequences
bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
    int n=(int) pushed.size(), i=0, j=0;
    stack<int> st;
    for(;i<n;i++) {
        st.push(pushed[i]);
        while(!st.empty() && j<n && popped[j]==st.top()) {
            st.pop();
            j++;
        }
    }
    return st.size()==0;
}

// LC 439 - Ternary Expression Parser
string parseTernary(string expression) {    // check right to left
    int n=(int) expression.size();
    stack<char> st;
    for(int i=n-1;i>=0;i--) {
        char c=expression[i];
        if(c!='?' && c!=':') {
            st.push(c);
        } else if(c=='?') {
            char ans1=st.top(); st.pop();
            char ans2=st.top(); st.pop();
            char TF=expression[--i];
            if(TF=='T') st.push(ans1);
            else st.push(ans2);
        }
    }
    return string(1, st.top());
}

int main() {
    vector<int> arr={1,-2,3,2,4,2,3,6,7,8};
    nextGreaterOnRight(arr);
    return 0;
}
