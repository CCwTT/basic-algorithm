//https://acm.hdu.edu.cn/showproblem.php?pid=5306
//@@@
//jiry segment tree
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;


class segment_tree{
public:
    ll n;
    vector<ll>& a;
    vector<ll> sum,mx,cnt,sem;
	vector<bool> tag;
    segment_tree(ll sz,vector<ll>& a):n(sz-1),a(a),sum(n<<2),mx(n<<2),cnt(n<<2),sem(n<<2),tag(n<<2){
        build(1,1,n);
    }
    void up(ll p) {
        sum[p]=sum[p<<1]+sum[p<<1|1];
        mx[p]=max(mx[p<<1],mx[p<<1|1]);
        if(mx[p<<1]>mx[p<<1|1]){
            cnt[p]=cnt[p<<1];
            sem[p]=max(sem[p<<1],mx[p<<1|1]);
        }else if(mx[p<<1]<mx[p<<1|1]){
            cnt[p]=cnt[p<<1|1];
            sem[p]=max(mx[p<<1],sem[p<<1|1]);
        }else{
            cnt[p]=cnt[p<<1]+cnt[p<<1|1];
            sem[p]=max(sem[p<<1],sem[p<<1|1]);
        }
    }

    void down(ll p){
        if(mx[p]<mx[p<<1]){
            sum[p<<1]-=(ll)(mx[p<<1]-mx[p])*cnt[p<<1];
            mx[p<<1]=mx[p];
        }
        if(mx[p]<mx[p<<1|1]){
            sum[p<<1|1]-=(ll)(mx[p<<1|1]-mx[p])*cnt[p<<1|1];
            mx[p<<1|1]=mx[p];
        }
    }

    void build(ll p,ll l,ll r){
		tag[p]=false;
        if(l==r) {
            sum[p]=a[l];
            mx[p]=a[l];
            cnt[p]=1;
            sem[p]=-1;
            return;
        }
        ll m=(l+r)>>1;
        build(p<<1,l,m);
        build(p<<1|1,m+1,r);
        up(p);
    }

    void update(ll p,ll l,ll r,ll x,ll y,ll v){
        if(v>=mx[p]){
            return;
        }
        if(x<=l&&r<=y&&sem[p]<v){
            sum[p]-=(mx[p]-v)*cnt[p];
            mx[p]=v;
            return;
        }
        down(p);
        ll m=(l+r)>>1;
        if(x<=m) update(p<<1,l,m,x,y,v);
        if(y>m) update(p<<1|1,m+1,r,x,y,v);
        up(p);
    }

    ll query_max(ll p,ll l,ll r,ll x,ll y){
        if(x<=l&&r<=y) {
            return mx[p];
        }
        down(p);
        ll m=(l+r)>>1;
        ll res=LLONG_MIN;
        if(x<=m) res=max(res,query_max(p<<1,l,m,x,y));
        if(y>m) res=max(res,query_max(p<<1|1,m+1,r,x,y));
        return res;
    }

    ll query_sum(ll p,ll l,ll r,ll x,ll y ) {
        if(x<=l&&r<=y) {
            return sum[p];
        }
        down(p);
        ll m=(l+r)>>1;
        ll res=0;
        if(x<=m) res+=query_sum(p<<1,l,m,x,y);
        if(y>m) res+=query_sum(p<<1|1,m+1,r,x,y);
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
        if(op==0){
            cin>>x>>y>>v;
            seg.update(1,1,seg.n,x,y,v);
        } else if(op == 1) {
            cin>>x>>y;
            cout<<seg.query_max(1,1,seg.n,x,y)<<endl;
        } else {
            cin>>x>>y;
            cout<<seg.query_sum(1,1,seg.n,x,y)<<endl;
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}