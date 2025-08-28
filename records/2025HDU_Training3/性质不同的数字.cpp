//https://acm.hdu.edu.cn/contest/problem?cid=1174&pid=1007
//@@@
//xor hash
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
constexpr ll N=2e5+10,mod=1e9+7;
ll n,h[N];

ll init=[](){
    for(ll i=0;i<N;i++)
        h[i]=rng();
    return 0;
}();

void solve(){
    cin>>n;
    vector<pair<ll,ll>> a(n);
    for(auto&[l,r]:a)
        cin>>l>>r;
    map<ll,ll> mp;
    for(ll i=0;i<n;i++){
        auto[l,r]=a[i];
        mp[l]^=h[i];
        mp[r+1]^=h[i];
    }
    unordered_set<ll> S;
    ll XOR=0;
    for(auto&[x,v]:mp){
        XOR^=v;
        S.insert(XOR);
    }
    S.insert(0);
    cout<<S.size()<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
