//https://atcoder.jp/contests/abc406/tasks/abc406_c
//@@@
//transformation
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
   ll n;
   cin>>n;
   vector<ll> a(n);
   for(ll i=0;i<n;i++){
      cin>>a[i];
   }
   vector<pair<char,ll>> b;
   for(ll i=0;i<n-1;i++){
      if(a[i]<a[i+1]){
         if(b.empty()||b.back().first=='>'){
            b.emplace_back('<',1);
         }else{
            b.back().second++;
         }
      }else{
         if(b.empty()||b.back().first=='<'){
            b.emplace_back('>',1);
         }else{
            b.back().second++;
         }
      }
   }
   ll ans=0;
   for(ll i=1;i<b.size()-1;i++){
       if(b[i].first=='>'){
           ans+=b[i-1].second*b[i+1].second;
       }
   }
   cout<<ans<<endl;
}

signed main() {
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}