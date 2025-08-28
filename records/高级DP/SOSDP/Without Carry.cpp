//https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1010
//@@@
//SOSDP
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll MAXN=2e6+5;
ll n;
ll a[MAXN];
constexpr ll pw[]={1,10,100,1000,10000,100000,1000000};
ll f[MAXN];

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        f[a[i]]++;
    }
    for(ll d=0;d<6;d++){
        for(ll mask=0;mask<pw[6];mask++){
            if(mask/pw[d]%pw[1]){
                f[mask]+=f[mask-pw[d]];
            }
        }
    }
    ll ans=0;
    for(ll i=1;i<=n;i++){
        ans+=f[pw[6]-1-a[i]];
        bool flag=false;
        for(ll d=0;d<6;d++){
            if(a[i]/pw[d]%pw[1]>=5){
                flag=true;
                break;
            }
        }
        ans-=(!flag);
    }
    cout<<(ans>>1)<<endl;
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