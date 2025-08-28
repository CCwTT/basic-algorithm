//https://www.luogu.com.cn/problem/P3808
//@@@
//AC automation
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=5e5+5;
const ll BASE=26;
ll n;
string s;
ll ch[N][BASE],ed[N],cnt;
ll fail[N];

void insert(string s){
    ll p=0;
    for(auto c:s){
        ll x=c-'a';
        if(!ch[p][x]) ch[p][x]=++cnt;
        p=ch[p][x];
    }
    ed[p]++;
}

//O(n*BASE)
void build(){
    queue<ll> q;
    for(ll i=0;i<BASE;i++){
        if(ch[0][i]){
            q.push(ch[0][i]);
        }
    }
    while(!q.empty()){
        ll u=q.front();
        q.pop();
        for(ll i=0;i<BASE;i++){
            ll v=ch[u][i];
            if(v){ //父亲来帮忙
                fail[v]=ch[fail[u]][i];
                q.push(v);
            }else{
                ch[u][i]=ch[fail[u]][i];
            }
        }
    }
}

//O(n+m)
ll query(string s){
    ll res=0;
    ll p=0;
    for(auto c:s){
        ll x=c-'a';
        p=ch[p][x];
        for(ll q=p;q&&~ed[q];q=fail[q]){
            res+=ed[q];
            ed[q]=-1;
        }
    }
    return res;
}

void solve(){
    cin>>n;
    for(ll i=0;i<n;i++){
        cin>>s;
        insert(s);
    }
    build();
    cin>>s;
    cout<<query(s)<<endl;
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