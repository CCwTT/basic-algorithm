#include <bits/stdc++.h>
using namespace std;
//#define endl '\n
#define inf LLONG_MAX/2
typedef long long ll;

void solve(){
    ll x,y;
    cin>>x>>y;
    if(x>y) swap(x,y);
    if(x>1){
        cout<<1<<endl;
        return;
    }
    cout<<-1<<endl;
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