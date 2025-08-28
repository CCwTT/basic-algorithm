//https://www.luogu.com.cn/problem/P4824
//@@@
//kmp,stack
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

vector<ll> get_next(string s){
  ll n=s.size();
  if(n==1){
    return {-1};
  }
  vector<ll> next(n);
  next[0]=-1;
  next[1]=0;
  ll i=2,j=0;
  while(i<n){
    if(s[i-1]==s[j]){
      next[i++]=++j;
    }else if(j){
      j=next[j];
    }else{
      next[i++]=0;
    }
  }
  return next;
}

void solve(){
    string s,t;
    cin>>s>>t;
    ll m=s.size(),n=t.size();
    auto next=get_next(t);
    stack<pair<ll,ll>> stk;
    
    ll i=0,j=0;
    while(i<m){
        if(s[i]==t[j]){
          stk.emplace(i++,j++);
        }else if(j){
          j=next[j];
        }else{
          stk.emplace(i++,-1);
        }
        if(j==n){
          for(ll k=0;k<n;k++){
              if(!stk.empty()) stk.pop();
          }
          j=stk.empty()?0:stk.top().second+1;
        }
    }
    string ans;
    while(!stk.empty()){
        ans+=s[stk.top().first];
        stk.pop();
    }
    reverse(ans.begin(),ans.end());
    cout<<ans<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}