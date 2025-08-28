//https://www.luogu.com.cn/problem/P3870
//@@@
//seg(flip)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// 定义一个函数 Log，用于输出一个 vector<ll> 类型的数组 a 的内容
void Log(vector<ll>& a){
    // 输出 "Log: " 作为日志的标题
	cout<<"Log: ";
	// 使用 for 循环遍历数组 a 的每一个元素
	for(int i=0;i<a.size();i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

class segment_tree{
public:
	ll n;
	vector<ll> sum;
	vector<bool> flip;

	segment_tree(ll sz):n(sz-1),sum(sz<<2),flip(sz<<2){}

	void up(ll p){
		sum[p]=sum[p<<1]+sum[p<<1|1];
	}

	void flip_update(ll p,ll l,ll r){
		ll n=r-l+1;
		sum[p]=n-sum[p];
		flip[p]=!flip[p];
	}
	
	void down(ll p,ll l,ll r){
		ll m=l+r>>1;
		ll ln=m-l+1;
		ll rn=r-m;
		if(flip[p]){
			flip_update(p<<1,l,m);
			flip_update(p<<1|1,m+1,r);
			flip[p]=false;
		}
	}
	
	void update(ll p,ll l,ll r,ll x,ll y){
		if(x<=l&&r<=y){
			flip_update(p,l,r);
			return;
		}
		ll m=l+r>>1;
		down(p,l,r);
		if(x<=m) update(p<<1,l,m,x,y);
		if(y>m) update(p<<1|1,m+1,r,x,y);
		up(p);
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
};

void solve(){
	ll n,m;
	cin>>n>>m;
	segment_tree seg(n+1);
	for(ll i=1,op,x,y;i<=m;i++){
		cin>>op>>x>>y;
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
