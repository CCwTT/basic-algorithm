//https://loj.ac/p/6280
//@@@
//block algorithm
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

const ll MAXN=50005;
const ll MAXT=300;
ll add[MAXT];
ll sum[MAXT];
ll a[MAXN];
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
        cin>>a[i];
        bel[i]=(i-1)/len+1;
        sum[bel[i]]+=a[i];
    }
    for(ll i=1;i<=n;i++){
        ll op,l,r,x;
        cin>>op>>l>>r>>x;
        if(op==0){
            if(bel[l]==bel[r]){
                for(ll i=l;i<=r;i++){
                    a[i]+=x;
                    sum[bel[i]]+=x;
                }
            }else{
                ll L=bel[(l+len-2)/len*len+1];
                ll R=bel[r/len*len];
                for(ll j=L;j<=R;j++){
                    add[j]+=x;
                    sum[j]+=x*len;
                }
                for(ll j=l;j<lend(L);j++){
                    a[j]+=x;
                    sum[bel[j]]+=x;
                }
                for(ll j=rend(R)+1;j<=r;j++){
                    a[j]+=x;
                    sum[bel[j]]+=x;
                }
            }
        }else{
            ll ans=0;
            ll mod=x+1;
            if(bel[l]==bel[r]){
                for(ll j=l;j<=r;j++){
                    ans=(ans+a[j]+add[bel[j]])%mod;
                }
            }else{
                ll L=bel[l]!=bel[l-1]?bel[l]:bel[l]+1;
                ll R=bel[r]!=bel[r+1]?bel[r]:bel[r]-1;
                for(ll j=l;j<lend(L);j++){
                    ans=(ans+a[j]+add[bel[j]])%mod;
                }
                for(ll j=r;j>rend(R);j--){
                    ans=(ans+a[j]+add[bel[j]])%mod;
                }
                for(ll j=L;j<=R;j++){
                    ans=(ans+sum[j])%mod;
                }
            }
            cout<<ans<<endl;
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
