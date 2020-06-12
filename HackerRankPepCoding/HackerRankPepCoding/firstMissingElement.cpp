//
//  firstMissingElement.cpp
//  HackerRankPepCoding
//
//  Created by Noor Mohd on 08/02/20.
//  Copyright © 2020 Moin Ahmed. All rights reserved.
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int n;
    cin>>n;
    int a[n];
    for (int i=0; i<n; i++) {
        cin>>a[i];
    }
    sort(a, a+n);
    int i=0;
    while (a[i]<=0) {
        i++;
    }
    if (a[i]!=1) {
        cout<<1;
        return 0;
    }
    while (a[i]+1==a[i+1]) {
        i++;
    }
    cout<<a[i]+1;
    return 0;
}

