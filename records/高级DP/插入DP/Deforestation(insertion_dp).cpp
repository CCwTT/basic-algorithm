//https://atcoder.jp/contests/abc209/tasks/abc209_f
//@@@
//insertion dp
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

const ll mod=1e9+7;

void solve(){
    ll n;
    cin>>n;
    vector<ll> a(n+1);
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    vector<vector<ll>> f(n+1,vector<ll>(n+1));
    vector<ll> s(n+1);
    f[1][1]=1;
    s[1]=1;
    for(ll i=2;i<=n;i++){
        for(ll j=1;j<=i;j++){
            if(a[i]==a[i-1]){
                f[i][j]=s[i-1];
                // for(ll k=1;k<=i-1;k++){
                //     f[i][j]=(f[i][j]+f[i-1][k])%mod;
                // }
            }else if(a[i]<a[i-1]){
                f[i][j]=s[j-1];
                // for(ll k=1;k<=j-1;k++){
                //     f[i][j]=(f[i][j]+f[i-1][k])%mod;
                // }
            }else{
                f[i][j]=(s[i-1]-s[j-1]+mod)%mod;
                // for(ll k=j;k<=i-1;k++){
                //     f[i][j]=(f[i][j]+f[i-1][k])%mod;
                // }
            }
        }
        for(ll j=1;j<=n;j++){
            s[j]=(s[j-1]+f[i][j])%mod;
        }
    }
    ll ans=0;
    for(ll j=1;j<=n;j++){
        ans=(ans+f[n][j])%mod;
    }
    cout<<ans<<endl;
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
