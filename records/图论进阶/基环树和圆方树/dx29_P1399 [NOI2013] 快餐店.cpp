//https://www.luogu.com.cn/problem/P1399
//@@@
//functional tree
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=100010;
ll n;
vector<pair<ll,ll>> g[N];
ll vis[N],pre[N],w[N];
ll onc[N],cv[N],cw[N],cn;
double dl[N],A[N],B[N],C[N],D[N];
double ans1,ans2=inf*1.0;

bool find_circle(ll u){
  vis[u]=true;
  for(auto [w_,v]:g[u]) if(v!=pre[u]){
      pre[v]=u; w[v]=w_;      
      if(!vis[v]){ //v未访问
        if(find_circle(v)) return true;
      }else{ //v已访问
        ll p=u;
        while(true){
          onc[p]=1;
          cv[++cn]=p;
          cw[cn]=w[p];
          p=pre[p];
          if(p==u) break;
        }    
        return 1;
      }
  }
  return 0;
}

void dfs(ll u,ll fa){
  for(auto [w,v]:g[u]){
    if(!onc[v]&&v!=fa){
      dfs(v,u);
      ans1=max(ans1,dl[u]+dl[v]+w);
      dl[u]=max(dl[u],dl[v]+w);
    }
  }
}

void solve(){
    cin>>n;
    for(ll i=1,x,y,z;i<=n;i++){
      cin>>x>>y>>z;
      g[x].emplace_back(z,y);
      g[y].emplace_back(z,x);
    }
    find_circle(1); //dfs for circle

    for(ll i=1;i<=cn;i++){
        dfs(cv[i],0); //dfs for ans1
    } 

    double sum=0,mx=0;
    for(ll i=1;i<=cn;++i){ //get prefix
        A[i]=max(A[i-1],sum+dl[cv[i]]);
        B[i]=max(B[i-1],mx+dl[cv[i]]+sum);
        mx=max(mx,dl[cv[i]]-sum);
        sum+=cw[i];
    }

    sum=mx=0;
    for(ll i=cn;i>=1;--i){ //get suffix
        if(i<cn) sum+=cw[i];
        C[i]=max(C[i+1],sum+dl[cv[i]]);
        D[i]=max(D[i+1],mx+dl[cv[i]]+sum);
        mx=max(mx,dl[cv[i]]-sum);
    }

    double tmp;
    for(ll i=1;i<cn;++i){ //拼凑答案
        tmp=max(max(B[i],D[i+1]),A[i]+C[i+1]+cw[cn]);
        ans2=min(ans2,tmp);
    }
    ans2=min(ans2,B[cn]); //断最后一条边
    cout<<fixed<<setprecision(1)<<max(ans1,ans2)/2.0<<endl;
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