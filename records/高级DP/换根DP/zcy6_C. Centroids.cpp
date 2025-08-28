    //https://www.luogu.com.cn/problem/P3047
    //@@@
    //rerooting dp
    #include<bits/stdc++.h>
    using namespace std;
    #define endl '\n'
    #define inf (LLONG_MAX/2)
    typedef long long ll;
     
    const ll MAXN=4e5+5;
    ll n;
    vector<ll> g[MAXN];
     
    ll sz[MAXN];
    ll mxsub[MAXN];
    ll inner[MAXN],id[MAXN];
    ll inner2[MAXN];
    ll outer[MAXN];
    ll dp[MAXN];
     
    void dfs1(ll x,ll fa){
        sz[x]=1;
        for(auto y:g[x]) if(y!=fa){
            dfs1(y,x);
            sz[x]+=sz[y];
            if(sz[y]>sz[mxsub[x]]){
                mxsub[x]=y;
            }
            ll tmp=sz[y]<=n/2?sz[y]:inner[y];
            if(tmp>inner[x]){
                inner2[x]=inner[x];
                inner[x]=tmp,id[x]=y;
            }else if(tmp>inner2[x]){
                inner2[x]=tmp;
            }
        }
    }
     
    void dfs2(ll x,ll fa){
        for(auto y:g[x]) if(y!=fa){
            if(n-sz[y]<=n/2){
                outer[y]=n-sz[y];
            }else{
                outer[y]=max(outer[x],y==id[x]?inner2[x]:inner[x]);
            }
            dfs2(y,x);
        }
    }
     
    void solve(){
        cin>>n;
        for(ll i=1;i<n;i++){
            ll u,v;
            cin>>u>>v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs1(1,0);
        dfs2(1,0);
     
        for(ll i=1;i<=n;i++){
            if(n-sz[i]>n/2){
                if(n-sz[i]-outer[i]<=n/2){
                    cout<<1<<" ";
                }else{
                    cout<<0<<" ";
                }
            }else if(sz[mxsub[i]]>n/2){
                if(sz[mxsub[i]]-inner[mxsub[i]]<=n/2){
                    cout<<1<<" ";
                }else{
                    cout<<0<<" ";
                }
            }else{
                cout<<1<<" ";
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