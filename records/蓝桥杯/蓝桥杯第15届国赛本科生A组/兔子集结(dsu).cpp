//https://www.lanqiao.cn/problems/20152/learning/
//@@@
//dsu
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

void Log(vector<ll>& a){
	ll n=a.size();
	for(ll i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

class Dsu{
public:
  vector<ll> f,pos;
  Dsu(ll n):f(n),pos(n,-1){
    iota(f.begin(),f.end(),0);
  }

  ll find(ll x){
    return f[x]==x?x:f[x]=find(f[x]);
  }

  void join(ll x,ll y){
    ll fx=find(x);
    ll fy=find(y);
    if(fx!=fy){
      f[fy]=fx;
      pos[fx]=max(pos[fx],pos[fy]);
    }
  }

  bool check(ll x,ll y){
    return find(x)==find(y);
  }
};

void solve(){
  ll n;
  cin>>n;
  vector<pair<ll,ll>> A(n);
  for(ll i=0;i<n;i++){
    cin>>A[i].first;
    A[i].second=i;
  }
  sort(A.begin(),A.end());
  vector<ll> dir(n);
  for(ll i=0;i<n;i++){
    if(i==0){
      dir[i]=1;
    }else if(i==n-1){
      dir[i]=-1;
    }else{
      if(A[i+1].first-A[i].first<A[i].first-A[i-1].first){
        dir[i]=1;
      }else{
        dir[i]=-1;
      }
    }
  }
  Dsu dsu(n);
  for(ll i=0;i<n;i++){
    if(dir[i]==1){
      dsu.join(i,i+1);
      if(dir[i+1]==-1){
        dsu.pos[dsu.find(i)]=(A[i].first+A[i+1].first)/2;
      }
    }else{
      dsu.join(i,i-1);
      if(dir[i-1]==1){
        dsu.pos[dsu.find(i)]=(A[i].first+A[i-1].first)/2;
      }
    }
  }
  vector<ll> ans(n);
  for(ll i=0;i<n;i++){
    ans[A[i].second]=dsu.pos[dsu.find(i)];
  }
  for(ll i=0;i<n;i++){
    cout<<ans[i]<<" ";
  }
  cout<<endl;
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
