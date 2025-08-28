//https://atcoder.jp/contests/dp/tasks/dp_t
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

const ll mod=1e9+7;

void solve(){
    ll n;
    string s;
    cin>>n>>s;
    s="  "+s;
    vector<vector<ll>> f(n+1,vector<ll>(n+1));
    vector<ll> sum(n+1);
    f[1][1]=sum[1]=1;
    for(ll i=2;i<=n;i++){
        for(ll j=1;j<=i;j++){
            if(s[i]=='<'){
                f[i][j]=sum[j-1];
                // for(ll k=1;k<j;k++){
                //     f[i][j]=(f[i][j]+f[i-1][k])%mod;
                // }
            }else{
                f[i][j]=(sum[i-1]-sum[j-1]+mod)%mod;
                // for(ll k=j;k<=i-1;k++){
                //     f[i][j]=(f[i][j]+f[i-1][k])%mod;
                // }
            }
        }
        for(ll j=1;j<=n;j++){
            sum[j]=(sum[j-1]+f[i][j])%mod;
        }
    }
    ll ans=0;
    for(ll i=1;i<=n;i++){
        ans=(ans+f[n][i])%mod;
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
