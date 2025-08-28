//https://www.luogu.com.cn/problem/P3804
//@@@
//SAM
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll MAXN=2e6+5;
string s;
vector<int> g[MAXN];
ll cnt[MAXN],ans;
ll tot=1,np=1;
int fa[MAXN],ch[MAXN][26],len[MAXN];

void extend(ll c){
    ll p=np;np=++tot;
    len[np]=len[p]+1;
    cnt[np]=1;
    while(p&&!ch[p][c]){
        ch[p][c]=np;
        p=fa[p];
    }
    if(!p){
        fa[np]=1;
    }else{
        ll q=ch[p][c];
        if(len[q]==len[p]+1){
            fa[np]=q;
        }else{
            ll nq=++tot;
            len[nq]=len[p]+1;
            fa[nq]=fa[q];
            fa[q]=nq;
            fa[np]=nq;
            while(p&&ch[p][c]==q){
                ch[p][c]=nq;
                p=fa[p];
            }
            memcpy(ch[nq],ch[q],sizeof(ch[q]));
        }
    }
}

void dfs(ll x){
    for(auto y:g[x]){
        dfs(y);
        cnt[x]+=cnt[y];
    }
    if(cnt[x]>1){
        ans=max(ans,cnt[x]*len[x]);
    }
}

void solve(){
   cin>>s;
   for(ll i=0;i<s.size();i++){
        extend(s[i]-'a');
   }
   for(ll i=2;i<=tot;i++){
        g[fa[i]].push_back(i);
   }
   dfs(1);
   cout<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}