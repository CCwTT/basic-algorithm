#include<bits/stdc++.h>
using namespace std;
//#define endl '\n
#define inf LLONG_MAX/2
typedef long long ll;

ll n;

void solve(){
    cin>>n;
    bool vis[65]={0};
    vector<ll> a(n);
    for(ll i=0;i<n;i++){
        cin>>a[i];
    }
    sort(a.rbegin(),a.rend());
    for(auto x:a){
        if(vis[__lg(x)]){
            cout<<"NO"<<endl;
            return;
        }
        for(ll d=63;d>=0;d--){
            if(x>>d&1){
                vis[d]=1;
            }
        }
    }
    cout<<"YES"<<endl;
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