//https://acm.hdu.edu.cn/showproblem.php?pid=5306
//@@@
//struct + vector 2730~>3000 medium 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class SGT{
public:
    ll n;
    struct Node{
        ll ma,t,se,s;
        bool tag;
    };
    vector<Node> node;
    vector<ll>& a;
    SGT(ll sz,vector<ll>& a):n(sz-1),a(a),node(n<<2){
        build(1,1,n);
    }
    void up(ll p,ll l,ll r){
        node[p].ma=max(node[p<<1].ma,node[p<<1|1].ma);
        ll m=(l+r)/2;
        if(node[p<<1].ma==node[p<<1|1].ma){
            node[p].ma=node[p<<1].ma;
            node[p].t=node[p<<1].t+node[p<<1|1].t;
            node[p].se=max(node[p<<1].se,node[p<<1|1].se);
        }else if(node[p<<1].ma>node[p<<1|1].ma){
            node[p].ma=node[p<<1].ma;
            node[p].t=node[p<<1].t;
            node[p].se=max(node[p<<1].se,node[p<<1|1].ma);
        }else{
            node[p].ma=node[p<<1|1].ma;
            node[p].t=node[p<<1|1].t;
            node[p].se=max(node[p<<1].ma,node[p<<1|1].se);
        }
        node[p].s=node[p<<1].s+node[p<<1|1].s;
    }
    
    void build(ll p,ll l,ll r){
        if(l==r){
            node[p].tag=false;
            node[p].s=a[l];
            node[p].ma=a[l];
            node[p].t=1;
            node[p].se=-1;
        }else{
            ll m=(l+r)/2;
            build(p<<1,l,m);
            build(p<<1|1,m+1,r);
            up(p,l,r);
        }
    }
    
    void down(ll p){
        ll v=node[p].ma;
        node[p].tag=false;
        if(node[p<<1].ma>v&&node[p<<1].se<v){
            node[p<<1].tag=true;
            node[p<<1].s-=(node[p<<1].ma-v)*(ll)node[p<<1].t;
            node[p<<1].ma=v;
        }
        if(node[p<<1|1].ma>v&&node[p<<1|1].se<v){
            node[p<<1|1].tag=true;
            node[p<<1|1].s-=(node[p<<1|1].ma-v)*(ll)node[p<<1|1].t;
            node[p<<1|1].ma=v;
        }
    }
    
    void update(ll p,ll l,ll r,ll x,ll y,ll v){
        ll m=(l+r)/2;
        if(l==x&&r==y&&v>node[p].se){
            if(v>=node[p].ma) return;
            else{
                node[p].s-=(node[p].ma-v)*(ll)node[p].t;
                node[p].ma=v;
                node[p].tag=true;
                return;
            }
        }
        if(node[p].tag) down(p);
        if(y<=m) update(p<<1,l,m,x,y,v);
        else if(x>m) update(p<<1|1,m+1,r,x,y,v);
        else update(p<<1,l,m,x,m,v),update(p<<1|1,m+1,r,m+1,y,v);
        up(p,l,r);
    }
    
    ll query_max(ll p,ll l,ll r,ll x,ll y){
        ll m=(l+r)/2;
        if(l==x&&r==y) return node[p].ma;
        if(node[p].tag) down(p);
        if(y<=m) return query_max(p<<1,l,m,x,y);
        else if(x>m) return query_max(p<<1|1,m+1,r,x,y);
        else return max(query_max(p<<1,l,m,x,m),query_max(p<<1|1,m+1,r,m+1,y));
    }
    
    ll query_sum(ll p,ll l,ll r,ll x,ll y){
        ll m=(l+r)/2;
        if(l==x&&r==y) return node[p].s;
        if(node[p].tag) down(p);
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