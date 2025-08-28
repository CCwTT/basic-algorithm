//https://ac.nowcoder.com/acm/contest/108304/D
//@@@
//dp on graph
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

void solve(){
    cout<<fixed<<setprecision(15);
    ll n,m;
    cin>>n>>m;
    vector reach(n,vector<ll>(n));
    vector<al3> edges(m);
    ll mxw=0;
    for(auto& [u,v,w]:edges){
        cin>>u>>v>>w;
        u--,v--;
        reach[u][v]=1;
        chmax(mxw,w);
    }
    for(ll k=0;k<n;k++){
        for(ll i=0;i<n;i++){
            for(ll j=0;j<n;j++){
                reach[i][j]|=reach[i][k]&reach[k][j];
            }
        }
    }
    vector dp(n,vector(n,vector<ll>(mxw*n+1,INF)));
    for(ll i=0;i<n;i++){
        dp[i][i][0]=0;
    }
    ld ans=INF;
    for(ll len=1;len<=n;len++){
        vector ndp(n,vector(n,vector<ll>(mxw*n+1,INF)));
        for(ll i=0;i<n;i++){
            for(auto [u,v,w]:edges){
                for(ll sw=0;sw<=mxw*(len-1);sw++){
                    chmin(ndp[i][v][sw+w],dp[i][u][sw]+w*w);
                }
            }
        }
        dp=move(ndp);
        for(ll sw=0;sw<=mxw*len;sw++){
            if(dp[0][n-1][sw]!=INF){
                chmin(ans,((ld)dp[0][n-1][sw]/len)-((ld)sw/len)*((ld)sw/len));
            }
        }
        for(ll i=0;i<n;i++){
            for(ll sw=0;sw<=mxw*len;sw++){
                if(dp[i][i][sw]!=INF&&reach[0][i]&&reach[i][n-1]){
                    chmin(ans,((ld)dp[i][i][sw]/len)-((ld)sw/len)*((ld)sw/len));
                }
            }
        }
    }
    cout<<(ans==INF?-1:ans)<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
    }
    return 0;
}