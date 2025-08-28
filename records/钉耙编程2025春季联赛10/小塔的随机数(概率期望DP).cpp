//https://acm.hdu.edu.cn/contest/problem?cid=1159&pid=1004
//@@@
//probability dp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const ll mod=1e9+7;

inline ll qpow(ll x,ll n){
  ll res=1;
  while(n){
    if(n&1) res=res*x%mod;
    x=x*x%mod;
    n>>=1;
  }
  return res;
}

ll inv(ll x){
	return qpow(x,mod-2);
}

const ll inv2=inv(2);

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<vector<ll>> f(n+1,vector<ll>(n+1,0));
    for(ll i=1;i<=m;i++){
      ll l,r;
      cin>>l>>r;
      for(ll j=l;j<=r;j++){
        for(ll k=l;k<=r;k++){
          if(j!=k) f[j][k]=inv2;
		}
	  }
      for(ll j=1;j<=n;j++) if(j<l||j>r){
        ll cur=0;
        for(ll k=l;k<=r;k++){
          cur=(cur+f[j][k])%mod;
		}
        cur=cur*inv(r-l+1)%mod;
        for(ll k=l;k<=r;k++){
          f[j][k]=f[k][j]=cur;
		}
      }
    }
    ll sum=0;
    for(ll i=1;i<=n;i++){
      for(ll j=i+1;j<=n;j++){
        sum=(sum+f[i][j])%mod;
	  }
	}
    cout<<sum<<endl;
}

signed main(){
  ios::sync_with_stdio(false);
  cin.tie(0);cout.tie(0);
  ll T;
  cin>>T;
  while(T--){
    solve();
  }
  return 0;
}