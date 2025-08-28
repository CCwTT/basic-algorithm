#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
#define EPS (1e-20)
typedef long long ll;
typedef __int128 i128;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

constexpr ll N=410,M=200;
ll n,m;
ll a[N],b[N],dp[N][2];

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
      cin>>a[i];  
    }
    a[0]=a[n+1]=0;
    if(m==1){
        ll mx=*max_element(a+1,a+n+1);
        for(ll i=1;i<=n;i++){
            a[i]=mx-a[i];
        } 
        ll ans=0;
        for(ll i=1;i<=n+1;i++){
            ans+=abs(a[i]-a[i-1]);
        }
        cout<<ans/2<<endl;
        return;
    }
    ll ans=INF;
    for(ll y=*max_element(a+1,a+n+1);y<=M;y++)
        for(ll x=1;x<=y;x++){
            memset(dp,0x3f,sizeof(dp));
            if(x>=a[1]) dp[1][0]=x-a[1];
            if(y>=a[1]) dp[1][1]=y-a[1];
            for(ll i=2;i<=n;i++){
                if(x>=a[i]) dp[i][0]=min(
                    dp[i-1][0]+abs((x-a[i])-(x-a[i-1])),
                    dp[i-1][1]+abs((x-a[i])-(y-a[i-1]))
                );
                if(y>=a[i]) dp[i][1]=min(
                    dp[i-1][0]+abs((y-a[i])-(x-a[i-1])),
                    dp[i-1][1]+abs((y-a[i])-(y-a[i-1]))
                );
            }
            chmin(ans,dp[n][0]+(x-a[n]));
            chmin(ans,dp[n][1]+(y-a[n]));
        }
    cout<<ans/2<<endl;
}

void clear(){}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
        clear();
    }
    return 0;
}