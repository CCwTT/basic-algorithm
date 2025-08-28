//https://acm.hdu.edu.cn/showproblem.php?pid=5306
//@@@
//diverse + static array 2730~>3000 medium
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

const ll MX=1e6+5;

class SGT{
public:
    ll n;
    vector<ll>& a;
    ll ma[MX],t[MX],se[MX],s[MX];
    bool tag[MX];
    SGT(ll sz,vector<ll>& a):n(sz-1),a(a){
        build(1,1,n);
    }
    void up(ll p,ll l,ll r){
        ma[p]=max(ma[p<<1],ma[p<<1|1]);
        ll m=(l+r)/2;
        if(ma[p<<1]==ma[p<<1|1]){
            ma[p]=ma[p<<1];
            t[p]=t[p<<1]+t[p<<1|1];
            se[p]=max(se[p<<1],se[p<<1|1]);
        }else if(ma[p<<1]>ma[p<<1|1]){
            ma[p]=ma[p<<1];
            t[p]=t[p<<1];
            se[p]=max(se[p<<1],ma[p<<1|1]);
        }else{
            ma[p]=ma[p<<1|1];
            t[p]=t[p<<1|1];
            se[p]=max(ma[p<<1],se[p<<1|1]);
        }
        s[p]=s[p<<1]+s[p<<1|1];
    }
    
    void build(ll p,ll l,ll r){
        if(l==r){
            tag[p]=0;
            s[p]=a[l];
            ma[p]=a[l];
            t[p]=1;
            se[p]=-1;
        }else{
            ll m=(l+r)/2;
            build(p<<1,l,m);
            build(p<<1|1,m+1,r);
            up(p,l,r);
        }
    }
    
    void down(ll p){
        ll v=ma[p];
        tag[p]=0;
        if(ma[p<<1]>v&&se[p<<1]<v){
            tag[p<<1]=1;
            s[p<<1]-=(ma[p<<1]-v)*(ll)t[p<<1];
            ma[p<<1]=v;
        }
        if(ma[p<<1|1]>v&&se[p<<1|1]<v){
            tag[p<<1|1]=1;
            s[p<<1|1]-=(ma[p<<1|1]-v)*(ll)t[p<<1|1];
            ma[p<<1|1]=v;
        }
    }
    
    void update(ll p,ll l,ll r,ll x,ll y,ll v){
        ll m=(l+r)/2;
        if(l==x&&r==y&&v>se[p]){
            if(v>=ma[p]) return;
            else{
                s[p]-=(ma[p]-v)*(ll)t[p];
                ma[p]=v;
                tag[p]=1;
                return;
            }
        }
        if(tag[p]) down(p);
        if(y<=m) update(p<<1,l,m,x,y,v);
        else if(x>m) update(p<<1|1,m+1,r,x,y,v);
        else update(p<<1,l,m,x,m,v),update(p<<1|1,m+1,r,m+1,y,v);
        up(p,l,r);
    }
    
    ll query_max(ll p,ll l,ll r,ll x,ll y){
        ll m=(l+r)/2;
        if(l==x&&r==y) return ma[p];
        if(tag[p]) down(p);
        if(y<=m) return query_max(p<<1,l,m,x,y);
        else if(x>m) return query_max(p<<1|1,m+1,r,x,y);
        else return max(query_max(p<<1,l,m,x,m),query_max(p<<1|1,m+1,r,m+1,y));
    }
    
    ll query_sum(ll p,ll l,ll r,ll x,ll y){
        ll m=(l+r)/2;
        if(l==x&&r==y) return s[p];
        if(tag[p]) down(p);
        if(y<=m) return query_sum(p<<1,l,m,x,y);
        else if(x>m) return query_sum(p<<1|1,m+1,r,x,y);
        else return query_sum(p<<1,l,m,x,m)+query_sum(p<<1|1,m+1,r,m+1,y);
    }
};

void solve(){
    ll n,m;
    cin>>n>>m;
    vector<ll> a(n+1);
    for(ll i=1;i<=n;i++) cin>>a[i];
    SGT sgt(n+1,a);
    ll op,x,y,val;
    while(m--){
        cin>>op>>x>>y;
        if(op==0){
            cin>>val;
            sgt.update(1,1,sgt.n,x,y,val);
        }else if(op==1){
            cout<<sgt.query_max(1,1,sgt.n,x,y)<<endl;
        }else{
            cout<<sgt.query_sum(1,1,sgt.n,x,y)<<endl;
        }
    }
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