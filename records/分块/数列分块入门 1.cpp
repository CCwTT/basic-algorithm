//https://loj.ac/p/6277
//@@@
//block algorithm
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

const ll MAXN=50005;
const ll MAXT=300;
ll add[MAXT];
ll val[MAXN];
ll bel[MAXN];
ll n,len;

ll lend(ll X){
    return (X-1)*len+1;
}

ll rend(ll X){
    return min(n,X*len);
}

void solve(){
    cin>>n;
    len=sqrt(n);
    for(ll i=1;i<=n;i++){
        bel[i]=(i-1)/len+1;
        cin>>val[i];
    }
    for(ll i=1;i<=n;i++){
        ll op,l,r,x;
        cin>>op>>l>>r>>x;
        if(op==0){
            if(bel[l]==bel[r]){
                for(ll i=l;i<=r;i++){
                    val[i]+=x;
                }
            }else{
                ll L=bel[(l+len-2)/len*len+1];
                ll R=bel[r/len*len];
                for(ll j=L;j<=R;j++){
                    add[j]+=x;
                }
                for(ll j=l;j<lend(L);j++){
                    val[j]+=x;
                }
                for(ll j=rend(R)+1;j<=r;j++){
                    val[j]+=x;
                }
            }
        }else{
            cout<<val[r]+add[bel[r]]<<endl;
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}
