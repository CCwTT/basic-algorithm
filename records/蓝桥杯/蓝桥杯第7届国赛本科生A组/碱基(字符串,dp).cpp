//https://www.lanqiao.cn/problems/117/learning/?isWithAnswer=true
//@@@
//string,dp
//let's emphasize:map<string,ll> map<vector<ll>,ll> map<pair<ll,ll>,ll>
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;
const ll mod=1e9+7;

void solve(){
    ll n,m,k;
    cin>>n>>m>>k;
    vector<string> ss(n+1);
    vector<map<string,ll>> mp(n+1);
    set<string> st;//统计
    for(ll i=1;i<=n;i++) cin>>ss[i];
    for(ll i=1;i<=n;i++){
        for(ll j=0;j<=ss[i].size()-k;j++){
            string s=ss[i].substr(j,k);
            mp[i][s]++;
            st.insert(s);
        }
    }
    ll ans=0;
    for(string s:st){
        vector<vector<ll>> f(n+1,vector<ll>(m+1));
        for(ll i=0;i<=n;i++){
            f[i][0]=1;
        }
        for(ll i=1;i<=n;i++){
            for(ll j=1;j<=m;j++){
                f[i][j]=(f[i-1][j]+f[i-1][j-1]*mp[i][s])%mod;
            }
        }
        ans=(ans+f[n][m])%mod;
    }
    cout<<ans%mod<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}