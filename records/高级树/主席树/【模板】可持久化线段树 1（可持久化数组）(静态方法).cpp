//https://www.luogu.com.cn/problem/P3919
//@@@
//persistent segment tree
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN=1e6+5;
class persistent_segment_tree{
public:
    ll n,cnt=0;
    vector<ll>& a;
    vector<ll> root,val,lc,rc;
    persistent_segment_tree(ll sz,ll SZ,vector<ll>& a):a(a),n(sz-1),root(sz),val(SZ),lc(SZ),rc(SZ){
        root[0]=build(1,n);
    }

    ll clone(ll p){
        ll q=++cnt;
        val[q]=val[p];
        lc[q]=lc[p];
        rc[q]=rc[p];
        return q;
    }

    ll build(ll l,ll r){
        ll p=++cnt;
        if(l==r){
            val[p]=a[l];
            return p;
        }
        ll m=l+r>>1;
        lc[p]=build(l,m);
        rc[p]=build(m+1,r);
        return p;
    }

    ll update(ll p,ll l,ll r,ll x,ll v){
        ll q=clone(p);
        if(l==r){
            val[q]=v;
            return q;
        }
        ll m=l+r>>1;
        if(x<=m) lc[q]=update(lc[p],l,m,x,v);
        else rc[q]=update(rc[p],m+1,r,x,v);
        return q;
    }

    ll query(ll p,ll l,ll r,ll x){
        if(l==r){
            return val[p];
        }
        ll m=l+r>>1;
        if(x<=m) return query(lc[p],l,m,x);
        else return query(rc[p],m+1,r,x);
    }
};

void solve(){
    ll n,m;
    cin>>n>>m;
    vector<ll> a(n+1);
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    persistent_segment_tree seg(n+1,max((ll)1e6,(n<<2)+(m*(ll)log2(n+1))),a);
    for(ll i=1;i<=m;i++){
        ll vs,op,x,y;
        cin>>vs>>op;
        if(op==1){
            cin>>x>>y;
            seg.root[i]=seg.update(seg.root[vs],1,n,x,y);
        }else{
            cin>>x;
            seg.root[i]=seg.root[vs];
            cout<<seg.query(seg.root[vs],1,n,x)<<'\n';
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