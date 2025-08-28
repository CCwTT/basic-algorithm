//https://acm.hdu.edu.cn/contest/problem?cid=1158&pid=1006
//@@@
//geometry,dijkstra
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Tri{
    ll x,y,len,w;
    pair<ll,ll> ver_proj(){
        return {x,x+len};
    }
    pair<ll,ll> hor_proj(){
        return {y,y+len};
    }
    pair<ll,ll> diag_proj(){
        return {y-x-len,y-x};
    }
    bool is_intersect(Tri b){
        auto not_intersect=[](pair<ll,ll> u,pair<ll,ll> v){
            return max(u.first,v.first) > min(u.second,v.second);
        };
        if(not_intersect(ver_proj(),b.ver_proj())) return false;
        if(not_intersect(hor_proj(),b.hor_proj())) return false;
        if(not_intersect(diag_proj(),b.diag_proj())) return false;
        return true;
    }
};

vector<ll> dijkstra(vector<vector<pair<ll,ll>>>& g,ll s){
    vector<ll> dis(g.size(),LLONG_MAX);
    dis[s]=0;
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq;
    pq.emplace(0,s);
    while(!pq.empty()){
        auto [disx,x]=pq.top();
        pq.pop();
        if(disx!=dis[x]) continue;
        for(auto [w,y]:g[x]){
            if(dis[y]>disx+w){
                dis[y]=disx+w;
                pq.emplace(dis[y],y);
            }
        }
    }
    return dis;
}

void solve(){
    ll n,W;
    cin>>n>>W;
    vector<Tri> a(n+1);
    for(ll i=1;i<=n;++i){
        ll x,y,len,w;
        cin>>x>>y>>len>>w;
        a[i]={x,y,len,w};
    }
    vector<vector<pair<ll,ll>>> g(n+4);
    auto add_edge=[&](ll u,ll v)->void{
        //Technique:point weight transforms into edge weight!
        g[u].emplace_back(u<=n?a[u].w:0,v); 
        g[v].emplace_back(v<=n?a[v].w:0,u);
    };
    for(ll i=1;i<=n;++i){
        auto [x,y,len,_]=a[i];
        if(x+len==W) add_edge(i,n+1);
        if(y==x) add_edge(i,n+2);
        if(y==0) add_edge(i,n+3);
    }
    for(ll i=1;i<=n;++i){
        for(ll j=i+1;j<=n;++j){
            if(a[i].is_intersect(a[j])){
                add_edge(i,j);
            }
        }
    }
    vector<ll> disa=dijkstra(g,n+1);
    vector<ll> disb=dijkstra(g,n+2);
    vector<ll> disc=dijkstra(g,n+3);
    ll ans=LLONG_MAX;
    for(ll i=1;i<=n;++i){
        if((disa[i]==LLONG_MAX)||(disb[i]==LLONG_MAX)||(disc[i]==LLONG_MAX)) continue;
        ans=min(ans,a[i].w+disa[i]+disb[i]+disc[i]);
    }
    cout<<(ans==LLONG_MAX?-1:ans)<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}