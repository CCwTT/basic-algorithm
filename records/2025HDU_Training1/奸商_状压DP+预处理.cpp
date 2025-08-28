//https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1003
//@@@
//state compression dp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

void solve(){
    ll n,L;
    string s;
    cin>>n>>s;
    s=" "+s;
    vector<ll> cost(17);
    for(ll i=0;i<17;i++){
        cin>>cost[i];
    }
    cin>>L;
    if(L&1)L++;
    if(L>n){
        cout<<0<<endl;
        return;
    }
    vector<ll> sum_cost(1<<18,0);
    for(ll mask=1;mask<(1<<17);mask++){
        sum_cost[mask]=sum_cost[mask&(mask-1)]+cost[__builtin_ctzll(mask)];
    }
    vector<vector<bool>> valid(n+2,vector<bool>(n+2,false));
    for(ll len=1;len<=L;len++){
        for(ll i=1,j=i+len-1;j<=n;i++,j++){
            valid[i][j]=valid[i+1][j-1]|(s[i]==s[j]);
        }
    }
    vector<vector<ll>> opt(n+2,vector<ll>(n+2,0));
    for(ll len=1;len<=L;len++){
        for(ll i=1,j=i+len-1;j<=n;i++,j++){
            if(!valid[i][j]){
                opt[i][j]=opt[i+1][j-1]|(1<<(min(s[i]-'a',s[j]-'a')));
            }
        }
    }
    ll ans=inf;
    for(ll mask=0;mask<(1<<17);mask++){
        bool ok=true;
        for(ll i=1,j=i+L-1;j<=n;i++,j++){
            if(valid[i][j])continue;
            ll B=opt[i][j]&mask;
            if(B==0){
                ok=false;
                break;
            }
        }
        if(ok){
            ans=min(ans,sum_cost[mask]);
        }

    }
    cout<<ans<<endl;
}


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}