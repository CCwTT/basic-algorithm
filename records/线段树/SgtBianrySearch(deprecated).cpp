//https://acm.hdu.edu.cn/submit.php?pid=4614
//@@@
//seg,bianry search
#include<bits/stdc++.h>
using namespace std;
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
            rst_update(p,l,r,v);
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
    
    pair<ll,ll> insert_flower(ll from,ll tot){
        ll cnt0=(n-from+1)-query(1,1,n,from,n);
        if(cnt0==0) return {-1,-1};
        tot=min({tot,cnt0});
        ll l=from,r=n;
		ll ans2=-1;
        while(l<=r){
            ll mid=l+r>>1;

			auto check=[&](ll mid)->bool{
				ll cnt0=(mid-from+1)-query(1,1,n,from,mid);
				return cnt0>=tot;
			};
            
			if(check(mid)){
                ans2=mid;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        l=from,r=ans2;
		ll ans1=from;
        while(l<=r){
            ll mid=l+r>>1;

			auto check=[&](ll mid)->bool{
				ll cnt0=(mid-from+1)-query(1,1,n,from,mid);
				return cnt0>0;
			};
            
            if(check(mid)){
                ans1=mid;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        update(1,1,n,ans1,ans2,1);
        return {ans1-1,ans2-1};
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