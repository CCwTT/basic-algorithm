//https://ac.nowcoder.com/acm/contest/108306/C
//@@@
//search,pruning
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

constexpr ll N=30;
ll n,m;
ll a[N],ind[N];
vector<vector<ll>> g(N);
ll ans=INF;

struct cmp{
    bool operator()(ll x,ll y)const{
        if(a[x]!=a[y])return a[x]<a[y];
        return x<y;
    }
};

void dfs(ll t,set<ll,cmp>& st){
    if(t>=ans) return;
    if(st.size()==0){
        ans=min(ans,t);
        return;
    }
    set<ll,cmp> nst=st;
    for(auto i:st){
        nst.erase(i);
        for(auto j:g[i]){
            ind[j]--;
            if(!ind[j]) nst.insert(j);
        }
        dfs(t+a[i],nst);
    }
    for(auto i:st){
        for(auto j:g[i]){
            ind[j]++;
        }
    }
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++)cin>>a[i];
    for(ll i=1,u,v;i<=m;i++){
        cin>>u>>v;
        g[u].push_back(v);
        ind[v]++;
    }
    set<ll,cmp> st;
    for(ll i=1;i<=n;i++){
        if(!ind[i]){
            st.insert(i);
        }
    }
    dfs(0,st);
    cout<<ans<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
    }
    return 0;
}