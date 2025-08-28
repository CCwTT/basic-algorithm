#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll x,n;
ll lim;

void find_lim(){
    lim=1;
    while(lim<=x){
        lim<<=1;
    }
}

void solve(){
    cin>>x>>n;
    find_lim();
    vector<ll> s(lim+1);
    for(ll i=1;i<=lim;i++){
        s[i]=s[i-1]+(__gcd(i*x^x,x)==1);
    }
    while(n--){
        ll l,r;
        cin>>l>>r;
        ll ans=s[lim]*(((r-1)/lim)-((l-1)/lim)-1);
        l=(l-1)%lim+1;
        r=(r-1)%lim+1;
        ans+=(s[lim]-s[l-1])+s[r];
        cout<<ans<<endl;
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
}