//https://www.lanqiao.cn/problems/231/learning/?isWithAnswer=true
//@@@
//dp(Joseph)
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
    ll n,k;
    cin>>n>>k;
    ll f=0;
    for(ll i=2;i<=n;i++){
      f=(f+k)%i;
    }
    cout<<f+1<<endl;
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
