//https://www.luogu.com.cn/problem/P6492
//@@@
//seg
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class segment_tree{
public:
	ll n;
	vector<ll>& a;
	vector<ll> len,pre,suf;
	segment_tree(vector<ll>& a):a(a) {
		n=a.size()-1;
		len.resize(n<<2);
		pre.resize(n<<2);
		suf.resize(n<<2);
        build(1,1,n);
	}

    void build(ll p,ll l,ll r){
        if(l==r){
            pre[p]=suf[p]=len[p]=1;
            return;
        }
        ll m=l+r>>1;
        build(p<<1,l,m);
        build(p<<1|1,m+1,r);
        up(p,l,r);
    }

	void up(ll p,ll l,ll r){
		ll m=l+r>>1;
		ll ln=m-l+1,rn=r-m;
		len[p]=max({len[p<<1],len[p<<1|1]});
		pre[p]=pre[p<<1];
		suf[p]=suf[p<<1|1];
		if(a[m]^a[m+1]){
			len[p]=max({len[p],suf[p<<1]+pre[p<<1|1]});
			if(len[p<<1]==ln){
				pre[p]=ln+pre[p<<1|1];
			}
			if(len[p<<1|1]==rn){
				suf[p]=rn+suf[p<<1];
			}
		}
	}
	
	void update(ll p,ll l,ll r,ll x){
		if(l==r){
			a[x]^=1;
			return;
		}
		ll m=(l+r)>>1;
		if(x<=m) update(p<<1,l,m,x);
		else update(p<<1|1,m+1,r,x);
		up(p,l,r);
	}
	
};

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<ll> a(n+1);
	segment_tree seg(a);
	for(ll i=1;i<=m;i++){
		ll x;
		cin>>x;
		seg.update(1,1,seg.n,x);
		cout<<seg.len[1]<<endl;
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
