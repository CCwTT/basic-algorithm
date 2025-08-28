//https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1010
//@@@
//prefix sum,bucket
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll MAXN=2e3+5;
ll a[MAXN];
ll b[MAXN];
ll buc[MAXN<<1];
ll bias;

void solve(){
    ll n;
    cin>>n;
    bias=n+1;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    ll ans=0;
    for(ll p=1;p<=n;p++){
        memset(buc,0,sizeof(buc));
        for(ll i=1;i<=n;i++){
            b[i]=a[i];
        }
        for(ll i=1;i<=n;i++){
            if(b[i]<a[p]) b[i]=-1;
            else if(b[i]>a[p]) b[i]=1;
            else b[i]=0;
        }
        partial_sum(b+1,b+n+1,b+1);
        for(ll i=0;i<p;i++){
            buc[bias+b[i]]+=i+1;
        }
        for(ll i=p;i<=n;i++){
            ans+=buc[bias+b[i]]*i*a[p];
        }
    }
    cout<<ans<<endl;
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