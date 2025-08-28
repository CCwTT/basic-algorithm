//https://www.luogu.com.cn/problem/P3372
//@@@
//segment tree,permanent lazy tagging
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class segment_tree{
public:
    ll n;
    vector<ll>& a;
    vector<ll> sum,add_tag;
    segment_tree(ll sz,vector<ll>& a):n(sz-1),sum(n<<2),add_tag(n<<2),a(a){
        build(1,1,n);
    }

    void up(ll p){
        sum[p]=sum[p<<1]+sum[p<<1|1];
    }

    void build(ll p,ll l,ll r){
        add_tag[p]=0;
        if(l==r){
            sum[p]=a[l];
            return;
        }
        ll m=l+r>>1;
        build(p<<1,l,m);
        build(p<<1|1,m+1,r);
        up(p);
    }

    void update(ll p,ll l,ll r,ll x,ll y,ll v){
        sum[p]+=v*(min(r,y)-max(l,x)+1);
        if(x<=l&&r<=y){
            add_tag[p]+=v;
            return;
        }
        ll m=l+r>>1;
        if(x<=m) update(p<<1,l,m,x,y,v);
        if(y>m) update(p<<1|1,m+1,r,x,y,v);
    }

    ll query(ll p,ll l,ll r,ll x,ll y,ll acc){
        if(x<=l&&r<=y){
            return sum[p]+acc*(r-l+1);
        }
        ll m=l+r>>1;
        ll res=0;
        if(x<=m) res+=query(p<<1,l,m,x,y,acc+add_tag[p]);
        if(y>m) res+=query(p<<1|1,m+1,r,x,y,acc+add_tag[p]);
        return res;
    }
};

void solve(){
    ll n,m;
    cin>>n>>m;
    vector<ll> a(n+1);
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    segment_tree seg(n+1,a);
    for(ll i=1;i<=m;i++){
        ll op,x,y,v;
        cin>>op;
        if(op==1){
            cin>>x>>y>>v;
            seg.update(1,1,n,x,y,v);
        }else{
            cin>>x>>y;
            cout<<seg.query(1,1,n,x,y,0)<<endl;
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
