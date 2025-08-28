//https://www.luogu.com.cn/problem/P7424
//@@@
//persistent segment tree
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef int ll;

const ll MAXN=2e5+5;
const ll MAXT=MAXN*30;

struct node{
    ll sz;
    ll lc;
    ll rc;
};
node tr[MAXT];
ll root[MAXN];
ll cnt=0;

ll n,m;
struct board_node{
    ll l,r,s;
};
board_node board[MAXN];
vector<ll> buc[MAXN];
ll ans[MAXN];

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
        return l;
    }
    ll m=l+r>>1;
    ll lsize=tr[tr[q].lc].sz-tr[tr[p].lc].sz;
    if(lsize>=k) return query(tr[p].lc,tr[q].lc,l,m,k);
    else return query(tr[p].rc,tr[q].rc,m+1,r,k-lsize);
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        cin>>board[i].l>>board[i].r>>board[i].s;
    }
    for(ll i=1;i<=m;i++){
        ll x;
        cin>>x;
        buc[x].push_back(i);
    }
    build(root[0],1,m);
    for(ll i=1;i<MAXN;i++){
        if(buc[i].empty()) root[i]=root[i-1];
        for(ll j=0;j<buc[i].size();j++){
            if(j==0){
                update(root[i],1,m,root[i-1],buc[i][j]);
            }else{
                update(root[i],1,m,root[i],buc[i][j]);
            }
        }
    }
    for(ll i=1;i<=n;i++){
        auto [l,r,s]=board[i];
        if(tr[root[r]].sz-tr[root[l-1]].sz<s) continue;
        ans[query(root[l-1],root[r],1,m,s)]++;
    }
    for(ll i=1;i<=m;i++){
        cout<<ans[i]<<endl;
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
