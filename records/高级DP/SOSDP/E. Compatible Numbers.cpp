//https://codeforces.com/problemset/problem/165/E
//@@@
//SOSDP,prefix sum
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll MAXN=5e6+5;
ll n;
ll a[MAXN],f[MAXN];

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        f[a[i]]=a[i];
    }
    ll U=(1ll<<22)-1;
    for(ll d=0;d<22;d++){
        for(ll mask=0;mask<(1<<22);mask++){
            if(mask>>d&1){
                if(f[mask^(1<<d)]){
                    f[mask]=f[mask^(1<<d)];
                }
            }
        }
    }
    for(ll i=1;i<=n;i++){
        if(f[U^a[i]]){
            cout<<f[U^a[i]]<<" ";
        }else{
            cout<<-1<<" ";
        }
    }
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