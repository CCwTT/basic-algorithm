//https://atcoder.jp/contests/abc399/tasks/abc399_d
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
	ll n;
	cin>>n;
	vector<ll> a(2*n+2);
	for(ll i=1;i<=2*n;i++){
		cin>>a[i];
	}
	a[0]=-1;
	a[2*n+1]=-2;
	vector<vector<ll>> pos(n+1);
	for(ll i=1;i<=2*n;i++){
		pos[a[i]].push_back(i);
	}
	ll ans=0;
	for(ll i=1;i<=n;i++){
		if(pos[i][0]+1==pos[i][1]) continue;
		ll u=a[pos[i][0]-1];
		ll v=a[pos[i][0]+1];
		ll p=a[pos[i][1]-1];
		ll q=a[pos[i][1]+1];
		if(u==p) ans++;
		if(u==q) ans++;
		if(v==p&&pos[i][1]-pos[i][0]>3) ans++;
		if(v==q) ans++;
	}
//	unordered_set<ll> st;
//	for(ll i=2;i<=2*n;i++){
//		ll x=a[i];
//		ll y=a[i-1];
//		if(pos[x][0]+1==pos[x][1]||pos[y][0]+1==pos[y][1]) continue;
//		vector<ll> tmp={pos[x][0],pos[x][1],pos[y][0],pos[y][1]};
//		sort(tmp.begin(),tmp.end());
//		if(tmp[0]+1==tmp[1]&&tmp[2]+1==tmp[3]){
//			st.insert((min(x,y)<<32)|max(x,y));
//		}
//	}
	cout<<ans/2<<endl;
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
