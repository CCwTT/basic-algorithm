//https://atcoder.jp/contests/abc282/tasks/abc282_g
//@@@
//insertion dp,2-dim prefix-sum
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

ll mod;

void solve(){
    ll n,K;
    cin>>n>>K>>mod;
    vector<vector<vector<vector<ll>>>> f(n+1,vector<vector<vector<ll>>>(K+2,vector<vector<ll>>(n+1,vector<ll>(n+1))));
    f[2][1][1][1]=f[2][1][2][2]=1;
    f[2][0][1][2]=f[2][0][2][1]=1;
    vector<vector<vector<ll>>> sum(K+1,vector<vector<ll>>(n+1,vector<ll>(n+1)));

    auto get=[&](ll t,ll x1,ll y1,ll x2,ll y2)->ll{
        if(!(x1<=x2&&y1<=y2)) return 0;
        return (sum[t][x2][y2]-sum[t][x1-1][y2]-sum[t][x2][y1-1]+sum[t][x1-1][y1-1]+2*mod)%mod;
    };

    for(ll i=3;i<=n;i++){

        for(ll t=0;t<=K;t++){
            for(ll j1=1;j1<=i-1;j1++){
                for(ll j2=1;j2<=i-1;j2++){
                    sum[t][j1][j2]=(sum[t][j1-1][j2]+sum[t][j1][j2-1]-sum[t][j1-1][j2-1]+f[i-1][t][j1][j2]+mod)%mod;
                }
            }
        }

        for(ll t=0;t<=K;t++){
            for(ll j1=1;j1<=i;j1++){
                for(ll j2=1;j2<=i;j2++){
                    f[i][t][j1][j2]=(f[i][t][j1][j2]+get(t,1,j2,j1-1,i-1))%mod;
                    // for(ll k1=1;k1<j1;k1++){
                    //     for(ll k2=j2;k2<=i-1;k2++){
                    //         f[i][t][j1][j2]=(f[i][t][j1][j2]+f[i-1][t][k1][k2])%mod;
                    //     }
                    // }
                    f[i][t][j1][j2]=(f[i][t][j1][j2]+get(t,j1,1,i-1,j2-1))%mod;
                    // for(ll k1=j1;k1<=i-1;k1++){
                    //     for(ll k2=1;k2<j2;k2++){
                    //         f[i][t][j1][j2]=(f[i][t][j1][j2]+f[i-1][t][k1][k2])%mod;
                    //     }
                    // }
                    if(t){
                        f[i][t][j1][j2]=(f[i][t][j1][j2]+get(t-1,1,1,j1-1,j2-1))%mod;
                        // for(ll k1=1;k1<j1;k1++){
                        //     for(ll k2=1;k2<j2;k2++){
                        //         f[i][t][j1][j2]=(f[i][t][j1][j2]+f[i-1][t-1][k1][k2])%mod;
                        //     }
                        // }
                        f[i][t][j1][j2]=(f[i][t][j1][j2]+get(t-1,j1,j2,i-1,i-1))%mod;
                        // for(ll k1=j1;k1<=i-1;k1++){
                        //     for(ll k2=j2;k2<=i-1;k2++){
                        //         f[i][t][j1][j2]=(f[i][t][j1][j2]+f[i-1][t-1][k1][k2])%mod;
                        //     }
                        // }
                    }
                }
            }
        }
    }
    ll ans=0;
    for(ll j1=1;j1<=n;j1++){
        for(ll j2=1;j2<=n;j2++){
            ans=(ans+f[n][K][j1][j2])%mod;
        }
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
