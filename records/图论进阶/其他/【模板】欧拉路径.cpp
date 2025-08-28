//https://www.luogu.com.cn/problem/P7771
//@@@
//Euler path(circuit)
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

const ll N=1e5+5;
ll n,m;
vector<ll> g[N];
ll vis[N];
stack<ll> stk;
ll ind[N],oud[N];

void dfs(ll u){
    for(ll i=vis[u];i<g[u].size();i=vis[u]){
        ll v=g[u][i];
        vis[u]=i+1;
        dfs(v);
    }
    stk.push(u);
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=m;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
        ind[v]++;
        oud[u]++;
    }
    for(ll i=1;i<=n;i++){
        sort(g[i].begin(),g[i].end());
    }
    ll src=INF;
    ll cnt1=0,cnt2=0;
    ll cnt_odd=0;
    for(ll i=1;i<=n;i++){
        if(ind[i]^oud[i]){
            if(oud[i]-ind[i]==1){
                cnt1++;
                chmin(src,i);
            }else if(ind[i]-oud[i]==1){
                cnt2++;
            }else{
                return cout<<"No"<<endl,void();
            }
        }
    }
    if(!(cnt1==0&&cnt2==0||cnt1==1&&cnt2==1)){
        return cout<<"No"<<endl,void();
    }
    if(cnt1==0&&cnt2==0){
        src=1;
    }
    dfs(src);
    while(!stk.empty()){
        cout<<stk.top()<<" ";
        stk.pop();
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