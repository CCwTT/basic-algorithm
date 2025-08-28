
// 狡猾的商人，带权并查集模版题2
// 有n个月的收入，下标1 ~ n，但是并不知道每个月收入是多少
// 操作 l r v，代表从第l个月到第r个月，总收入为v
// 一共给你m个操作，请判断给定的数据是自洽还是自相矛盾
// 自洽打印true，自相矛盾打印false
// 1 <= n <= 100    1 <= m <= 1000
// 总收入不会超过int类型范围
// 测试链接 : https://www.luogu.com.cn/problem/P2294
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
	ll n,m;
	cin>>n>>m;
	WDsu dsu(n+2);
	bool ok=true;
	for(ll i=1;i<=m;i++){
		ll x,y,v;
		cin>>x>>y>>v;
		if(!ok) continue;
		if(dsu.check(x,y+1)){
			if(v!=dsu.query(x,y+1)){
				ok=false;
			}
		}else{
			dsu.join(x,y+1,v);
		}
	}
	cout<<(ok==true?"true":"false")<<endl;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	ll T=1;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
} 
