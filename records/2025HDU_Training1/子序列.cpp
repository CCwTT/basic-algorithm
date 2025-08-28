//https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1009
//@@@
//fenwick tree
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll MAXN=2e6+5;\
ll a[MAXN];
ll tr[MAXN];
ll n,m;

void add(ll x,ll v){
    while(x<=n){
        tr[x]+=v;
        x+=x&-x;
    }
}

ll sum(ll x){
    ll res=0;
    while(x){
        res+=tr[x];
        x=x&(x-1);
    }
    return res;
}

void solve(){
    cin>>n;
    fill(tr+1,tr+n+1,0);
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        add(a[i],1);
    }
    ll l=1,r=n;
    ll ans=0;
    while(l<=r){
        if(l==r){
            ans=max(ans,1ll);
            break;
        }
        ll x=min(a[l],a[r])-1;
        ans=max(ans,sum(x)+2);
        if(a[l]<a[r]){
            add(a[l],-1);
            l++;
        }else{
            add(a[r],-1);
            r--;
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