//https://acm.hdu.edu.cn/contest/problem?cid=1178&pid=1001
//@@@
//sweeping line(seg)
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll N=1e4+5;

struct segment_tree{
    vector<ll> mx,add;
    ll n;
    segment_tree(ll n){
        this->n=n;
        mx.resize(n<<2);
        add.resize(n<<2);
    }
    void up(ll p){
        mx[p]=max(mx[p<<1],mx[p<<1|1]);
    }

    void put_add(ll p,ll v){
        mx[p]+=v;
        add[p]+=v;
    }
    
    void down(ll p,ll l,ll r){
        if(add[p]){
            put_add(p<<1,add[p]);
            put_add(p<<1|1,add[p]);
            add[p]=0;
        }
    }
    
    void update(ll p,ll l,ll r,ll x,ll y,ll v){
        if(x<=l&&r<=y){
            put_add(p,v);
            return;
        }
        down(p,l,r);
        ll mid=l+r>>1;
        if(x<=mid) update(p<<1,l,mid,x,y,v);
        if(y>mid) update(p<<1|1,mid+1,r,x,y,v);
        up(p);
    }
};

ll n,k,ans;
vector<pair<ll,ll>> vec[N];
ll compute(ll h){
    segment_tree seg(n+1);
    ll w=k/h;
    for(ll i=1;i<=h;i++){
        for(auto p:vec[i]){
            seg.update(1,1,n,max(1ll,p.first-w+1),p.first,p.second);
        }
    }
    ll res=seg.mx[1];
    for(ll i=h+1;i<=n;i++){
        for(auto p:vec[i-h]){
            seg.update(1,1,n,max(1ll,p.first-w+1),p.first,-p.second);
        }
        for(auto p:vec[i]){
            seg.update(1,1,n,max(1ll,p.first-w+1),p.first,p.second);
        }
        res=max(res,seg.mx[1]);
    }
    return res;
}

void solve(){
    ans=0;
    cin>>n>>k;
    for(ll i=1;i<=n;i++){
        ll x,y,v;
        cin>>x>>y>>v;
        vec[x].push_back({y,v});
    }
    for(ll h=1;h<=min(n,k);h++) {
        h=k/(k/h);
        ans=max(ans,compute(h));
    }
    cout<<ans<<endl;

    for(ll i=1;i<=n;i++){
        vec[i].clear();
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}