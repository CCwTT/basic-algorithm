//https://acm.hdu.edu.cn/contest/problem?cid=1177&pid=1008
//@@@
//mask dp(subset dp)
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

ll val[1<<13],cval[1<<13],dp[14][1<<13],a[13];
ll n,m,k;

void solve(){
    cin>>n>>m>>k;
    k=min(k,m);
    for(ll i=0;i<1<<m;i++){
        val[i]=0;
    }
    for(ll j=0;j<n;j++){
        for(ll i=0;i<m;i++){
            cin>>a[i];
        }
        for(ll mask=1;mask<1<<m;mask++){
            cval[mask]=cval[mask&(mask-1)]+a[__builtin_ctzll(mask)];
            val[mask]=max(val[mask],cval[mask]);
        }
    }
    for(ll i=0;i<=k;i++){
        for(ll mask=0;mask<1<<m;mask++){
            dp[i][mask]=0;
        }
    }

    ll U=(1<<m)-1;
    //写法1(刷表)：
    // for(ll i=0;i<k;i++){
    //     for(ll cur=0;cur<1<<m;cur++){
    //         for(ll add=U^cur;add;add=(add-1)&(U^cur)){
    //             dp[i+1][cur|add]=max(dp[i+1][cur|add],dp[i][cur]+val[add]);
    //         }
    //     }
    // }
    //写法2(填表):
    for(ll i=1;i<=k;i++){
        for(ll cur=1;cur<1<<m;cur++){
            for(ll prev=(cur-1)&cur;;prev=(prev-1)&cur){
                dp[i][cur]=max(dp[i][cur],dp[i-1][prev]+val[cur^prev]);
                if(prev==0) break;
            }
        }
    }
    cout<<dp[k][U]<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}