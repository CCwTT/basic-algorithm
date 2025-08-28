#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//不难发现或通过打表后发现:(x+(a<<大))^y=(x^y)+(a<<大)，
//所以gcd((k+(1<<大))*x^x,x)=gcd((kx+(1<<大)*x)^x,x)=gcd((kx+(x<<大))^x,x)=gcd(kx^x+(x<<大),x)=gcd(kx^x,x)
//所以只要打1~(1<<大)的表即可
//利用前缀和求区间和的思想求区间值

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
        l--;
        ll ans1=s[lim]*(r/lim)+s[r%lim];
        ll ans2=s[lim]*(l/lim)+s[l%lim];
        cout<<ans1-ans2<<endl;
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