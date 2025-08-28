//https://loj.ac/p/6281
//@@@
//block algorithm
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

const ll MAXN=50005;
const ll MAXB=300;
ll sum[MAXB];
bool tag[MAXB];
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
        ll L=bel[l]!=bel[l-1]?bel[l]:bel[l]+1;
        ll R=bel[r]!=bel[r+1]?bel[r]:bel[r]-1;
        if(op==0){
            if(bel[l]==bel[r]){
                for(ll i=l;i<=r;i++){
                    sum[bel[i]]+=-a[i]+(ll)sqrt(a[i]);
                    a[i]=(ll)sqrt(a[i]);
                }
            }else{
                for(ll j=L;j<=R;j++){
                    if(tag[j]){
                        continue;
                    }
                    bool flag=true;
                    for(ll k=lend(j);k<=rend(j);k++){
                        sum[bel[k]]+=-a[k]+(ll)sqrt(a[k]);
                        a[k]=(ll)sqrt(a[k]);
                        if(a[k]>1) flag=false;
                    }
                    tag[j]=flag;
                }
                for(ll j=l;j<lend(L);j++){
                    sum[bel[j]]+=-a[j]+(ll)sqrt(a[j]);
                    a[j]=(ll)sqrt(a[j]);
                }
                for(ll j=rend(R)+1;j<=r;j++){
                    sum[bel[j]]+=-a[j]+(ll)sqrt(a[j]);
                    a[j]=(ll)sqrt(a[j]);
                }
            }
        }else{
            ll ans=0;
            if(bel[l]==bel[r]){
                for(ll j=l;j<=r;j++){
                    ans+=a[j];
                }
            }else{
                for(ll j=l;j<lend(L);j++){
                    ans+=a[j];
                }
                for(ll j=r;j>rend(R);j--){
                    ans+=a[j];
                }
                for(ll j=L;j<=R;j++){
                    ans+=sum[j];
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
