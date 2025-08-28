//https://www.luogu.com.cn/problem/P3567
//@@@
//persistent segment tree
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef int ll;

ll n,m;
const ll MAXN=5e5+5;
const ll MAXT=MAXN*30;
ll a[MAXN];
struct node{
    ll sz;
    ll lc;
    ll rc;
};
ll root[MAXN];
node tr[MAXT];
ll cnt=0;

void up(ll p){
    tr[p].sz=tr[tr[p].lc].sz+tr[tr[p].rc].sz;
}

void build(ll& p,ll l,ll r){
    p=++cnt;
    if(l==r){
        tr[p].sz=0;
        return;
    }
    ll m=l+r>>1;
    build(tr[p].lc,l,m);
    build(tr[p].rc,m+1,r);
    up(p);
}

void update(ll& p,ll l,ll r,ll pre,ll x,ll v=1){
    p=++cnt,tr[p]=tr[pre];
    if(l==r){
        tr[p].sz++;
        return;
    }
    ll m=l+r>>1;
    if(x<=m) update(tr[p].lc,l,m,tr[pre].lc,x,v);
    else update(tr[p].rc,m+1,r,tr[pre].rc,x,v);
    up(p);
}

ll query(ll p,ll q,ll l,ll r,ll k){
    if(l==r){
        if(tr[q].sz-tr[p].sz>=k){
            return l;
        }else{
            return 0;
        }
    }
    ll m=l+r>>1;
    if(tr[tr[q].lc].sz-tr[tr[p].lc].sz>=k) return query(tr[p].lc,tr[q].lc,l,m,k);
    else if(tr[tr[q].rc].sz-tr[tr[p].rc].sz>=k) return query(tr[p].rc,tr[q].rc,m+1,r,k);
    return 0;
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    build(root[0],1,n);
    for(ll i=1;i<=n;i++){
        update(root[i],1,n,root[i-1],a[i]);
    }
    while(m--){
        ll l,r;
        cin>>l>>r;
        ll len=r-l+1;
        ll k=(len&1)?(len+1)/2:(len+2)/2;
        cout<<query(root[l-1],root[r],1,n,k)<<endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}
