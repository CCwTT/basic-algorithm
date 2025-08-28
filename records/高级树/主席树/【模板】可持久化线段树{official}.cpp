#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

const ll MAXN=1e6+5;
const ll MAXT=MAXN*30;

struct node{
    ll val;
    ll lc;
    ll rc;
    node(ll val=0):val(val),lc(0),rc(0){}
    node(ll val,ll lc,ll rc):val(val),lc(lc),rc(rc){}
};

ll n,m;
ll a[MAXN];

ll root[MAXN];
node tr[MAXT];
ll cnt=0;

void build(ll& p,ll l,ll r){
    p=++cnt;
    if(l==r){
        tr[p].val=a[l];
        return;
    }
    ll m=l+r>>1;
    build(tr[p].lc,l,m);
    build(tr[p].rc,m+1,r);
    return;
}

void update(ll& p,ll l,ll r,ll pre,ll x,ll v){
    p=++cnt,tr[p]=tr[pre];
    if(l==r){
        tr[p].val=v;
        return;
    }
    ll m=l+r>>1;
    if(x<=m) update(tr[p].lc,l,m,tr[pre].lc,x,v);
    else update(tr[p].rc,m+1,r,tr[pre].rc,x,v);
}

ll query(ll p,ll l,ll r,ll x){
    if(l==r){
        return tr[p].val;
    }
    ll m=l+r>>1;
    if(x<=m) return query(tr[p].lc,l,m,x);
    else return query(tr[p].rc,m+1,r,x);
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    build(root[0],1,n);
    for(ll i=1;i<=m;i++){
        ll vs,op,x,y;
        cin>>vs>>op;
        if(op==1){
            cin>>x>>y;
            update(root[i],1,n,root[vs],x,y);
        }else{
            cin>>x;
            root[i]=root[vs];
            cout<<query(root[i],1,n,x)<<endl;
        }
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
