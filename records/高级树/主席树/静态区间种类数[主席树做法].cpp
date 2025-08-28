//https://www.luogu.com.cn/problem/P1972
//@@@
//persistent segment tree
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef int ll;

const ll MAXN=1e6+5;
const ll MAXT=MAXN*30;
ll a[MAXN];
ll b[MAXN];
ll root[MAXN];
struct node{
    ll sz;
    ll lc;
    ll rc;
};
node tr[MAXT];
ll cnt=0;

ll n,m;
vector<ll> pos[MAXN];

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
    if(x<=m) update(tr[p].lc,l,m,tr[pre].lc,x);
    else update(tr[p].rc,m+1,r,tr[pre].rc,x);
    up(p);
}

ll query(ll p,ll q,ll l,ll r,ll x){
    if(r<=x){
        return 0;
    }
    if(l>x){
        return tr[q].sz-tr[p].sz;
    }
    ll res=0;
    ll m=l+r>>1;
    if(m<=x) res+=query(tr[p].rc,tr[q].rc,m+1,r,x);
    else res+=query(tr[p].rc,tr[q].rc,m+1,r,x)+query(tr[p].lc,tr[q].lc,l,m,x);
    return res;
}

// ll query(ll p,ll q,ll l,ll r,ll x,ll y){
//     if(x<=l&&r<=y){
//         return tr[q].sz-tr[p].sz;
//     }
//     ll res=0;
//     ll m=l+r>>1;
//     if(x<=m) res+=query(tr[p].lc,tr[q].lc,l,m,x,y);
//     if(y>m) res+=query(tr[p].rc,tr[q].rc,m+1,r,x,y);
//     return res;
// }

void pre_process(){
    for(ll i=1;i<=n;i++){
        auto p=lower_bound(pos[a[i]].begin(),pos[a[i]].end(),i)-pos[a[i]].begin();
        b[i]=(p==pos[a[i]].size()-1)?n+1:pos[a[i]][p+1];
    }
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        pos[a[i]].push_back(i);
    }
    pre_process();
    build(root[0],1,n);
    for(ll i=1;i<=n;i++){
        update(root[i],1,n+1,root[i-1],b[i]);
    }
    cin>>m;
    while(m--){
        ll l,r;
        cin>>l>>r;
        cout<<query(root[l-1],root[r],1,n+1,r)<<endl;
        //cout<<(r-l+1)-query(root[l-1],root[r],1,n+1,r)<<endl;
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
