#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MAXN=1e5+5;
ll n,ans=0;
set<string> st[MAXN];


void solve(){
    cin>>n;
    for(ll i=0;i<n;i++){
        string s;
        cin>>s;
        st[s.size()].insert(s);
    }
    st[0].insert("");
    for(ll i=1;i<MAXN;i++){
        if(st[i].empty()){
            break;
        }
        for(auto it=st[i].begin();it!=st[i].end();){
            if(!st[i-1].count((*it).substr(0,i-1))||!st[i-1].count((*it).substr(1))){
                it=st[i].erase(it);
            }else{
                ans=i;
                it++;
            }
        }
    }
    cout<<ans<<endl;
}

signed main(){
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}