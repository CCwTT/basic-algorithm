//https://acm.hdu.edu.cn/contest/problem?cid=1176&pid=1006
//@@@
//game theory
//link:records\2025HDU_Training5\支配游戏.cpp(graphical explanations and table-making programs)
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

ll f(ll x,ll typ){
    if(typ==1){
        if(x==3) return 2;
        if(x%4==0) return 0;
        if(x%4==3) return 3;
        return 1;
    }else{
        if(x%4==3) return 1;
        return 0;
    }
}

void solve(){
    ll n;
    cin>>n;
    ll XOR=0;
    for(ll i=1;i<=n;i++){
        ll x,typ;
        cin>>x>>typ;
        XOR^=f(x,typ);
    }
    cout<<(XOR?"Yes":"No")<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}