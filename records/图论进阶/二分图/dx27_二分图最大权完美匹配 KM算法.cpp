//perfect bipartite matching(KM algorithm)
//O(n^4)
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=505;

ll n,m;
ll match[N];//右点匹配了哪个左点
ll va[N],vb[N];//标记是否在交替路中
ll la[N],lb[N];//左顶标,右顶标
ll w[N][N],d[N];//维护更新的delta值

bool dfs(ll x){
    va[x]=1; //x在交替路中
    for(ll y=1;y<=n;y++){
        if(!vb[y]){
            if(la[x]+lb[y]-w[x][y]==0){//相等子图
                vb[y]=1; //y在交替路中
                if(!match[y]||dfs(match[y])){
                  match[y]=x; //配对
                  return 1;
                }
            }else{   //不是相等子图则记录最小的d[y]
              d[y]=min(d[y],la[x]+lb[y]-w[x][y]);
            }
        }
    }
    return 0;
}
ll KM(){
  //左顶标取i的出边的最大边权
    for(ll i=1;i<=n;i++){
        la[i]=-inf;
    } 
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=n;j++){
            la[i]=max(la[i],w[i][j]);
        }
    }
    for(ll i=1;i<=n;i++){
        lb[i]=0;
    }   
    for(ll i=1;i<=n;i++){
        while(true){//直到左点i找到匹配
            fill(va+1,va+n+1,0);
            fill(vb+1,vb+n+1,0);
            fill(d+1,d+n+1,inf);
            if(dfs(i)) break;
            ll delta=inf;
            for(ll j=1;j<=n;j++){
                if(!vb[j]){
                    delta=min(delta,d[j]);
                }
            } 
            for(ll j=1;j<=n;j++){//修改顶标
                if(va[j]) la[j]-=delta;
                if(vb[j]) lb[j]+=delta;
            }
        }
    }
    ll res=0;
    for(ll i=1;i<=n;i++) res+=w[match[i]][i];    
    return res;
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=n;j++){
            w[i][j]=-inf; 
        }
    }   
    for(ll i=1;i<=m;i++){
        ll x,y,z;
        cin>>x>>y>>z;
        w[x][y]=z;
    }
    cout<<KM()<<endl;
    for(ll i=1;i<=n;i++){
        cout<<match[i]<<" ";
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