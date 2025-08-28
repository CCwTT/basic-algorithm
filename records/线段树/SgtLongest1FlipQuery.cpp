//https://www.luogu.com.cn/problem/P2572
//@@@
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class segment_tree{
public:
    ll n;
    vector<ll>& a;
    vector<ll> sum,len0,len1,pre0,pre1,suf0,suf1,rstval;
    vector<bool> rst,flip;
    segment_tree(vector<ll>& a):a(a){
        n=a.size()-1;
        sum.resize(n<<2);
        len0.resize(n<<2);
        len1.resize(n<<2);
        pre0.resize(n<<2);
        pre1.resize(n<<2);
        suf0.resize(n<<2);
        suf1.resize(n<<2);
        rstval.resize(n<<2);
        rst.resize(n<<2);
        flip.resize(n<<2);
        build(1,1,n);
    }

    void up(ll p,ll l,ll r){
        ll m=l+r>>1;
        ll ln=m-l+1,rn=r-m;
        sum[p]=sum[p<<1]+sum[p<<1|1];
        len0[p]=max({len0[p<<1],len0[p<<1|1],suf0[p<<1]+pre0[p<<1|1]});
        pre0[p]=len0[p<<1]<ln?pre0[p<<1]:(pre0[p<<1]+pre0[p<<1|1]);
        suf0[p]=len0[p<<1|1]<rn?suf0[p<<1|1]:(suf0[p<<1|1]+suf0[p<<1]);
        len1[p]=max({len1[p<<1],len1[p<<1|1],suf1[p<<1]+pre1[p<<1|1]});
        pre1[p]=len1[p<<1]<ln?pre1[p<<1]:(pre1[p<<1]+pre1[p<<1|1]);
        suf1[p]=len1[p<<1|1]<rn?suf1[p<<1|1]:(suf1[p<<1|1]+suf1[p<<1]);
    }
    
    void rst_update(ll p,ll l,ll r,ll v){
        ll n=(r-l+1);
        sum[p]=v*n;
        len0[p]=pre0[p]=suf0[p]=v==0?n:0;
        len1[p]=pre1[p]=suf1[p]=v==1?n:0;
        rstval[p]=v;
        rst[p]=true;
        flip[p]=false;
    }
    
    void flip_update(ll p,ll l,ll r){
        ll n=r-l+1;
        sum[p]=n-sum[p];
        swap(len0[p],len1[p]);
        swap(pre0[p],pre1[p]);
        swap(suf0[p],suf1[p]);
        flip[p]=!flip[p];
    }
    
    void down(ll p,ll l,ll r){
        ll m=l+r>>1;
        ll ln=m-l+1,rn=r-m;
        if(rst[p]){
            rst_update(p<<1,l,m,rstval[p]);
            rst_update(p<<1|1,m+1,r,rstval[p]);
            rst[p]=false;
        }
        if(flip[p]){
            flip_update(p<<1,l,m);
            flip_update(p<<1|1,m+1,r);
            flip[p]=false;
        }
    }
    
    void build(ll p,ll l,ll r){
        rst[p]=flip[p]=false;
        if(l==r){
            sum[p]=a[l];
            len0[p]=pre0[p]=suf0[p]=a[l]==0?1:0;
            len1[p]=pre1[p]=suf1[p]=a[l]==1?1:0;
            return;
        }
        ll m=l+r>>1;
        build(p<<1,l,m);
        build(p<<1|1,m+1,r);
        up(p,l,r);
    }
    
    void update_rst(ll p,ll l,ll r,ll x,ll y,ll v){
        if(x<=l&&r<=y){
            rst_update(p,l,r,v);
            return;
        }
        ll m=l+r>>1;
        down(p,l,r);
        if(x<=m) update_rst(p<<1,l,m,x,y,v);
        if(y>m) update_rst(p<<1|1,m+1,r,x,y,v);
        up(p,l,r);
    }
    
    void update_flip(ll p,ll l,ll r,ll x,ll y){
        if(x<=l&&r<=y){
            flip_update(p,l,r);
            return;
        }
        ll m=l+r>>1;
        down(p,l,r);
        if(x<=m) update_flip(p<<1,l,m,x,y);
        if(y>m) update_flip(p<<1|1,m+1,r,x,y);
        up(p,l,r);
    }
    
    ll query_sum(ll p,ll l,ll r,ll x,ll y){
        if(x<=l&&r<=y){
            return sum[p];
        }
        ll m=l+r>>1;
        down(p,l,r);
        ll res=0;
        if(x<=m) res+=query_sum(p<<1,l,m,x,y);
        if(y>m) res+=query_sum(p<<1|1,m+1,r,x,y);
        return res;
    }
    
    tuple<ll,ll,ll> query_longest(ll p,ll l,ll r,ll x,ll y){
        if(x<=l&&r<=y){
            return {len1[p],pre1[p],suf1[p]};
        }
        ll m=l+r>>1;
        ll ln=m-l+1;
        ll rn=r-m;
        down(p,l,r);
        if(y<=m) return query_longest(p<<1,l,m,x,y);
        if(x>m) return query_longest(p<<1|1,m+1,r,x,y);
        auto [llen,lpre,lsuf]=query_longest(p<<1,l,m,x,y);
        auto [rlen,rpre,rsuf]=query_longest(p<<1|1,m+1,r,x,y);
        return {
            max({llen,rlen,lsuf+rpre}),
            llen<ln?lpre:(lpre+rpre),
            rlen<rn?rsuf:(lsuf+rsuf)
        };
    }
};

void solve(){
	ll n,m;
	cin>>n>>m;
    vector<ll> a(n+1);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	}
    segment_tree seg(a);
	for(ll i=1;i<=m;i++){
		ll op,x,y;
		cin>>op>>x>>y;
		x++,y++;
		if(op==0){
			seg.update_rst(1,1,seg.n,x,y,0);
		}else if(op==1){
			seg.update_rst(1,1,seg.n,x,y,1);
		}else if(op==2){
			seg.update_flip(1,1,seg.n,x,y);
		}else if(op==3){
			cout<<seg.query_sum(1,1,seg.n,x,y)<<endl;
		}else{
			cout<<get<0>(seg.query_longest(1,1,seg.n,x,y))<<endl;
		}
	}
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
	ll T=1;
	while(T--){
		solve();
	}
    return 0;
}
