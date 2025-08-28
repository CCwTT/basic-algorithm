//https://www.lanqiao.cn/problems/1564/learning/
//@@@
//state compression,dp
//link:records\ABC\ABC407\DominoCoveringXOR(状压DP).cpp
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

void Log(vector<ll>& a){
	ll n=a.size();
	for(ll i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

void solve(){
	ll n=8;
    //pre-calculation
	vector<bool> pre(1ll<<n,true);
	for(ll mask=0;mask<(1ll<<n);mask++){
		ll cnt0=0;
		for(ll d=0;d<n;d++){
			if(~mask&1ll<<d){
				cnt0++;
			}else{
				if(cnt0&1){
					pre[mask]=false;
					break;
				}
			}
		}
		if(cnt0&1){
			pre[mask]=false;
		}
	} 
	vector<vector<ll>> f(n+1,vector<ll>(1ll<<n,0));
	f[0][0]=1;
	for(ll i=1;i<=n;i++){
		for(ll mask=0;mask<(1ll<<n);mask++){
			for(ll pmask=0;pmask<(1ll<<n);pmask++){
				if(!(mask&pmask)&&pre[mask|pmask]){
					f[i][mask]+=f[i-1][pmask];
				}
			}
		}
	}
	cout<<f[n][0]<<endl;
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