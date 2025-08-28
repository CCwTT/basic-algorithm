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

void Log(vector<vector<ll>>& a){
	ll m=a.size(),n=a[0].size();
	cout<<"    ";
	for(ll j=0;j<n;j++){
		cout<<setw(4)<<j;
	}
	cout<<endl;
	for(ll i=0;i<m;i++){
		cout<<"i:"<<i<<" ";
		for(ll j=0;j<n;j++){
			cout<<setw(4)<<(a[i][j]<LLONG_MIN/2||a[i][j]>LLONG_MAX/2?-1:a[i][j]);
		}
		cout<<endl;
	}
	cout<<endl;
}

const ll mod=LLONG_MAX;
ll qpow(ll x,ll n){
	if(x==0) return 0;
	ll res=1;
	while(n){
		if(n&1) res=res*x%mod;
		n>>=1;
		x=x*x%mod;
	}
	return res;
}

const ll p=19937;

string fan(string t){
	string res;
	for(auto c:t){
		res+=1-(c-'0')+'0';
	}
	return res;
}

char fan(char c){
	return 1-(c-'0')+'0';
}

void solve(){
	string s;
	cin>>s;
	string rs=fan(s);
	ll n=s.size();
	vector<vector<ll>> hash(n,vector<ll>(n));
	for(ll i=0;i<n;i++){
		for(ll j=i;j<n;j++){
			hash[i][j]=qpow(p,j-i)*(s[j]-'0')+(j>i?hash[i][j-1]:0);
		}
	} 
	
	vector<vector<ll>> hash1(n,vector<ll>(n));
	for(ll i=0;i<n;i++){
		for(ll j=i;j<n;j++){
			hash1[i][j]=qpow(p,j-i)*(rs[j]-'0')+(j>i?hash1[i][j-1]:0);
		}
	} 
	
	
	ll ans=0;
	for(ll len=1;len<=n;len++){
		unordered_map<ll,ll> mp;
		for(ll i=0;i+len<=n;i++){
			ll x=i,y=i+len-1;
			if(i-len>=0){
				mp[hash[i-len][i-1]]++;
			}
			ans+=mp[hash1[x][y]];
		}
	}
	cout<<ans<<endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	ll T=1;
	while(T--){
		solve();
	}
	return 0;
} 
