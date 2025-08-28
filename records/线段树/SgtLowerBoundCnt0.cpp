//https://acm.hdu.edu.cn/submit.php?pid=4614
//@@@
//seg,bianry search
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

class segment_tree{
public:
    ll n;
    vector<ll> sum,rstval;
    vector<bool> rst;

    segment_tree(ll sz):n(sz-1),sum(sz<<2),rst(sz<<2),rstval(sz<<2) {}

    void up(ll p){
        sum[p]=sum[p<<1]+sum[p<<1|1];
    }

    void rst_update(ll p,ll l,ll r,ll v){
        ll n=r-l+1;
        sum[p]=n*v;
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
            rst_update(p,l,r,v);\
            return;
        }
        ll m=l+r>>1;
        down(p,l,r);
        if(x<=m) update(p<<1,l,m,x,y,v);
        if(y>m) update(p<<1|1,m+1,r,x,y,v);
        up(p);
    }
    
    ll query(ll p,ll l,ll r,ll x,ll y){
        if(x<=l&&r<=y){
            return sum[p];
        }
        ll m=l+r>>1; 
        down(p,l,r);
        ll ans=0;
        if(x<=m) ans+=query(p<<1,l,m,x,y);
        if(y>m) ans+=query(p<<1|1,m+1,r,x,y);
        return ans;
    }

    ll lower_bound_cnt0(ll v){
        function<ll(ll,ll,ll,ll,ll)> binary_search=[&](ll p,ll l,ll r,ll v,ll above)->ll{
            ll len=r-l+1;
            if(l==r){
                if(above+(len-sum[p])>=v) return l;
                assert(0);
            }
            down(p,l,r);
            ll m=l+r>>1;
            ll ln=m-l+1;
            if(above+(ln-sum[p<<1])>=v) return binary_search(p<<1,l,m,v,above);
            if(above+(len-sum[p])>=v) return binary_search(p<<1|1,m+1,r,v,above+(ln-sum[p<<1]));
            return -1;
        };
        return binary_search(1,1,n,v,0);
    }

    ll lower_bound_cnt0(ll s,ll v){
        if(s==1) return lower_bound_cnt0(v);
        return lower_bound_cnt0(v+(s-1-query(1,1,n,1,s-1)));
    }
    
    pair<ll,ll> insert_flower(ll from,ll tot){
        ll cnt0=(n-from+1)-query(1,1,n,from,n);
        if(cnt0==0) return {-1,-1};
        tot=min(tot,cnt0);
        ll l=lower_bound_cnt0(from,1);
        ll r=lower_bound_cnt0(from,tot);
        update(1,1,n,l,r,1);
        return {l-1,r-1};
    }

    ll clear_flower(ll left,ll right){
        ll res=query(1,1,n,left,right);
        update(1,1,n,left,right,0);
        return res;
    }
};

void solve(){
    ll n,m;
    cin>>n>>m;
    segment_tree seg(n+1);
    for(ll i=0;i<m;i++){
        ll op;
        cin>>op;
        if(op==1){
            ll from,tot;
            cin>>from>>tot;
			from++;
            auto res=seg.insert_flower(from,tot);
            if(res.first==-1){
                cout<<"Can not put any one."<<endl;
            }else{
                cout<<res.first<<" "<<res.second<<endl;
            }
        }else{
            ll left,right;
            cin>>left>>right;
			left++,right++;
            cout<<seg.clear_flower(left,right)<<endl;
        }
    }
    cout<<endl;
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