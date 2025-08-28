// 错误答案数量，带权并查集模版题3
// 有n个数字，下标1 ~ n，但是并不知道每个数字是多少
// 操作 l r v，代表l~r范围上累加和为v
// 一共m个操作，如果某个操作和之前的操作信息自相矛盾，认为当前操作是错误的，不进行这个操作
// 最后打印错误操作的数量
// 1 <= n <= 200000    1 <= m <= 40000
// 累加和不会超过int类型范围
// 测试链接 : https://acm.hdu.edu.cn/showproblem.php?pid=3038
// 测试链接 : https://vjudge.net/problem/HDU-3038
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
	while(cin>>n>>m){
		ll ans=0;
		WDsu dsu(n+2);
		for(ll i=1;i<=m;i++){
			ll x,y,v;
			cin>>x>>y>>v;
			if(!dsu.check(x,y+1)){
				dsu.join(x,y+1,v);
			}else{
				if(v!=dsu.query(x,y+1)){
					ans++;
				}
			}
		}
		cout<<ans<<endl;	
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
