//https://ac.nowcoder.com/acm/contest/108304/C
//@@@
//greedy
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
    ll ans=0;
    for(ll i=n-1;i;i--){
        ans=max(ans,a[i]-a[i+1]);
        a[i]=min(a[i],a[i+1]);
    }
    cout<<ans<<endl;
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