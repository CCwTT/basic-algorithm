#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=2e5+5;
ll n,a[N];

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    if(n<=2){
        cout<<0<<endl;
        return;
    }
    ll mx=*max_element(a+1,a+n+1);
    ll ans=mx*(n-3);
    ans+=max(a[1],a[n]);
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