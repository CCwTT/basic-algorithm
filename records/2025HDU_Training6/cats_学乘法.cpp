//https://acm.hdu.edu.cn/contest/problem?cid=1177&pid=1001
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=2e5+5;
ll n,a[N];

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++) cin>>a[i];
    ll cnt0=0,cnt_=0;
    for(ll i=1;i<=n;i++){
        if(a[i]==0) cnt0++;
        else if(a[i]<0) cnt_++;
    }
    ll ans;
    if(cnt0>0||~cnt_&1){
        ans=cnt0;
    }else{
        ll mn=inf;
        for(ll i=1;i<=n;i++){
            mn=min(mn,abs(a[i])+1);
        }
        ans=mn;
    }
    cout<<ans<<endl;
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