//https://atcoder.jp/contests/abc399/editorial/12580
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Dsu{
	public:
		vector<ll> f;
		Dsu(ll n):f(n){
			iota(f.begin(),f.end(),0);
		}
		ll find(ll x){
			return f[x]==x?x:f[x]=find(f[x]);
		}
		bool check(ll x,ll y){
			return find(x)==find(y);
		}
		void join(ll x,ll y){
			if(!check(x,y)) f[find(y)]=find(x);
		}
	};

void solve(){
	ll n;
	cin>>n;
	string s,t;
	cin>>s>>t;
	if(s==t){
		cout<<0<<endl;
		return;
	}
	vector<ll> f(26,-1);
	for(ll i=0;i<n;i++){
		ll sc=s[i]-'a';
		ll tc=t[i]-'a';
		if(f[sc]!=-1&&f[sc]!=tc){
			cout<<-1<<endl;
			return;
		}
		f[sc]=tc;
	}
	bool is_perm=true;
	auto tmp=f;
	sort(tmp.begin(),tmp.end());
	for(ll i=0;i<26;i++){
		is_perm&=tmp[i]==i;
	}
	if(is_perm){
		cout<<-1<<endl;
		return;
	}
	ll ans=0;

	Dsu dsu(26);
	vector<ll> in(26);
	for(ll i=0;i<26;i++){
		if(~f[i]){
			if(f[i]!=i){
				ans++;
			}
			in[f[i]]++;
			dsu.join(i,f[i]);
		}
	}

	unordered_map<ll,vector<ll>> groups;
	for(ll i=0;i<26;i++){
		groups[dsu.find(i)].push_back(i);
	}
	for(auto& [_,grp]:groups){
		bool is_cycle=true;
		for(ll& i:grp){
			is_cycle&=in[i]==1;
		}
		if(is_cycle&&grp.size()>1){
			ans++;
		}
	}
	cout<<ans<<endl;
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
