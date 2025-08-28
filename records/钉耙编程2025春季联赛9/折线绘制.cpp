//https://acm.hdu.edu.cn/contest/problem?cid=1158&pid=1002
//@@@
//manacher_p_array
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

vector<ll> get_p(vector<ll> s){
    ll n=s.size();
    vector<ll> p(n);
    ll c=0,r=0;
    for(ll i=0;i<n;i++){
        ll len=i<r?min(r-i,p[2*c-i]):1;
        while(0<=i-len&&i+len<n&&(s[i-len]==-1||s[i-len]+s[i+len]==s[i-len+2]+s[i+len-2])){
            len++;
        }
        p[i]=len;
        if(i+len>r){
            r=i+len;
            c=i;
        }
    }
    return p;
}

vector<ll> manacher(vector<ll> s0){
    vector<ll> s={-1};
    for(auto x:s0){
        s.push_back(x);
        s.push_back(-1);
    }
    return get_p(s);
}

void solve(){
    ll n;
    cin>>n;
    vector<ll> a(n);
    for(ll i=0;i<n;i++){
        cin>>a[i];
    }
    auto p=manacher(a);
    ll ans=0;
    for(ll len:p){
        ans+=len/2;
    }
    cout<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}