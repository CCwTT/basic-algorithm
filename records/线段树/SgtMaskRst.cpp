//https://www.luogu.com.cn/problem/P1558
//@@@
//seg,bit operation
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class segment_tree{
public:
	ll n;
    vector<ll> mask,rstval;
    vector<bool> rst;
    
	segment_tree(ll sz):n(sz-1),mask(sz<<2,2),rst(sz<<2,false),rstval(sz<<2,0) {}

    void up(ll p){
        mask[p]=mask[p<<1]|mask[p<<1|1];
    }

    void rst_update(ll p,ll l,ll r,ll v){
        mask[p]=1ll<<v;
        rst[p]=true;
        rstval[p]=v;
    }

    void down(ll p,ll l,ll r){
        ll m=l+r>>1;
        if(rst[p]){
            rst_update(p<<1,l,m,rstval[p]);
            rst_update(p<<1|1,m+1,r,rstval[p]);
            rst[p]=false;
        }
    }

    void update(ll p,ll l,ll r,ll x,ll y,ll v){
        if(x<=l&&r<=y){
            rst_update(p,l,r,v);
            return;
        }
        down(p,l,r);
        ll m=(l + r)>>1;
        if(x<=m) update(p<<1,l,m,x,y,v);
        if(y>m) update((p<<1)|1,m + 1,r,x,y,v);
        up(p);
    }

    ll query(ll p,ll l,ll r,ll x,ll y){
        if(x<=l&&r<=y){
            return mask[p];
        }
        down(p,l,r);
        ll m=(l + r)>>1;
        ll res=0;
        if(x<=m) res|=query(p<<1,l,m,x,y);
        if(y>m) res|=query((p<<1)|1,m + 1,r,x,y);
        return res;
    }
};

void solve(){
    ll L,T,O;
    cin>>L>>T>>O;
    segment_tree seg(L+1);
    while(O--){
        char op;
        cin>>op;
        ll x,y,v;
        if(op=='C'){
            cin>>x>>y>>v;
            if(x>y) swap(x,y);
            seg.update(1,1,seg.n,x,y,v);
        }else{
            cin>>x>>y;
            if(x>y) swap(x,y);
            ll mask=seg.query(1,1,seg.n,x,y);
            cout<<__builtin_popcountll(mask)<<endl;
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}