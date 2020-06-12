//
//  Lexico.cpp
//  HackerRankPepCoding
//
//  Created by Noor Mohd on 08/02/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//
#include<iostream>
using namespace std;

// This is a functional problem only.
// Input is handled for you.
// You do not have to change the main function.
// Write your code in the function below.

void lexcico(int start, int end) {
    int x=start;
    for (int i=0; i<=9; i++) {
        x=start*10+i;
        if (x<end) {
            cout<<x<<"\n";
            lexcico(x,end);
        }
        else
            break;
    }
}

int main(int argc, char** argv) {
    int n;
    cin>>n;
    for (int i=1; i<=9; i++) {
        if (i<n) {
            cout<<i<<"\n";
            lexcico(i,n);
        }
        else
            break;
    }
    return 0;
}
