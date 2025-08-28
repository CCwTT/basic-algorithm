//https://acm.hdu.edu.cn/contest/status?cid=1180&rid=13724
//@@@
//palindrome brute force
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

ll n,res;
string s;
bool vis[100010];
bool check(ll l,ll r){
	for(ll i=l;i<r;i++) if(s[i]=='('&&s[i+1]==')')return 1;
	return 0;
}

void solve(){
	string s;
    cin>>s;
    n=s.size();
    s=" "+s;
	for(ll i=1;i<n;i++){
        if(s[i]=='('&&s[i+1]==')'){
            vis[i]=true;
        }
    }
	for(ll i=1;i<=n;i++){ 
		bool ok=0;ll x=1;
		while(i-x>=1&&i+x<=n){
			if(s[i-x]!=s[i+x]) break;
			ok|=vis[i-x]|vis[i+x-1];
			res+=ok;
			x++;
		}
	}
    for(ll i=1;i<n;i++) if(s[i]==s[i+1]){
		bool ok=0;ll x=1;
		while(i-x>=1&&i+1+x<=n){
			if(s[i-x]!=s[i+1+x]) break;
			ok|=vis[i-x]|vis[i+x];
			res+=ok;
			x++;
		}
	}
	cout<<res<<endl;
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