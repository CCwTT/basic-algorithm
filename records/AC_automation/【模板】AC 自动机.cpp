//https://www.luogu.com.cn/problem/P5357
//@@@
//AC automation
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=2e5+5;
const ll T=2e5+5;  //The passal number of characters in all target strings
const ll B=26;

ll eid[N];

struct AC{
    ll tr[T][B],fail[T],pass[T],cnt=0; //AC Automation
    vector<ll> g[T]; //fail tree

    void insert(const string& s,ll id){
        ll p=0;
        for(auto &c:s){
            ll x=c-'a';
            if(!tr[p][x]) tr[p][x]=++cnt;
            p=tr[p][x];
        }
        eid[id]=p;
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
            for(ll i=0;i<B;i++){
                ll v=tr[u][i];
                if(v){
                    fail[v]=tr[fail[u]][i];
                    q.push(v);
                }else{
                    tr[u][i]=tr[fail[u]][i];
                }
            }
        }
    }
    
    void query(const string& s){
        ll p=0;
        for(auto c:s){
            ll x=c-'a';
            p=tr[p][x];
            pass[p]++;
        }
    }
    
    void dfs(ll u){
        for(auto v:g[u]){
            dfs(v);
            pass[u]+=pass[v];
        }
    }

    void build_fail_tree(){
        for(ll i=1;i<=cnt;i++){
            g[fail[i]].push_back(i);
        }
        dfs(0);
    }
};

ll n;

void solve(){
    AC ac;
    cin>>n;
    for(ll i=1;i<=n;i++){
        string s;
        cin>>s;
        ac.insert(s,i);
    }
    ac.build();
    string S;
    cin>>S;
    ac.query(S);
    ac.build_fail_tree();
    for(ll i=1;i<=n;i++){
        cout<<ac.pass[eid[i]]<<endl;
    }
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