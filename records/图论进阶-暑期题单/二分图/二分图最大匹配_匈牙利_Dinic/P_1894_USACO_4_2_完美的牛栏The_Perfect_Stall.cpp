//https://www.luogu.com.cn/problem/P4329
//perfect bipartite matching(KM algorithm)
//O(n^4)
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=505;
const long double eps=1e-10;

ll n;
ll match[N];//右点匹配了哪个左点
bool va[N],vb[N];//标记是否在交替路中
long double la[N],lb[N];//左顶标,右顶标
long double w[N][N],d[N];//维护更新的delta值

bool dfs(ll x){
    va[x]=1; //x在交替路中
    for(ll y=1;y<=n;y++){
        if(!vb[y]){
            if(fabsl(la[x]+lb[y]-w[x][y])<eps){//相等子图  //attention!
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

long double KM(){
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
            long double delta=inf;
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
    double res=0.0;
    for(ll i=1;i<=n;i++) res+=w[match[i]][i];    
    return res;
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=n;j++){
            ll x;
            cin>>x;
            w[i][j]=x/100.0;
            if(w[i][j]==0){
                w[i][j]=-inf;   //attention!
            }else{
                w[i][j]=log2(w[i][j]);
            }
        }
    }  
    cout<<fixed<<setprecision(10)<<(exp2(KM())*100)<<endl;
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