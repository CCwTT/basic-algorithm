#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a,b,c;

ll f(ll npeople,ll nproblem){
    if(npeople>=nproblem){
        return b;
    }
    return min(a+f(npeople<<1,nproblem),(nproblem+npeople-1)/npeople*b);
}

void solve(){
    cin>>a>>b>>c;
    cout<<f(1,c)<<endl;
}

signed main(){
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}