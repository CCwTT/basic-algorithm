//https://acm.hdu.edu.cn/contest/problem?cid=1173&pid=1002
//@@@
//classification
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

constexpr ll N=-1;

ll lowbit(ll x){
    return x&-x;
}

void solve(){
    ll n,x,y;
    cin>>n>>x>>y;
    if(x==y){
        cout<<0<<endl;
        return;
    }
    ll cntx=__builtin_popcountll(x);
    ll cnty=__builtin_popcountll(y);
    if(cntx==cnty){
        cout<<1<<endl;
        return;
    }
    if(lowbit(x)==lowbit(y)){
        cout<<1<<endl;
        return;
    }
    cout<<2<<endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
       solve(); 
    } 
    return 0;
}
