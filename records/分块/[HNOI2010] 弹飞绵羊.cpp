//https://www.luogu.com.cn/problem/P3203
//@@@
//block algorithm
/*
如果我们记录答案数组，那么每次修改操作最坏为 O(n)，查询操作
O(1)，如果我们 O(1) 修改，那么每次查询最坏情况要跳 O(n)，所以
我们考虑平衡两者的复杂度，修改只考虑当前块，每次修改跳出当前
块就停止，每次查询直接跳过完整的块。
使用 num[i] 代表从 i 开始跳需要几次跳出当前块，nxt[i] 代表从 i 开始
跳出当前块之后会落到哪个点上。
单点修改时重新维护当前块的 nxt[] 和 num[]。
查询时最坏情况下需要跳过 √n 个块，每个块都可以 O(1) 跳出。
两者的复杂度最坏情况都是 O(√n)
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MAXN=2e5+5;
const ll MAXB=500;

ll a[MAXN];
ll bel[MAXN];
ll times[MAXN];
ll nxt[MAXN];

ll n,m,len;

inline ll lend(ll X){
    return (X-1)*len+1;
}

inline ll rend(ll X){
    return min(n,X*len);
}

void pre_process(){
    for(ll i=n;i>=1;i--){
        if(i+a[i]>rend(bel[i])){
            times[i]=1;
            nxt[i]=i+a[i];
        }else{
            times[i]=times[i+a[i]]+1;
            nxt[i]=nxt[i+a[i]];
        }
    }
}

void solve(){
    cin>>n;
    len=(ll)sqrt(n);
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        bel[i]=(i-1)/len+1;
    }
    pre_process();
    cin>>m;
    while(m--){
        ll op;
        cin>>op;
        if(op==1){
            ll x;
            cin>>x;
            x++;
            ll ans=0;
            ll i=x;
            while(i<=n){
                ans+=times[i];
                i=nxt[i];
            }
            cout<<ans<<endl;
        }else{
            ll x,v;
            cin>>x>>v;
            x++;
            a[x]=v;
            for(ll i=x;i>=lend(bel[x]);i--){
                if(i+a[i]>rend(bel[x])){
                    times[i]=1;
                    nxt[i]=i+a[i];
                }else{
                    times[i]=times[i+a[i]]+1;
                    nxt[i]=nxt[i+a[i]];
                }
            }
        }
    }
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