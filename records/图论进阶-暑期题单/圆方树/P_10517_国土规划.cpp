#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
#define EPS (1e-20)
typedef long long ll;
typedef __int128 i128;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll N=1e6+5;

ll n,m,q;

ll dfn[N],low[N],tim,cnt; stack<ll> stk; //tarjan
ll dep[N],pa[N],siz[N],son[N],top[N],dfn1[N],ori[N],cnt1; //HLD
bool key[N];
ll x,y,t,sum1;
ll ans[N];
vector<ll> g[N],G[N];
set<ll> st;

void tarjan(ll x){
    dfn[x]=low[x]=++tim;
    stk.push(x);
    for(auto y:g[x]){
        if(!dfn[y]){
            tarjan(y);
            low[x]=min(low[x],low[y]);
            if(low[y]==dfn[x]){
                cnt++;
                while(true){
                    ll u=stk.top();
                    stk.pop();
                    G[u].push_back(cnt);
                    G[cnt].push_back(u);
                    if(u==y) break;
                }
                G[cnt].push_back(x);
                G[x].push_back(cnt);
            }
        } else{
            low[x]=min(low[x],dfn[y]);
        }
    }
}

void dfs1(ll u,ll fa){
    dep[u]=dep[fa]+1;
    pa[u]=fa;
    siz[u]=1;
    son[u]=0;
    for(auto v:G[u]) if(v!=fa){
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]){
            son[u]=v;
        }
    }
}

void dfs2(ll u,ll tp){
    top[u]=tp;
    dfn1[u]=++cnt1;
    ori[cnt1]=u;
    ans[u]=ans[pa[u]]+(u<=n);
    for(auto v:G[u]) if(v!=pa[u]){
        if(v==son[u]){
            dfs2(son[u],tp);
        }else{
            dfs2(v,v);
        }
    }
}

ll __lca(ll u,ll v){
    while(top[u]!=top[v]){
        if(dep[top[u]]>dep[top[v]]){
            u=pa[top[u]];
        }else{
            v=pa[top[v]];
        }
    }
    return dep[u]<=dep[v]?u:v;
}

ll sum;

inline void check(ll x,ll f){
    key[x]=!key[x];
    if(f==-1) st.insert(dfn1[x]);
    auto it=st.find(dfn1[x]);
    if(it==st.begin()){
        it++;
        if(it!=st.end()){
            ll lca=__lca(ori[*st.begin()],ori[*it]);
            sum-=(ans[ori[*st.begin()]]+ans[ori[*it]]-2*ans[lca])*f;
            lca=__lca(ori[*st.begin()],ori[*st.rbegin()]);
            sum-=(ans[ori[*st.begin()]]+ans[ori[*st.rbegin()]]-2*ans[lca])*f;
            lca=__lca(ori[*it],ori[*st.rbegin()]);
            sum+=(ans[ori[*it]]+ans[ori[*st.rbegin()]]-2*ans[lca])*f;
            lca=__lca(ori[*st.begin()],ori[*st.rbegin()]);
            sum1-=(lca<=n)*f;
            lca=__lca(ori[*it],ori[*st.rbegin()]);
            sum1+=(lca<=n)*f;
        } else{
            sum1-=1*f;
        }
    } else{
        it++;
        if(it==st.end()){
            it--;
            auto it1=it;
            it1--;
            if(st.size()!=1){
                ll lca=__lca(ori[*it1],ori[*it]);
                sum-=(ans[ori[*it1]]+ans[ori[*it]]-2*ans[lca])*f;
                lca=__lca(ori[*st.begin()],ori[*it1]);
                sum+=(ans[ori[*st.begin()]]+ans[ori[*it1]]-2*ans[lca])*f;
                lca=__lca(ori[*st.begin()],ori[*it]);
                sum-=(ans[ori[*st.begin()]]+ans[ori[*it]]-2*ans[lca])*f;
                lca=__lca(ori[*st.begin()],ori[*it]);
                sum1-=(lca<=n)*f;
                lca=__lca(ori[*st.begin()],ori[*it1]);
                sum1+=(lca<=n)*f;
            }
        } else{
            auto it1=it;
            it--;
            auto it2=it;
            it2--;
            ll lca=__lca(ori[*it1],ori[*it2]);
            sum+=(ans[ori[*it1]]+ans[ori[*it2]]-2*ans[lca])*f;
            lca=__lca(ori[*it1],ori[*it]);
            sum-=(ans[ori[*it1]]+ans[ori[*it]]-2*ans[lca])*f;
            lca=__lca(ori[*it2],ori[*it]);
            sum-=(ans[ori[*it2]]+ans[ori[*it]]-2*ans[lca])*f;
        }
    }
    if(f==1) st.erase(dfn1[x]);
}


void solve(){
    cin>>n>>m>>q;
    for(ll i=1;i<=m;i++){
        cin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    cnt=n;
    tarjan(1); //连通,n>=2
    dfs1(1,0);
    dfs2(1,1);
    while(q--){
        cin>>x;
        if(key[x]==1){
            check(x,1);
        } else{
            check(x,-1);
        }
        cout<<n-(sum>>1)-sum1<<'\n';
    }
}

void clear(){}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
        clear();
    }
    return 0;
}
