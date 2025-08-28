//https://www.luogu.com.cn/problem/P4145
//@@@
//seg,potential analysis(n(logn)^2)
//segment_tree with potential analysis needs no lazy tag and pushdown
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void Log(vector<ll>& a){
	cout<<"Log: ";
	for(int i=0;i<a.size();i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

class segment_tree{
public:
    ll n;
    vector<ll>& a;
    vector<ll> sum,mx;

    segment_tree(vector<ll>& a):a(a){
        n=a.size()-1;
        sum.resize(n<<2);
        mx.resize(n<<2);
        build(1,1,n);
    }

    void up(ll p){
        sum[p]=sum[p<<1]+sum[p<<1|1];
        mx[p]=max({mx[p<<1],mx[p<<1|1]});
    }

    void build(ll p,ll l,ll r){
        if(l==r){
            sum[p]=a[l];
            mx[p]=a[l];
            return;
        }
        ll m=(l+r)>>1;
        build(p<<1,l,m);
        build(p<<1|1,m+1,r);
        up(p);
    }

    void update(ll p,ll l,ll r,ll x,ll y){
        if(l==r){
            sum[p]=mx[p]=(ll)(sqrt(mx[p]));
            return;
        }
        ll m=(l+r)>>1;
        if(x<=m&&mx[p<<1]>1) update(p<<1,l,m,x,y);
        if(y>m&&mx[p<<1|1]>1) update(p<<1|1,m+1,r,x,y);
        up(p);
    }

    ll query(ll p,ll l,ll r,ll x,ll y){
        if(x<=l&&r<=y){
            return sum[p];
        }
        ll m=(l+r)>>1;
        ll res=0;
        if(x<=m) res+=query(p<<1,l,m,x,y);
        if(y>m) res+=query(p<<1|1,m+1,r,x,y);
        return res;
    }
};

void solve(){
	ll n;
	cin>>n;
    vector<ll> a(n+1);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	}
	segment_tree seg(a);
	ll m;
	cin>>m;
	for(ll i=1,op,x,y;i<=m;i++){
		cin>>op>>x>>y;
		if(x>y){
			swap(x,y);
		}
		if(op==0){
			seg.update(1,1,seg.n,x,y);
		}else{
			cout<<seg.query(1,1,seg.n,x,y)<<endl;
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