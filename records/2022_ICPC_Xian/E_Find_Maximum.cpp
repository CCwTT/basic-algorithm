#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

ll f(ll x){
    if(x==0) return 1;
    if(x%3==0) return f(x/3)+1;
    return f(x-1)+1;
}

ll g(ll l,ll r){
    if(l==r) return f(l);
    ll l1=(l+2)/3*3;
    ll r1=r/3*3;
    ll res=0;
    if(l1>=r1){
        for(ll i=l;i<=r;i++)
            res=max(res,f(i));
        return res;
    }
    for(ll i=l;i<l1;i++)
        res=max(res,f(i));
    for(ll i=r1;i<=r;i++)
        res=max(res,f(i));
    res=max(res,g(l1/3,r1/3-1)+3);
    return res;
}

void solve(){
    ll l,r;
    cin>>l>>r;
    cout<<g(l,r)<<endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}