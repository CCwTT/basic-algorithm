//https://www.luogu.com.cn/problem/P6088
//@@@
//persistent trie
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf LLONG_MAX/2
typedef long long ll;

const ll MAXN=1e5+5;
const ll MAXT=MAXN*30;
const ll HIGH=20;
ll n,m;

vector<pair<string,ll>> g[MAXN];
ll root[MAXN];
struct node{
    ll ch[27];
    ll pass;
};
node tr[MAXT];
ll cnt=0;

ll dep[MAXN];
ll stj[MAXN][HIGH+1];

ll num(char c){
    return c-'a'+1;
}

ll insert(const string& s,ll pre){
    ll rt=++cnt;
    tr[rt]=tr[pre];
    tr[rt].pass++;
    for(auto c:s){
        ll path=num(c);
        pre=tr[pre].ch[path];
        cnt++;
        tr[cnt]=tr[pre];
        tr[cnt].pass++;
        tr[cnt-1].ch[path]=cnt;
    }
    return rt;
}

ll  count_prefix(const string& s,ll p){
    for(auto c:s){
        ll path=num(c);
        p=tr[p].ch[path];
        if(!p) return 0;
    }
    return tr[p].pass;
}

void dfs(ll x,ll fa,const string& s){
    root[x]=insert(s,root[fa]);
    dep[x]=dep[fa]+1;
    stj[x][0]=fa;
    for(ll d=1;d<=HIGH;d++){
        stj[x][d]=stj[stj[x][d-1]][d-1];
    }
    for(auto [w,y]:g[x]) if(y!=fa){
        dfs(y,x,w);
    }
}

ll lca(ll x,ll y){
    if(dep[x]<dep[y]) swap(x,y);
    for(ll d=HIGH;d>=0;d--){
        if(dep[stj[x][d]]>=dep[y]){
            x=stj[x][d];
        }
    }
    if(x==y) return x;
    for(ll d=HIGH;d>=0;d--){
        if(stj[x][d]!=stj[y][d]){
            x=stj[x][d];
            y=stj[y][d];
        }
    }
    return stj[x][0];
}

ll compute(ll x,ll y,const string& prefix){
    return count_prefix(prefix,root[x])+count_prefix(prefix,root[y])-2*count_prefix(prefix,root[lca(x,y)]);
}

void solve(){
    cin>>n;
    for(ll i=1;i<n;i++){
        ll u,v;
        string w;
        cin>>u>>v>>w;
        g[u].emplace_back(w,v);
        g[v].emplace_back(w,u);
    }
    dfs(1,0,"");
    cin>>m;
    while(m--){
        ll x,y;
        string s;
        cin>>x>>y>>s;
        cout<<compute(x,y,s)<<endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}    