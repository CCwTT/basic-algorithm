//https://acm.hdu.edu.cn/contest/problem?cid=1177&pid=1004
//@@@
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=2e5+5;
ll n,a[N],dp[N];

struct segment_tree{
    ll mx[N<<2];

    void update(ll p,ll l,ll r,ll x,ll v){
        mx[p]=max(mx[p],v);
        if(l==r) return;
        ll m=l+r>>1;
        if(x<=m) update(p<<1,l,m,x,v);
        else update(p<<1|1,m+1,r,x,v);
    }

    ll query(ll p,ll l,ll r,ll x,ll y){
        if(!(0<=x&&x<=y)) return 0;
        if(x<=l&&r<=y) return mx[p];
        ll m=l+r>>1;
        ll res=0;
        if(x<=m) res=max(res,query(p<<1,l,m,x,y));
        if(y>m) res=max(res,query(p<<1|1,m+1,r,x,y));
        return res;
    }
}seg;

void solve(){
    cin>>n;
    memset(dp,-1,(n+1)*sizeof(ll));
    memset(seg.mx,0,(n<<2)*sizeof(ll));
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    for(ll i=1;i<=n;i++){
        dp[a[i]]=max(dp[a[i]-1]+1,seg.query(1,1,n,1,a[i]-2));
        if(a[i]==1) dp[a[i]]++;
        if(a[i]==n) dp[a[i]]++;
        seg.update(1,1,n,a[i],dp[a[i]]);
    }
    cout<<n+1-*max_element(dp+1,dp+n+1)<<endl;
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