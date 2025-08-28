//https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1010
//@@@
//persistent segment tree
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll MAXN=2e3+5;
ll a[MAXN];
struct node{
    ll sz;
    ll lc;
    ll rc;
};
node tr[MAXN<<5];
ll cnt=0;
ll root[MAXN];

void build(ll& p,ll l,ll r){
    p=++cnt;
    if(l==r){
        tr[p].sz=0;
        return;
    }
    ll m=(l+r)>>1;
    build(tr[p].lc,l,m);
    build(tr[p].rc,m+1,r);
}

void modify(ll& p,ll l,ll r,ll pre,ll x,ll v=1){
    p=++cnt,tr[p]=tr[pre];
    tr[p].sz++;
    if(l==r){
        return;
    }
    ll m=l+r>>1;
    if(x<=m) modify(tr[p].lc,l,m,tr[pre].lc,x);
    else modify(tr[p].rc,m+1,r,tr[pre].rc,x);
}

ll query(ll p,ll q,ll l,ll r,ll k){
    if(l==r){
        return l;
    }
    ll m=l+r>>1;
    ll lsize=tr[tr[q].lc].sz-tr[tr[p].lc].sz;
    if(k<=lsize) return query(tr[p].lc,tr[q].lc,l,m,k);
    else return query(tr[p].rc,tr[q].rc,m+1,r,k-lsize);
}

void solve(){
    cnt=0;
    ll n;
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    build(root[0],1,n);
    for(ll i=1;i<=n;i++){
        modify(root[i],1,n,root[i-1],a[i]);
    }
    ll ans=0;
    for(ll i=1;i<=n;i++){
        for(ll j=i;j<=n;j++){
            if((j-i)&1) continue;
            ans+=i*j*query(root[i-1],root[j],1,n,(j-i+2)/2);
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