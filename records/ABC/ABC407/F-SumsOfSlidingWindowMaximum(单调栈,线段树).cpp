//https://atcoder.jp/contests/abc407/tasks/abc407_f
//@@@
//monotonic stack,sgt
//link:/线段树/BoringSequence(提供用户接口)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> get_lnb(vector<ll>& a){
    ll n=a.size();
    vector<ll> lnb(n,-1);
    stack<ll> stk;
    for(ll i=0;i<n;i++){
        while(!stk.empty()&&a[stk.top()]<=a[i]){
            stk.pop();
        }
        if(stk.size()){
            lnb[i]=stk.top();
        }
        stk.push(i);
    }
    return lnb;
}

vector<ll> get_rnb(vector<ll>& a){
    ll n=a.size();
    vector<ll> rnb(n,n);
    stack<ll> stk;
    for(ll i=n-1;i>=0;i--){
        while(!stk.empty()&&a[stk.top()]<a[i]){
            stk.pop();
        }
        if(stk.size()){
            rnb[i]=stk.top();
        }
        stk.push(i);
    }
    return rnb;
}

class SGT{
public:
	ll n;
	vector<ll> sum,add;

	SGT(ll sz):n(sz-1),sum(n<<2),add(n<<2) {}

	void up(ll p,ll l,ll r){
		sum[p]=sum[p<<1]+sum[p<<1|1];
	}

	void add_update(ll p,ll l,ll r,ll v){
		ll n=r-l+1;
		sum[p]+=n*v;
		add[p]+=v;
	}

	void down(ll p,ll l,ll r){
		ll m=l+r>>1;
		if(add[p]){
			add_update(p<<1,l,m,add[p]);
			add_update(p<<1|1,m+1,r,add[p]);
			add[p]=0;
		}
	}

	void update(ll p,ll l,ll r,ll x,ll y,ll v){
        if(x>y) return;
		if(x<=l&&r<=y){
			add_update(p,l,r,v);
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
			return sum[p];
		}
		ll m=l+r>>1;
		down(p,l,r);
		ll res=0;
		if(x<=m) res+=query(p<<1,l,m,x,y);
		if(y>m) res+=query(p<<1|1,m+1,r,x,y);
		return res;
	}

	void user_update(ll x,ll y,ll k,ll d){
		update(1,1,n,x,x,k);
		if(y-x>=1){
			update(1,1,n,x+1,y,d);
		}
		if(y+1<=n){
			update(1,1,n,y+1,y+1,-(k+(y-x)*d));
		}
	}

	ll user_query(ll x){
		return query(1,1,n,1,x);
	}
};

void solve(){
    ll n;
    cin>>n;
    vector<ll> a(n);
    for(ll i=0;i<n;i++){
        cin>>a[i];
    }
    vector<pair<ll,ll>> A(n);
    for(ll i=0;i<n;i++){
        A[i]={a[i],i};
    }
    sort(A.begin(),A.end());
    auto lnb=get_lnb(a);
    auto rnb=get_rnb(a);
    SGT sgt(n+1);
    for(ll i=n-1;i>=0;i--){
        auto [val,idx]=A[i];

        ll r=rnb[idx]-idx-1;
        ll l=idx-lnb[idx]-1;

        ll mn=min(l,r),mx=max(l,r);
        sgt.user_update(1,1+mn,val,val);
        sgt.user_update(2+mn,1+mx,(1+mn)*val,0);
        sgt.user_update(2+mx,2+mn+mx,mn*val,-val);
    }
    for(ll i=1;i<=n;i++){
        cout<<sgt.user_query(i)<<endl;
    }
}

signed main() {
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}