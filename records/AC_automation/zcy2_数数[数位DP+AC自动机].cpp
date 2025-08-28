//https://www.luogu.com.cn/problem/P3311
//@@@
//digit dp+AC automation
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll MOD=1e9+7;
const ll N=1305;
const ll T=2005;
const ll B=10;

string num;
ll n,m;

struct AC{
    ll tr[T][B],fail[T],cnt=0;
    bool ed[T];

    void insert(const string& s){
        ll p=0;
        for(auto& c:s){
            ll x=c-'0';
            if(!tr[p][x]) tr[p][x]=++cnt;
            p=tr[p][x];
        }
        ed[p]=true;
    }

    void build(){
        queue<ll> q;
        for(ll i=0;i<B;i++){
            if(tr[0][i]){
                q.push(tr[0][i]);
            }
        }
        while(!q.empty()){
            ll u=q.front();
            q.pop();
            ed[u]|=ed[fail[u]];
            for(ll i=0;i<B;i++){
                ll& v=tr[u][i];
                if(v){
                    fail[v]=tr[fail[u]][i];
                    q.push(v);
                }else{
                    v=tr[fail[u]][i];
                }
            }
        }
    }
}ac;

ll dp[N][T][2][2];

void clear(){
    for(ll i=0;i<=n;i++){
        for(ll j=0;j<=ac.cnt;j++){
            memset(dp[i][j],-1,sizeof(dp[i][j]));
        }
    }
}

ll dfs(ll p1,ll p2,bool free,bool begun){
    if(ac.ed[p2]){
        return 0;
    }
    if(p1==n){
        return begun;
    }
    ll& res=dp[p1][p2][free][begun];
    if(~res){
        return res;
    }
    res=0;
    if(!begun){
        res=(res+dfs(p1+1,0,true,false))%MOD;
    }
    ll down=begun?0:1;
    ll up=free?9:num[p1]-'0';
    for(ll d=down;d<=up;d++){
        res=(res+dfs(p1+1,ac.tr[p2][d],free||d<up,true))%MOD;
    }
    return res;
}

void solve(){
    cin>>num;
    n=num.size();
    cin>>m;
    for(ll i=1;i<=m;i++){
        string s;
        cin>>s;
        ac.insert(s);
    }
    ac.build();
    clear();
    cout<<dfs(0,0,0,0)<<endl;
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