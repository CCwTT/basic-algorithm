//https://loj.ac/p/6278
//@@@
//block algorithm
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

const ll MAXN=50005;
const ll MAXT=300;
ll add[MAXT];
vector<ll> vec[MAXT];
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
        bel[i]=(i-1)/len+1;
        cin>>a[i];
        vec[bel[i]].push_back(a[i]);
        if(i==rend(bel[i])){
            sort(vec[bel[i]].begin(),vec[bel[i]].end());
        }
    }
    for(ll i=1;i<=n;i++){
        ll op,l,r,x;
        cin>>op>>l>>r>>x;
        if(op==0){
            if(bel[l]==bel[r]){
                for(ll j=l;j<=r;j++){
                    a[j]+=x;
                }
                vec[bel[l]].assign(a+lend(bel[l]),a+rend(bel[l])+1);
                sort(vec[bel[l]].begin(),vec[bel[l]].end());
            }else{
                ll L=bel[(l+len-2)/len*len+1];
                ll R=bel[r/len*len];
                for(ll j=L;j<=R;j++){
                    add[j]+=x;
                }
                for(ll j=l;j<lend(L);j++){
                    a[j]+=x;
                }
                vec[bel[l]].assign(a+lend(bel[l]),a+rend(bel[l])+1);
                sort(vec[bel[l]].begin(),vec[bel[l]].end());
                for(ll j=rend(R)+1;j<=r;j++){
                    a[j]+=x;
                }
                vec[bel[r]].assign(a+lend(bel[r]),a+rend(bel[r])+1);
                sort(vec[bel[r]].begin(),vec[bel[r]].end());
            }
        }else{
            if(bel[l]==bel[r]){
                ll ans=0;
                for(ll i=l;i<=r;i++){
                    ans+=(a[i]+add[bel[i]])<x*x;
                }
                cout<<ans<<endl;
            }else{
                ll ans=0;
                ll L=bel[(l+len-2)/len*len+1];
                ll R=bel[r/len*len];
                for(ll j=l;j<lend(L);j++){
                    ans+=(a[j]+add[bel[j]])<x*x;
                }
                for(ll j=r;j>rend(R);j--){
                    ans+=(a[j]+add[bel[j]])<x*x;
                }
                for(ll j=L;j<=R;j++){
                    ans+=lower_bound(vec[j].begin(),vec[j].end(),x*x-add[j])-vec[j].begin();
                }
                cout<<ans<<endl;
            }
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
