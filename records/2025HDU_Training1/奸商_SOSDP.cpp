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
    vector<short> ok(1<<17,true);
    for(ll i=1,j=i+L-1;j<=n;i++,j++){
        ll mask=0;
        for(ll k=i;k<=(i+j)/2;k++){
            if(s[k]!=s[i+j-k]){
                ll mn=min(s[k]-'a',s[i+j-k]-'a');
                mask|=1<<mn;
            }else{
                mask=0;
                break;
            }
        }
        if(mask) ok[mask]=false;
    }
    for(ll d=0;d<17;d++){
        for(ll mask=0;mask<1<<17;mask++){
            if(mask>>d&1){
                ok[mask]&=ok[mask^1<<d];
            }
        }
    }
    ll ans=inf;
    for(ll mask=0;mask<1<<17;mask++){
        if(ok[mask]){
            ll cur=0;
            for(ll d=0;d<17;d++){
                if(~mask&1<<d){
                    cur+=cost[d];
                }
            }
            ans=min(ans,cur);
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