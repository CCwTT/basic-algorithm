//https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1010
//@@@
//SOSDP,prefix sum
//[model]:using SOSDP to solve two-dimensional prefix sum
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll MAXN=1005;
ll n,m;
ll a[MAXN][MAXN];
ll f[MAXN*MAXN];
ll pw[3];

void solve(){
    cin>>n>>m;
    pw[0]=1;pw[1]=m;pw[2]=m*n;
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=m;j++){
            cin>>a[i][j];
            f[(i-1)*pw[1]+j-1]=a[i][j];
        }
    }
    for(ll d=0;d<2;d++){
        for(ll mask=0;mask<pw[2];mask++){
            if(mask/pw[d]%pw[1]){
                f[mask]+=f[mask-pw[d]];
            }
        }
    }
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=m;j++){
            cout<<f[(i-1)*pw[1]+j-1]<<" ";
        }
        cout<<endl;
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