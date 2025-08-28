//https://atcoder.jp/contests/abc408/tasks/abc408_f
//@@@
//sgt
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

class SGT{
public: 
    ll n;
    vector<ll> mx;

    SGT(ll sz):n(sz-1),mx(n<<2,LLONG_MIN/2) {}

    void up(ll p,ll l,ll r){
        mx[p]=max(mx[p<<1],mx[p<<1|1]);
    }

    void update(ll p,ll l,ll r,ll x,ll v){
        if(l==r){
            mx[p]=v;
            return;
        }
        ll m=l+r>>1;
        if(x<=m) update(p<<1,l,m,x,v);
        else update(p<<1|1,m+1,r,x,v);
        up(p,l,r);
    }

    ll query(ll p,ll l,ll r,ll x,ll y){
        if(x<=l&&r<=y) return mx[p];
        ll m=l+r>>1;
        ll res=LLONG_MIN/2;
        if(x<=m) res=max(res,query(p<<1,l,m,x,y));
        if(y>m) res=max(res,query(p<<1|1,m+1,r,x,y));
        return res;
    }
};

void solve(){
    ll n,dh,dx;
    cin>>n>>dh>>dx;
    vector<ll> a(n+1);
    vector<ll> pos(n+1);
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        pos[a[i]]=i;
    }
    SGT sgt(n+1);
    vector<ll> f(n+1,0);
    for(ll h=1;h<=n;h++){
        if(h-dh>=1){
            sgt.update(1,1,sgt.n,pos[h-dh],f[h-dh]);
        }
        f[h]=max(f[h],sgt.query(1,1,sgt.n,max(0ll,pos[h]-dx),min(n,pos[h]+dx))+1);
    }
    cout<<*max_element(f.begin()+1,f.end())<<endl;
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
