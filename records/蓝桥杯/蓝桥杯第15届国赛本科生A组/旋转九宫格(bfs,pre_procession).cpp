//https://www.lanqiao.cn/problems/20156/learning/
//@@@
//bfs,pre-procession
#include<bits/stdc++.h>
using namespace std;
#define endl '\n';
typedef long long ll;

string rotate_top_left(const string &s){
    string t=s;
    t[0]=s[1];
    t[1]=s[4];
    t[3]=s[0];
    t[4]=s[3];
    return t;
}

string rotate_top_right(const string &s){
    string t=s;
    t[1]=s[2];
    t[2]=s[5];
    t[4]=s[1];
    t[5]=s[4];
    return t;
}

string rotate_bottom_left(const string &s){
    string t=s;
    t[3]=s[4];
    t[4]=s[7];
    t[6]=s[3];
    t[7]=s[6];
    return t;
}

string rotate_bottom_right(const string &s){
    string t=s;
    t[4]=s[5];
    t[5]=s[8];
    t[7]=s[4];
    t[8]=s[7];
    return t;
}

vector<function<string(const string&)>> Rotate={
    rotate_top_left,
    rotate_top_right,
    rotate_bottom_left,
    rotate_bottom_right
};

unordered_map<ll,ll> dis;

int init=[]{
  string s="123456789";
  ll s_code=stoll(s);
  queue<string> q;
  q.push(s);
  dis[s_code]=0;

  while(!q.empty()){
      string u=q.front();
      q.pop();
      ll u1=stoll(u);
      for(ll i=0;i<4;++i){
          string v=Rotate[i](u);
          ll v1=stoll(v);
          if(!dis.count(v1)){
              dis[v1]=dis[u1]+1;
              q.push(v);
          }
      }
  }
  return 0;
}();

void solve(){
  string s;
  for(ll i=0;i<3;++i){
      for(ll j=0;j<3;++j){
        ll x;
        cin>>x;
        s+=x+'0';
      }
  }
  cout<<dis[stoll(s)]<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}