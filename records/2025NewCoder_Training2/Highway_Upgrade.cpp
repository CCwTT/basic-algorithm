//https://ac.nowcoder.com/acm/contest/108299/H
//@@@
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n
#define inf (LLONG_MAX/3)
typedef long long ll;

const ll MAXN=6e5+5;
ll n,m,q;
vector<array<ll,3>> g[MAXN];
vector<array<ll,3>> rg[MAXN];
ll t0[MAXN];
array<ll,4> edges[MAXN];
pair<ll,ll> edges1[MAXN];
pair<ll,ll> edges2[MAXN];
pair<ll,ll> Q[MAXN];
ll ans[MAXN];

void f(ll ql,ll qr,ll el,ll er){
    if(ql>qr) return;
    ll qm=(ql+qr)>>1;
    ll mn=inf,mnid=-1;
    auto [k,id]=Q[qm];
    for(ll i=el;i<=er;i++){
        auto [t,w]=edges2[i];
        if(t-k*w<mn){
            mn=t-k*w;
            mnid=i;
        }
    }
    ans[id]=mn;
    f(ql,qm-1,el,mnid);
    f(qm+1,qr,mnid,er);
}

vector<ll> dijkstra(vector<array<ll,3>>* g,ll s){
    vector<ll> dis(n+1,inf);
    dis[s]=0;
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq;
    pq.emplace(0,s);
    while(!pq.empty()){
        auto [disu,u]=pq.top();
        pq.pop();
        if(disu>dis[u]) continue;
        for(auto [v,t,_]:g[u]){
            if(dis[v]>dis[u]+t){
                dis[v]=dis[u]+t;
                pq.emplace(dis[v],v);
            }
        }
    }
    return dis;
}

void solve(){
    for(ll i=1;i<=n;i++){
        g[i].clear();
        rg[i].clear();
    }
    cin>>n>>m;
    for(ll i=1;i<=m;i++){
        ll u,v,t,w;
        cin>>u>>v>>t>>w;
        g[u].push_back({v,t,w});
        rg[v].push_back({u,t,w});
        edges[i]={u,v,t,w};
    }
    auto dis=dijkstra(g,1);
    auto rdis=dijkstra(rg,n);
    for(ll i=1;i<=m;i++){
        auto [u,v,t,w]=edges[i];
        edges1[i]={dis[u]+t+rdis[v],w};
    }
    sort(edges1+1,edges1+m+1,[](const auto& u,const auto& v){
        return u.first^v.first?u.first<v.first:u.second<v.second;
    });
    vector<pair<ll,ll>> stk;
    for(ll i=1;i<=m;i++){
        if(!stk.empty()&&(stk.back().first==edges1[i].first)){
            stk.pop_back();
        }
        if(stk.empty()||edges1[i].second>stk.back().second) stk.push_back(edges1[i]);
    }
    for(ll i=1;i<=(ll)stk.size();i++){
        edges2[i]=stk[i-1];
    }
    cin>>q;
    for(ll i=1;i<=q;i++){
        ll k;
        cin>>k;
        Q[i]={k,i};
    }
    sort(Q+1,Q+q+1);
    f(1,q,1,stk.size());
    for(ll i=1;i<=q;i++){
        cout<<ans[i]<<endl;
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T; 
    while(T--){
        solve();
    }
    return 0;
}