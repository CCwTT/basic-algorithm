//https://ac.nowcoder.com/acm/contest/108307/E
//@@@
//difference,high-dimensional linear dp
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

const ll N=400+7,M=200+7;
ll n,m,k=200;
ll ans;
ll dp[N][M][2]; 

void solve(){
    cin>>n>>m;
    vector<ll> a(n+2);
    ll mx=0;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        chmax(mx,a[i]);
    }
    if(n==1){
        cout<<0<<endl;
        return;
    }
    if(m==1){
        ans=0;
        ll mx_diff=-1;
        for(ll i=1;i<=n;i++){
            chmax(mx_diff,mx-a[i]);
        }
        for(ll _=1;_<=mx_diff;_++){
            for(ll i=2;i<=n+1;i++){
                if(i==n+1||a[i]==mx){
                    ans+=(a[i-1]!=mx);
                }
            }
            for(ll i=1;i<=n;i++){
                a[i]=min(mx,a[i]+1);
            } 
        }
        cout<<ans<<endl;
    }else{
        ans=INF;
        for(ll i=n;i>=2;i--) a[i]=a[i]-a[i-1];
        for(ll d=0;d<M;d++){
            memset(dp,0x3f,sizeof(dp));
            for(ll j=0;j<M;j++) dp[1][j][0]=dp[1][j][1]=j;
            for(ll i=2;i<=n;i++){
                for(ll j=0;j<M;j++){
                    if(a[i]>0&&a[i]-j<=0){
                        chmin(dp[i][j-a[i]][0],dp[i-1][j][0]);
                        chmin(dp[i][j-a[i]][1],dp[i-1][j][1]);
                    }
                    if(a[i]<=0){
                        chmin(dp[i][j-a[i]][0],dp[i-1][j][0]-a[i]);
                        chmin(dp[i][j-a[i]][1],dp[i-1][j][1]-a[i]);
                    }
                    if(a[i]>d&&a[i]-j<=d){
                        chmin(dp[i][j-(a[i]-d)][0],dp[i-1][j][1]);
                    }
                    if(a[i]<=d){
                        chmin(dp[i][j-(a[i]-d)][0],dp[i-1][j][1]-(a[i]-d));
                    }
                    if(a[i]>-d&&a[i]-j<=-d){
                        chmin(dp[i][j-(a[i]+d)][1],dp[i-1][j][0]);
                    }
                    if(a[i]<=-d){
                        chmin(dp[i][j-(a[i]+d)][1],dp[i-1][j][0]-(a[i]+d));
                    }
                }
            }
            for(ll j=0;j<M;j++)
            chmin(ans,dp[n][j][0]),
            chmin(ans,dp[n][j][1]);
        }
        cout<<ans<<endl;
    }
    return;
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