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
    vector<ll> s(lim);
    for(ll i=0;i<lim;i++){
        s[i]=(i==0?0:s[i-1])+(__gcd((i+1)*x^x,x)==1);
    }
    while(n--){
        ll l,r;
        cin>>l>>r;
        l--,r--;
            ll ans=s[lim-1]*((r/lim)-(l/lim)-1);
            l%=lim;
            r%=lim;
            ans+=s[lim-1]-(l==0?0:s[l-1])+s[r];
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