
// 推导部分和，带权并查集模版题1
// 有n个数字，下标1 ~ n，但是并不知道每个数字是多少
// 先给出m个数字段的累加和，再查询q个数字段的累加和
// 给出数字段累加和的操作 l r v，代表l~r范围上的数字，累加和为v
// 查询数字段累加和的操作 l r，代表查询l~r范围上的数字累加和
// 请根据m个给定，完成q个查询，如果某个查询无法给出答案，打印"UNKNOWN"
// 1 <= n, m, q <= 10^5
// 累加和不会超过long类型范围
// 测试链接 : https://www.luogu.com.cn/problem/P8779
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class WDsu{
public:
	vector<ll> f;
	vector<ll> dist;

	WDsu(ll n):f(n),dist(n){
		iota(f.begin(),f.end(),0);
	}

	ll find(ll x){
		ll _fx=f[x];
		return f[x]==x?x:(f[x]=find(f[x]),dist[x]+=dist[_fx],f[x]);
	}

	//y is the referenced system
	void join(ll x,ll y,ll v){
		ll fx=find(x);
		ll fy=find(y);
		if(fx==fy) return;
		f[fy]=fx;
		dist[fy]=v+dist[x]-dist[y];
	}

	bool check(ll x,ll y){
		return find(x)==find(y);
	}

	ll query(ll x,ll y){
		return check(x,y)?dist[y]-dist[x]:LLONG_MAX;
	}
};

void solve(){
	ll n,m,q;
	cin>>n>>m>>q;
	WDsu dsu(n+2);
	for(ll i=1;i<=m;i++){
		ll x,y,v;
		cin>>x>>y>>v;
		dsu.join(x,y+1,v);
	}
	for(ll i=1;i<=q;i++){
		ll x,y;
		cin>>x>>y;
		ll ret=dsu.query(x,y+1);
		if(ret==LLONG_MAX){
			cout<<"UNKNOWN"<<endl;
		}else{
			cout<<ret<<endl;
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
