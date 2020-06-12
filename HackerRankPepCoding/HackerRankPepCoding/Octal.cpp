#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int octalToDecimal(int x) {
    int ans=0;
    int i=0;
    while (x>0) {
        int y=x%10;
        x/=10;
        ans+=y*pow(8, i++);
    }
    return ans;
}

int decimalToOctal(int x) {
    int ans=0;
    int i=0;
    while (x>0) {
        int y=x%8;
        x/=8;
        ans+=y*pow(10, i++);
    }
    return ans;
}

int main() {
    int a,b;
    cin>>a>>b;
    int m=octalToDecimal(a);
    int n=octalToDecimal(b);
    cout<<decimalToOctal(m-n);
    return 0;
}
