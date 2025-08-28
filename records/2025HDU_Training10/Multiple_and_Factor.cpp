#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
#define EPS (1e-20)
typedef long long ll;
typedef __int128 i128;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

using namespace std;

const ll N=500010;
const ll M=800;
const ll B=300;

ll n,m;
ll a[N],sprinkle[B],collect[B];
vector<ll> factor[N];

void solve(){
	cin>>n>>m;
	for(ll i=1;i<=n;i++){
		for(ll j=i;j<=n;j+=i){
			factor[j].emplace_back(i);
		}
	}
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	} 
	for(ll i=1;i<=B;i++){
		for(ll j=i;j<=n;j+=i){
			collect[i]+=a[j];
		}
	}
	while(m--){
		ll op,x,k;
		cin>>op>>x;
		if(op==1){
			cin>>k;
			if(x<=B){
				sprinkle[x]+=k;
			} else{
				for(ll i=x;i<=n;i+=x)
					a[i]+=k;
			}
			for(ll i=1;i<=B;i++){
				collect[i]+=k*(n/lcm(i,x));
			}
		} else if(op==2){
			cin>>k;
			for(ll i:factor[x])
				a[i]+=k;
			for(ll i=1;i<=B;i++){
				if(x%i==0) collect[i]+=k*factor[x/i].size();
			} 
		} else if(op==3){
			if(x<=B){
				cout<<collect[x]<<'\n';
			} else{
				ll ans=0;
				for(ll i=x;i<=n;i+=x)
					ans+=a[i];
				for(ll i=1;i<=B;i++){
					ans+=sprinkle[i]*(n/lcm(i,x));
				} 
				cout<<ans<<'\n';
			}
		} else{
			ll ans=0;
			for(ll i:factor[x]){
				ans+=a[i];
				if(i<=B)
					ans+=sprinkle[i]*factor[x/i].size();
			}
			cout<<ans<<'\n';
		}
	}
}

void clear(){}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	ll T=1;
	//cin>>T;
	while(T--){
		solve();
		clear();
	}
	return 0;
}

