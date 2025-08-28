//https://atcoder.jp/contests/abc399/editorial/12580

//https://www.luogu.com.cn/problem/P7981
//g是内向基环树，rg是外向基环树
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
};

//https://www.luogu.com.cn/problem/P1453
//@@@
//无向基环树
struct functional_graph{
    vector<ll> g[N],rg[N];
    bool onc[N]; ll bel[N],cdis[N],sc[N];
   // ll dep[N],entry[N]; //wait to be added
    ll deg[N],vis[N];
    //onc
    void find_cycle(){
      for(ll i=1;i<=n;i++){
        onc[i]=true;
        for(auto j:g[i]){
          if(i<=j){
            deg[i]++;
            deg[j]++;
          }
        }
      }
      queue<ll> q;
      for(ll i=1;i<=n;i++){
        if(deg[i]==1){
          q.push(i);
        }
      }
      while(!q.empty()){
        ll u=q.front();
        q.pop();
        onc[u]=false;
        for(auto v:g[u]){
          if(--deg[v]==1){
            q.push(v);
          }
        }
      }
    }
    
    //bel,cdis,sc,rf
    void dfs1(ll x,ll fa,ll rt){
        bel[x]=rt;
        sc[rt]++;
        for(auto y:g[x]) if(y!=fa&&onc[y]){
            if(y!=rt){
                cdis[y]=cdis[x]+1;
                dfs1(y,x,rt);
            }
        }
        sc[x]=sc[rt];
    }

    void build(){
        find_cycle();
        for(ll i=1;i<=n;i++){
            if(onc[i]&&!bel[i]){
                dfs1(i,0,i);
            }
        }
    }
};