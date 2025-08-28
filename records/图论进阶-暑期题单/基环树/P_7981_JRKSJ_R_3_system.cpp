//https://www.luogu.com.cn/problem/P7981
//@@@
//functional graph
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=5e5+5;
ll n,K;

struct functional_graph{
    ll f[N],rf[N];
    vector<ll> g[N],rg[N];
    bool onc[N]; ll bel[N],cdis[N],sc[N];
    ll dep[N],entry[N];
    bool vis[N];
    //onc
    void dfs1(ll x,ll rt){
        vis[x]=true;
        for(auto y:rg[x]){
            if(!vis[y]){
                dfs1(y,rt);
                onc[x]|=onc[y];
            }else if(y==rt){
                onc[x]=true;
            }
        }
    }
    
    //bel,cdis,sc,rf
    void dfs2(ll x,ll rt){
        bel[x]=rt;
        sc[rt]++;
        ll y=f[x];
        rf[y]=x;
        if(y!=rt){
            cdis[y]=cdis[x]+1;
            dfs2(y,rt);
        }
        sc[x]=sc[rt];
    }
    
    //dep,entry
    void dfs3(ll x,ll fa,ll rt){
        dep[x]=dep[fa]+1;
        entry[x]=rt;
        for(auto y:rg[x]){
            if(!bel[y]){
                dfs3(y,x,rt);
            }
        }
    }

    void build(){
        for(ll i=1;i<=n;i++){
            g[i].push_back(f[i]);
            rg[f[i]].push_back(i);
        }
        for(ll i=1;i<=n;i++){
            if(!vis[i]){
                dfs1(i,i);
            }
        }
        for(ll i=1;i<=n;i++){
            if(onc[i]&&!bel[i]){
                dfs2(i,i);
            }
        }
        for(ll i=1;i<=n;i++){
            if(onc[i]){
                for(auto j:rg[i]){
                    if(!bel[j]){
                        dfs3(j,i,i);
                    }else{
                        entry[j]=j;
                    }
                }
            }
        }
    }
}fg;

ll a[N],b[N];
ll tmp[N];

void bf(){
    for(ll i=1;i<=n;i++){
        b[i]=a[a[i]];
    }
    for(ll i=1;i<=n;i++){
        a[i]=b[i];
    }
    return;
}

ll qpow(ll x,ll n,ll mod){
    ll res=1;
    while(n){
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}

void solve(){
    cin>>n>>K;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    for(ll i=1;i<=18;i++){
        bf();
        if(--K==0){
            for(ll i=1;i<=n;i++){
                cout<<a[i]<<" ";
            }
            cout<<endl;
            return;
        }
    }
    for(ll i=1;i<=n;i++){
        fg.f[i]=a[i];
    }
    fg.build();

    for(ll i=1;i<=n;i++) if(fg.bel[i]==i){
        ll times=qpow(2,K,fg.sc[i]);
        ll p=i;
        ll q=i;
        for(ll j=1;j<=times;j++){
            q=fg.f[q];
        }
        for(ll j=1;j<=fg.sc[i];j++){
            tmp[p]=q;
            p=fg.f[p];
            q=fg.f[q];
        }
    }
    for(ll i=1;i<=n;i++){
        cout<<fg.rf[tmp[fg.f[i]]]<<" ";
    }
    cout<<endl;
}

signed main(){
    // freopen("out1.txt","wb",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    // cin>>T;
    while(T--){
        solve();
    }
    return 0;
}