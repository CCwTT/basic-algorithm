#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//@@@
string getMin(string s){
	ll n=s.size();
	s=s+s;
	ll i=0,j=1;
	while(j<n){
		ll k=0;
		while(k<n&&s[i+k]==s[j+k]) k++;
		if(s[i+k]>s[j+k]) i+=k+1;
		else j+=k+1;
		if(i==j) j++;
		if(i>j) swap(i,j);
	}
	return s.substr(i,n);
}


const ll p=19937;
ll qpow(ll x,ll n){
	if(x==0) return 0;
	ll res=1;
	while(n){
		if(n&1) res*=x;
		n>>=1;
		x*=x;
	}
	return res;
}

//https://vjudge.net/contest/714395#problem/L
//@@@
//0-indexed
vector<ll> get_h(string s){
	ll n=s.size();
	vector<ll> h(n);
	h[0]=s[0];
	for(ll i=1;i<n;i++){
		h[i]=h[i-1]*p+s[i];
	}
	return h;
}

//https://vjudge.net/contest/714395#problem/L 
//@@@
//0-indexed
ll get(vector<ll>& h,ll l,ll r){
	if(l==0) return h[r];
	return h[r]-h[l-1]*qpow(p,r-l+1);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    string s="hdflankval";
	cout<<getMin(s)<<endl;
    return 0;
}


vector<ll> get_h(string s){
	ll n=s.size();
	vector<ll> h(n);
	h[0]=s[0];
	for(ll i=1;i<n;i++){
		h[i]=h[i-1]*p+s[i];
	}
	return h;
}

ll get(vector<ll>& h,ll l,ll r){
	if(l==0) return h[r];
	return h[r]-h[l-1]*qpow(p,r-l+1);
}