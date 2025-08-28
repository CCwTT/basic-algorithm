//https://www.luogu.com.cn/problem/P2197

#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

//Bash游戏:一堆石子
//Nim游戏：n堆石子

void solve(){
    ll n;
    cin>>n;
    ll XOR=0;
    for(ll i=0;i<n;i++){
        ll x;
        cin>>x;
        XOR^=x;
    }
    cout<<(XOR?"Yes":"No")<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}