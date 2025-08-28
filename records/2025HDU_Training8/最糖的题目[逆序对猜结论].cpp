//https://acm.hdu.edu.cn/contest/problem?cid=1179&pid=1004
//@@@
//逆序对猜结论
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

struct discretizer{
	vector<ll> disc={LLONG_MIN};
	void init(){
		disc={LLONG_MIN};
	}
	void insert(ll x){
		disc.push_back(x);
	}
	ll discretize(){
		sort(disc.begin(),disc.end());
		disc.erase(unique(disc.begin(),disc.end()),disc.end());
		return disc.size()-1;
	}
	ll get_rank(ll x){
		return lower_bound(disc.begin(),disc.end(),x)-disc.begin();
	}
}disc;

const ll N=1e5+5;
ll fw[N];

void fw_update(ll x,ll v){
	while(x<N){
		fw[x]+=v;
		x+=x&-x;
	}
}

ll fw_query(ll x){
	ll res=0;
	while(x>1){
		res+=fw[x];
		x&=x-1;
	}
	return res;
}

ll f(vector<ll>& a){
	ll n=a.size()-2;
	memset(fw,0,sizeof fw);
	disc.init();
	for(ll i=1;i<=n;i++) disc.insert(a[i]);
	disc.discretize();
	ll res=0;
	for(ll i=1;i<=n;i++){
		ll x=disc.get_rank(a[i]);
		res+=i-1-fw_query(x);
		fw_update(x,1);
	}
	return res;
}

void solve(){
	ll n,k;
	cin>>n>>k;
	vector<ll> a(n+2),b(n+2);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	}
	for(ll i=1;i<=n;i++){
		cin>>b[i];
	}
	if(k==1){
		for(ll i=1;i<=n;i++){
			if(a[i]!=b[i]){
				cout<<"NO"<<endl;
				return;
			}
		}
		cout<<"YES"<<endl;
		return;
	}
	unordered_map<ll,ll> mp;
	for(ll i=1;i<=n;i++){
		mp[a[i]]++;
	}
	for(ll i=1;i<=n;i++){
		mp[b[i]]--;
	}
	for(auto [x,c]:mp){
		if(c){
			cout<<"NO"<<endl;
			return;
		}
	}
	if(mp.size()<n){
		cout<<"YES"<<endl;
		return;
	}
	ll cnt1=f(a);
	ll cnt2=f(b);
	if(k&1){
		if((cnt1&1)==(cnt2&1)){
			cout<<"YES"<<endl;
		}else{
			cout<<"NO"<<endl;
		}
	}else{
		cout<<"YES"<<endl;
	}
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