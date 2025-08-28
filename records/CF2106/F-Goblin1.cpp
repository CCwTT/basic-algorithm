//https://codeforces.com/problemset/problem/2106/F
//@@@
//Dsu
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void Log(vector<ll>& a){
	ll n=a.size();
	for(ll i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

class Dsu{
public:	
	vector<ll> f,cnt0;
	Dsu(ll n):f(n),cnt0(n){
		iota(f.begin(),f.end(),0);
	} 
	ll find(ll x){
		return f[x]==x?x:f[x]=find(f[x]);
	}
	void join(ll x,ll y){
		ll fx=find(x);
		ll fy=find(y);
		if(fx==fy) return;
		cnt0[fx]+=cnt0[fy];
		f[fy]=fx;
	}
	bool check(ll x,ll y){
		return find(x)==find(y);
	}
};


void solve(){
	ll n;
	cin>>n;
	string s;
	cin>>s;
	Dsu dsu(n<<1);
	if(s[0]=='1'){
		dsu.cnt0[0]=1;
		dsu.cnt0[1]=0;
	}else{
		dsu.cnt0[0]=0;
		dsu.cnt0[1]=n-1;
	}
	for(ll i=1;i<n;i++){
		if(s[i]=='0'){
			dsu.cnt0[2*i]=i;
			dsu.cnt0[2*i+1]=n-i-1;
			if(s[i-1]=='0'){
				dsu.join(2*i,2*(i-1));
				dsu.join(2*i+1,2*(i-1)+1);
			}else{
				dsu.join(2*i,2*(i-1));
			}
		}else{
			dsu.cnt0[2*i]=1;
			dsu.cnt0[2*i+1]=0;
			if(s[i-1]=='0'){
				dsu.join(2*i,2*(i-1)+1);
			}else{
				//do nothing
			}
		}
	}
	ll ans=0;
	for(ll i=0;i<n;i++){
		ans=max({ans,dsu.cnt0[2*i],dsu.cnt0[2*i+1]});
	} 
	cout<<ans<<endl;
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
