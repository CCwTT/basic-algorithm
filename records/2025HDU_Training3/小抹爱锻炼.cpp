//https://acm.hdu.edu.cn/contest/problem?cid=1174&pid=1002
//@@@
//greedy
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

constexpr ll N=1e6+10;
ll n,m;
ll b[N],c[N];

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++) cin>>b[i];
    for(ll i=1;i<=n;i++) cin>>c[i];
    ll l=0,r=c[n];
    for(ll i=1;i<=n;i++)
        l+=b[i]=max(b[i],b[i-1]);
    for(ll i=n-1;i>=1;i--)
        r+=c[i]=min(c[i],c[i+1]);
    for(ll i=1;i<=n;i++)
        if(b[i]>c[i]){
            cout<<"NO"<<endl;
            return;
        }
    if(l<=m&&m<=r) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
    }
    return 0;
}