//https://www.luogu.com.cn/problem/P1383
//@@@
//persistent segment tree
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

void Log(vector<ll>& a){
	ll n=a.size();
	for(ll i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

const ll MAXN=1e5+5;
const ll MAXT=MAXN*30;
ll n;
ll root[MAXN];
struct node{
    ll sz;
    char val;
    ll lc;
    ll rc;
    node(ll sz=0):sz(sz),lc(0),rc(0){}
};
node tr[MAXT];
ll cnt=0;

ll vs=0;

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

void update(ll& p,ll l,ll r,ll pre,ll x,char v){
    p=++cnt,tr[p]=tr[pre];
    if(l==r){
        tr[p].sz=1;
        tr[p].val=v;
        return;
    }
    ll m=l+r>>1;
    if(x<=m) update(tr[p].lc,l,m,tr[pre].lc,x,v);
    else update(tr[p].rc,m+1,r,tr[pre].rc,x,v);
    up(p);
    return;
}

char query(ll p,ll l,ll r,ll x){
    if(l==r){
        return tr[p].val;
    }
    ll m=l+r>>1;
    if(x<=tr[tr[p].lc].sz) return query(tr[p].lc,l,m,x);
    else return query(tr[p].rc,m+1,r,x-tr[tr[p].lc].sz);
}

void solve(){
    cin>>n;
    build(root[0],1,n);
    for(ll i=1;i<=n;i++){
        char op;
        cin>>op;
        if(op=='T'){
            char c;
            cin>>c;
            ++vs;
            update(root[vs],1,n,root[vs-1],tr[root[vs-1]].sz+1,c);
        }else if(op=='U'){
            ll x;
            cin>>x;
            ++vs;
            root[vs]=root[vs-x-1];
        }else{
            ll x;
            cin>>x;
            cout<<query(root[vs],1,n,x)<<endl;
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
