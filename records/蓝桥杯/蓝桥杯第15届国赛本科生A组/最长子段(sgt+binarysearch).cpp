//https://www.lanqiao.cn/problems/20170/learning/
//@@@
//sgt+binary search
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

class SGT{
public:
    ll n;
    vector<ll> mn;

    SGT(ll sz):n(sz-1),mn(n<<2,LLONG_MAX) {}

    void up(ll p,ll l,ll r){
      mn[p]=min(mn[p<<1],mn[p<<1|1]);
    }

    void update(ll p,ll l,ll r,ll x,ll v){
        if(l==r){
            mn[p]=v;
            return;
        }
        ll m=l+(r-l)/2;
        if(x<=m) update(p<<1,l,m,x,v);
        else update(p<<1|1,m+1,r,x,v);
        up(p,l,r);
    }
    ll query(ll p,ll l,ll r,ll x,ll y){
      if(x<=l&&r<=y){
        return mn[p];
      }
      ll res=LLONG_MAX;
      ll m=l+r>>1;
      if(x<=m) res=min(res,query(p<<1,l,m,x,y));
      if(y>m) res=min(res,query(p<<1|1,m+1,r,x,y));
      return res;
    }

    ll first_pos_lessthan(ll p,ll l,ll r,ll x,ll y,ll target){
        if(r<x||l>y||mn[p]>target){
            return -1;
        }
        if(l==r){
            return mn[p]<target?l:-1;
        }
        ll m=l+(r-l)/2;
        ll res=-1;
        if(x<=m&&mn[p<<1]<target){   
            res=first_pos_lessthan(p<<1,l,m,x,y,target);
        }
        if(res==-1&&y>m){
            res=first_pos_lessthan(p<<1|1,m+1,r,x,y,target);
        }
        return res;
    }
};

void solve(){
    ll n,a,b,c;
    cin>>n>>a>>b>>c;
    vector<ll> s(n+1);
    for(ll i=1;i<=n;i++){
        cin>>s[i];
    }
    partial_sum(s.begin()+1,s.end(),s.begin()+1);
    SGT sgt(n+1);
    vector<ll> f(n+1);
    for(ll i=1;i<=n;i++){
        f[i]=s[i]-a*b*i;
    }
    for(ll i=1;i<=n;i++){
        ll gi=s[i-1]-a*c*i;
        sgt.update(1,1,sgt.n,i,gi);
    }
    ll ans=0;
    for(ll i=1;i<=n;i++){
        ans=max(ans,i-sgt.first_pos_lessthan(1,1,sgt.n,1,sgt.n,f[i])+1);
    }
    cout<<ans<<endl;
}

signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}