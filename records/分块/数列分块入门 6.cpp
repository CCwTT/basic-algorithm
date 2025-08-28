//https://loj.ac/p/6282
//@@@
//block algorithm(periodic reconstruction)
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

const ll MAXN=2000005;
const ll MAXB=2000;
ll sz[MAXB];
vector<ll> vec[MAXB];
ll a[MAXN];
ll bel[MAXN];
ll n,m,len,nb;

ll lend(ll X){
    return (X-1)*len+1;
}

ll rend(ll X){
    return min(n,X*len);
}

void solve(){
    cin>>n;
    m=n;
    len=sqrt(n);
    nb=(n+len-1)/len;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        bel[i]=(i-1)/len+1;
        sz[bel[i]]++;
        vec[bel[i]].push_back(a[i]);
    }
    for(ll i=1;i<=m;i++){
        ll op,l,r,x;
        cin>>op>>l>>r>>x;
        if(op==0){
            ll pos=l;
            ll p=1;
            while(p<=nb&&pos>vec[p].size()){
                pos-=vec[p].size();
                p++;
            }
            if(p==nb+1) assert(0);
            vec[p].insert(vec[p].begin()+pos-1,r);
        }else{
            ll pos=r;
            ll p=1;
            while(p<=nb&&pos>vec[p].size()){
                pos-=vec[p].size();
                p++;
            }
            if(p==nb+1) assert(0);
            cout<<vec[p][pos-1]<<endl;
        }
        //periodic reconstruction
        if(i%(ll)sqrt(m)==0){
            vector<ll> tmp={-1};
            for(ll b=1;b<=nb;b++){
                tmp.insert(tmp.end(),vec[b].begin(),vec[b].end());
                vec[b].clear();
                sz[b]=0;
            }
            n=tmp.size()-1;
            len=(ll)sqrt(n);
            nb=(n+len-1)/len;
            for(ll i=1;i<=n;i++){
                bel[i]=(i-1)/len+1;
                sz[bel[i]]++;
                vec[bel[i]].push_back(tmp[i]);
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
