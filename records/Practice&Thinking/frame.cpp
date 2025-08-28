#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MAXN=1e5+5;
ll n;
ll a[MAXN],b[MAXN];

struct node{
    ll val;
    ll ai,bi;
    bool operator<(const node& o) const{
        return val<o.val;
    }
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    for(ll i=1;i<=n;i++){
        cin>>b[i];
    }
    sort(a+1,a+n+1);
    sort(b+1,b+n+1);
    a[n+1]=b[n+1]=LLONG_MAX/2;
    priority_queue<node,vector<node>,greater<node>> pq;
    pq.push({a[1]+b[1],1,1});
    for(ll i=1;i<=n;i++){
        auto [val,ai,bi]=pq.top();
        pq.pop();
        cout<<val<<" ";
        if(a[ai+1]-a[ai]<=b[bi+1]-b[bi]){
            pq.push({a[ai+1]+b[bi],ai+1,bi});
        }else{
            pq.push({a[ai]+b[bi+1],ai,bi+1});
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