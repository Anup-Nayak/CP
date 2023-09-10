#include<iostream>
#include<cmath>
using namespace std;

unsigned long long power(int x, int n){
    unsigned long long ans = 1;
    while (n > 0) {
        if (n%2 == 1) 
        {
            ans = ans * x;
        }
        x *=x;
        n/=2; 
    }
    return ans;
}
int main(){

    int a= pow(11,5);
    int b= -347643%4597;
    
    // int a=2;
    // int b=4;
    // int c=power(11,22);
    cout<<a;
};
