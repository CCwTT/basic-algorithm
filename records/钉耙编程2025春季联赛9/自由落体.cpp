//https://acm.hdu.edu.cn/contest/problem?cid=1158&pid=1009
//@@@
//sgt
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Rect{
    ll xl,yl,xr,yr;
    ll area(){
        return (yr-yl)*(xr-xl);
    }
};

class SGT{
public:
    ll n;
    vector<ll> mx;
    vector<bool> rst;
    SGT(ll sz):n(sz-1),mx(sz<<2,0),rst(sz<<2,false){}

    void up(ll p,ll l,ll r){
        mx[p]=max(mx[p<<1],mx[p<<1|1]);
    }

    void rst_update(ll p,ll l,ll r,ll v){
        mx[p]=v;
        rst[p]=true;
    }

    void down(ll p,ll l,ll r){
        ll m=l+r>>1;
        if(rst[p]){
            rst_update(p<<1,l,r,mx[p]);
            rst_update(p<<1|1,m+1,r,mx[p]);
            rst[p]=false;
        }
    }

    void update(ll p,ll l,ll r,ll x,ll y,ll v){
        if(x<=l&&r<=y){
            rst_update(p,l,r,v);
            return;
        }
        ll m=l+r>>1;
        down(p,l,r);
        if(x<=m) update(p<<1,l,m,x,y,v);
        if(y>m) update(p<<1|1,m+1,r,x,y,v);
        up(p,l,r);
    }

    ll query(ll p,ll l,ll r,ll x,ll y){
        if(x<=l&&r<=y){
            return mx[p];
        }
        ll m=l+r>>1;
        ll res=0;
        down(p,l,r);
        if(x<=m) res=max(res,query(p<<1,l,m,x,y));
        if(y>m) res=max(res,query(p<<1|1,m+1,r,x,y));
        return res;
    }
};

void solve(){
    ll n;
    cin>>n;
    vector<Rect> a(n+1);
    for(ll i=1;i<=n;++i){
        cin>>a[i].xl>>a[i].yl>>a[i].xr>>a[i].yr;
    }
    sort(a.begin()+1,a.end(),[](const Rect& u,const Rect& v){
        return u.yl<v.yl;
    });
    ll ans=0;
    SGT sgt(2e5+5);
    for(ll i=1;i<=n;i++){
        auto rect=a[i];
        ll dest_yl=sgt.query(1,1,sgt.n,rect.xl,rect.xr-1);
        ll dest_yr=dest_yl+(rect.yr-rect.yl);
        sgt.update(1,1,sgt.n,rect.xl,rect.xr-1,dest_yr);
        ll dy=rect.yl-dest_yl;
        ans+=dy*rect.area();
    }
    cout<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}