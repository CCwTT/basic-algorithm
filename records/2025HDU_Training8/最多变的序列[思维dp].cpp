//https://acm.hdu.edu.cn/contest/problem?cid=1179&pid=1012
//@@@
//dp
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const int N=3005;
const int MOD=998244353;

void solve(){
	ll n;
	cin>>n;
	vector<ll> a(n+2),dp(n+2);
	for(int i=1;i<=n;i++) cin>>a[i];
	dp[0]=1;
	for(int i=1,l,r;i<=n;i++){
		for(l=i;a[l-1]>a[i];l--);
		for(r=i;a[r+1]>a[i];r++);
		for(int j=l;j<=r;j++){
			(dp[j]+=dp[j-1])%=MOD;
		}
	}
	cout<<dp[n]<<endl;
	
}

signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	ll T=1;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
