struct cost_flow{
    const static ll MAXN=1e5+5;
    const static ll MAXM=2e6+5;
    struct edge{
        ll to,c,w,ne;
    };

    ll n=0,m=0;
    edge e[MAXM<<1]; ll h[MAXN]; ll cnte=1;
    ll dis[MAXN],cur[MAXN]; bool vis[MAXN];
    ll src,snk,flow,cost;

    cost_flow(ll n){
        clear();
        this->n=n;
    }

    void clear(){
        for(ll i=0;i<=n;i++){
            h[i]=dis[i]=cur[i]=vis[i]=0;
        }
        for(ll i=0;i<=cnte;i++){
            e[i]={0,0,0,0};
        }
        n=m=src=snk=flow=cost=0;
        cnte=1;
    }

    void add_edge(ll u,ll v,ll c,ll w){
        e[++cnte]={v,c,w,h[u]};
        h[u]=cnte;
        e[++cnte]={u,0,-w,h[v]};
        h[v]=cnte;
    }

    bool spfa(){
        fill(dis,dis+n+1,INF);
        copy(h,h+n+1,cur);
        deque<ll> q; 
        dis[src]=0;
        vis[src]=true;
        q.push_back(src);
        while(!q.empty()){
            ll u=q.front();
            q.pop_front();
            vis[u]=false;
            for(ll i=h[u];i;i=e[i].ne){
                auto [v,c,w,_]=e[i];
                if(dis[v]>dis[u]+w&&c){
                    dis[v]=dis[u]+w;
                    if(!vis[v]){
                        vis[v]=true;
                        //SLF optimization: If the new distance is less than the front-of-queue distance,insert at the front of the queue.
                        if(!q.empty()&&dis[v]<dis[q.front()]){
                            q.push_front(v);
                        }else{
                            q.push_back(v);
                        }
                    }
                }
            }
        }
        return dis[snk]<INF; 
    }

    ll dfs(ll u,ll mf){
        if(u==snk) return mf;
        ll res=0;
        vis[u]=true;
        for(ll i=cur[u];i;i=e[i].ne){
            cur[u]=i; 
            auto [v,c,w,_]=e[i];
            if(!vis[v]&&dis[v]==dis[u]+w&&c){
                ll f=dfs(v,min(mf,c));
                if(f){
                    e[i].c-=f;
                    e[i^1].c+=f;
                    res+=f;
                    mf-=f;
                    cost+=f*e[i].w;
                    if(mf==0) break;
                }
                else{
                    dis[v]=INF; 
                }
            }
        }
        vis[u]=false; 
        return res;
    }

    pll mcmf(ll src,ll snk){
        this->src=src;
        this->snk=snk;
        while(spfa()){
            flow+=dfs(src,INF);
        }
        return {flow,cost};
    }
};