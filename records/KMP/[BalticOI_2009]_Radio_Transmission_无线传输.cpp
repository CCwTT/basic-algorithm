//https://www.luogu.com.cn/record/217735995
//@@@
//next array
//perception:So many times we say we use kmp,manacher... what we actually need is nothing but the next array,the p array,the z array etc. 
//And during the process of calculating the next array,the p array,the z array etc,we refers to the idea of kmp and manacher.
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

void Log(vector<ll>& a){
	ll n=a.size();
	for(ll i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

vector<ll> get_next(string s){
  ll n=s.size();
  vector<ll> next(n+1);
  next[0]=-1;
  next[1]=0;
  ll i=2,j=0;
  while(i<=n){
    if(s[i-1]==s[j]){
      next[i++]=++j;
    }else if(j){
      j=next[j];
    }else{
      next[i++]=0;
    }
  }
  return next;
}

void solve(){
  ll n;
  string s;
  cin>>n>>s;
  auto next=get_next(s);
  cout<<n-next[n]<<endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}
