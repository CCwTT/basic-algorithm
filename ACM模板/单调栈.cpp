#include<bits/stdc++.h>
using namespace std;

//https://codeforces.com/contest/2090/problem/E1
/*

rnear: find the smallest j>i s.t. pred1(j)</<=/>/>=pred2(i);
vector<ll> rnear(n+1,n+1);
stack<ll> stk;
for(ll i=n;i>=1;i--){
    while(!stk.empty()&&pred1(stk.top())>=/>/<=/<pred2(i)){
        stk.pop();
    }
    if(!stk.empty()) rnear[i]=stk.top();
    stk.push(i);
}

lnear: find the biggest j<i s.t. pred1(j)</<=/>/>=pred2(i);
vector<ll> lnear(n+1,0);
stack<ll> stk;
for(ll i=1;i<=n;i++){
    while(!stk.empty()&&pred1(stk.top())>=/>/<=/<pred2(i)){
        stk.pop();
    }
    if(!stk.empty()) lnear[i]=stk.top();
    stk.push(i);
}

*/

vector<int> getLeftNearestSmaller(vector<int>& a){
    int n=a.size();
    vector<int> ret(n);
    stack<int> stk;
    for(int i=0;i<n;i++){
        while(!stk.empty()&&a[stk.top()]>=a[i]){
            stk.pop();
        }
        ret[i]=stk.empty()?-1:stk.top();
        stk.push(i);
    }
    return ret;
}

vector<int> getRightNearestSmaller(vector<int>& a){
    int n=a.size();
    vector<int> ret(n);
    stack<int> stk;
    for(int i=n-1;i>=0;i--){
        while(!stk.empty()&&a[stk.top()]>=a[i]){
            stk.pop();
        }
        ret[i]=stk.empty()?-1:stk.top();
        stk.push(i);
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
  	
    return 0;
}
