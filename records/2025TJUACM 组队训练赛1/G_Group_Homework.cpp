//codeforces.com/gym/104008/problem/G
//@@@
//tree dp
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=2e5+5;
ll a[N];
vector<ll> g[N];
ll n,ans=0;

struct node{
    ll val;
    ll id;
    node(ll val=0,ll id=0):val(val),id(id){}
    bool operator<(const node& o) const{
        return val<o.val;
    }
};

vector<node> inner1[N];
vector<node> inner2[N];
vector<ll> outer1[N];
vector<ll> outer2[N];

void add(vector<ll>& vec,ll x,ll sz){
    vec.push_back(x);
    sort(vec.rbegin(),vec.rend());
    vec.resize(sz);
}

void add(vector<node>& vec,node x,ll sz){
    for(auto& [val,id]:vec){
        if(id==x.id){
            if(x.val>val){
                val=x.val;
            }
            sort(vec.rbegin(),vec.rend());
            return;    
        }
    }
    vec.push_back(x);
    sort(vec.rbegin(),vec.rend());
    vec.resize(sz);
}

void init(){
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=4;j++) inner1[i].emplace_back(0,0);
        for(ll j=1;j<=3;j++) inner2[i].emplace_back(0,0);
        outer1[i].push_back(0);
        outer2[i].push_back(0);
    }
}

void dfs1(ll u,ll fa){
    for(auto v:g[u]) if(v!=fa){
        dfs1(v,u);
        add(inner1[u],{inner1[v][0].val+a[v],v},4);
        add(inner2[u],{inner2[v][0].val,v},3);
        add(inner2[u],{inner1[v][0].val+inner1[v][1].val+a[v],v},3);
    }
}

void dfs2(ll u,ll fa){
    for(auto v:g[u]) if(v!=fa){
        add(outer1[v],a[u]+max(outer1[u][0],inner1[u][0].id!=v?inner1[u][0].val:inner1[u][1].val),1);
        add(outer2[v],outer2[u][0],1);
        add(outer2[v],inner2[u][0].id!=v?inner2[u][0].val:inner2[u][1].val,1);
        add(outer2[v],a[u]+outer1[u][0]+(inner1[u][0].id!=v?inner1[u][0].val:inner1[u][1].val),1);
        if(v==inner1[u][0].id){
            add(outer2[v],a[u]+inner1[u][1].val+inner1[u][2].val,1);
        }else if(v==inner1[u][1].id){
            add(outer2[v],a[u]+inner1[u][0].val+inner1[u][2].val,1);
        }else{
            add(outer2[v],a[u]+inner1[u][0].val+inner1[u][1].val,1);
        }
        dfs2(v,u);
    }
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    for(ll i=1;i<n;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if(n==1){
        cout<<0<<endl;
        return;
    }
    init();
    dfs1(1,0);
    dfs2(1,0);
    for(ll i=1;i<=n;i++){
        vector<node> tmp(inner1[i].begin(),inner1[i].end());
        add(tmp,{outer1[i][0],-1},4);
        ans=max(ans,tmp[0].val+tmp[1].val+tmp[2].val+tmp[3].val);
        if(i>1){
            ans=max(ans,max(inner1[i][0].val+inner1[i][1].val+a[i],inner2[i][0].val)+outer2[i][0]);
        }
    }
    cout<<ans<<endl;
}

signed main(){
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}