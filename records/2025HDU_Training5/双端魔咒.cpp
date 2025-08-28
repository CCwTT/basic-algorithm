//https://acm.hdu.edu.cn/contest/problem?cid=1176&pid=1008
//@@@
//AC automation
//(重要结论)只要保证以每个字母开头的模式串只有一个，就可以安心地在匹配过程中跳fail
//(Important conclusion) As long as it is ensured that there is only one pattern string starting with each letter, one can safely jump to fail during the matching process.
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const int N=1e6+5;
const int T=1e6+5;
const int B=26;

struct AC{
  int tr[T][B],fail[T],id[T],len[T],cnt=0;

  void init(){
    for(int i=0;i<=cnt;i++){
      for(int j=0;j<B;j++){
        tr[i][j]=0;
      }
      fail[i]=id[i]=len[i]=0;
    }
    cnt=0;
  }

  void insert(const string& s,int idx){
    int p=0;
    for(auto c:s){
      int x=c-'a';
      if(!tr[p][x]) tr[p][x]=++cnt;
      p=tr[p][x];
    }
    id[p]=idx;
    len[p]=s.size();
  }

  void build(){
    queue<int> q;
    for(int i=0;i<B;i++){
      if(tr[0][i]){
        q.push(tr[0][i]);
      }
    }
    while(!q.empty()){
      int u=q.front();
      q.pop();
      for(int i=0;i<B;i++){
        int& v=tr[u][i];
        if(v){
          fail[v]=tr[fail[u]][i];
          q.push(v);
        }else{
          v=tr[fail[u]][i];
        }
      }
    }
  }

  vector<vector<int>> query_pos(const string& s,int n){
    vector<vector<int>> pos(n+1);
    int p=0;
    int i=0;
    for(auto c:s){
      int x=c-'a';
      p=tr[p][x];
      for(int q=p;q;q=fail[q]){
        if(id[q]){
          pos[id[q]].push_back(i-len[q]+1);
        }
      }
      i++;
    }
    return pos;
  }

  ll query_sum(const string& s){
    ll res=0;
    int p=0;
    for(auto c:s){
      int x=c-'a';
      p=tr[p][x];
      for(int q=p;q;q=fail[q]){
        if(id[q]){
          res++;
        }
      }
    }
    return res;
  }

  vector<int> collect(int p=0){
    vector<int> res;
    queue<int> q;
    q.push(p);
    while(!q.empty()){
      int u=q.front();
      q.pop();
      if(id[u]){
        res.push_back(id[u]);
        continue;
      }
      for(int i=0;i<B;i++){
        if(tr[u][i]){
          q.push(tr[u][i]);
        }
      }
    }
    return res;
  }
}ac1,ac2;

string prefix[N],suffix[N];
ll sum[N];

void solve(){
  ac1.init();
  ac2.init();
  int n,m;
  cin>>n>>m;
  for(int i=1;i<=n;i++){
    cin>>prefix[i];
    ac1.insert(prefix[i],i);
  }
  for(int i=1;i<=m;i++){
    cin>>suffix[i];
    reverse(suffix[i].begin(),suffix[i].end());
    ac2.insert(suffix[i],i);
  }
  string S;
  cin>>S;
  for(int i=0;i<S.size();i++){
    sum[i]=0;
  }
  auto ids1=ac1.collect();
  auto ids2=ac2.collect();
  ac1.init();
  ac2.init();
  for(auto i:ids1){
    ac1.insert(prefix[i],i);
  }
  for(auto i:ids2){
    reverse(suffix[i].begin(),suffix[i].end());
    ac2.insert(suffix[i],i);
  }
  ac1.build();
  ac2.build();
  auto pre_pos=ac1.query_pos(S,n);
  auto suf_pos=ac2.query_pos(S,m);
  for(int i=0;i<ids2.size();i++){
    for(auto pos:suf_pos[ids2[i]]){
      sum[pos]++;
    }
  }
  for(int i=(int)S.size()-1;i>0;i--){
    sum[i-1]+=sum[i];
  }
  ll ans=0;
  for(int i0=0;i0<ids1.size();i0++){
    int i=ids1[i0];
    for(auto pos:pre_pos[i]){
      ans+=sum[pos];
    }
    auto inter_cnt=ac2.query_sum(prefix[i].substr(0,(int)prefix[i].size()-1));
    ans-=inter_cnt*pre_pos[i].size();
  }
  cout<<ans<<endl;
}

signed main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);cout.tie(0);
    int T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}