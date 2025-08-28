//https://ac.nowcoder.com/acm/contest/108302/E
//@@@
//bit operation,math
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

void solve(){
    ll n;
    cin>>n;
    vector<ll> a(n+1);
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    vector<vector<ll>> b(n+1,vector<ll>(32));
    for(ll i=1;i<=n;i++){
        ll cnt1=0;
        for(ll d=0;d<32;d++){
            b[i][d]=(a[i]>>d&1)+cnt1*2;
            cnt1^=a[i]>>d&1;
        }
    }
    ll ans=0;
    for(ll d=0;d<32;d++){
        ll cnt0=0,cnt1=0,cnt2=0,cnt3=0;
        for(ll i=1;i<=n;i++){
            if(b[i][d]==0){
                ans+=cnt1<<d;
                cnt0++;
            }else if(b[i][d]==1){
                ans+=cnt0<<d;
                cnt1++;
            }else if(b[i][d]==2){
                ans+=cnt3<<d;
                cnt2++;
            }else{
                ans+=cnt2<<d;
                cnt3++;
            }
        }
    }
    cout<<ans<<endl;
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