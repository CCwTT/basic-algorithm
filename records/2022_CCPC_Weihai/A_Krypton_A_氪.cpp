#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll p[7]={1,6,28,88,198,328,648};
ll r[7]={8,18,28,58,128,198,388};
ll ans=0;

void solve(){
    ll n;
    cin>>n;
    for(ll mask=0;mask<(1ll<<7);mask++){
        ll sum=0;
        ll cur=0;
        for(ll i=0;i<7;i++){
            if(mask&(1ll<<i)){
                sum+=p[i];
                cur+=p[i]*10+r[i];
            }
        }
        if(sum>n) continue;
        ll rest=n-sum;
        cur+=rest*10;
        ans=max(ans,cur);
    }
    cout<<ans<<endl;
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