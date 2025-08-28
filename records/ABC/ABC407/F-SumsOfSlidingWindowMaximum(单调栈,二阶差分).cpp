//https://atcoder.jp/contests/abc407/tasks/abc407_f
//@@@
//!!!
//monotonic stack,second difference
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> get_lnb(vector<ll>& a){
    ll n=a.size();
    vector<ll> lnb(n,-1);
    stack<ll> stk;
    for(ll i=0;i<n;i++){
        while(!stk.empty()&&a[stk.top()]<=a[i]){
            stk.pop();
        }
        if(stk.size()){
            lnb[i]=stk.top();
        }
        stk.push(i);
    }
    return lnb;
}

vector<ll> get_rnb(vector<ll>& a){
    ll n=a.size();
    vector<ll> rnb(n,n);
    stack<ll> stk;
    for(ll i=n-1;i>=0;i--){
        while(!stk.empty()&&a[stk.top()]<a[i]){
            stk.pop();
        }
        if(stk.size()){
            rnb[i]=stk.top();
        }
        stk.push(i);
    }
    return rnb;
}

void solve(){
    ll n;
    cin>>n;
    vector<ll> a(n);
    for(ll i=0;i<n;i++){
        cin>>a[i];
    }
    vector<pair<ll,ll>> A(n);
    for(ll i=0;i<n;i++){
        A[i]={a[i],i};
    }
    sort(A.begin(),A.end());
    auto lnb=get_lnb(a);
    auto rnb=get_rnb(a);

    vector<vector<ll>> diff(3,vector<ll>(n+3));
    for(ll i=n-1;i>=0;i--){
        auto [val,idx]=A[i];
        ll r=rnb[idx]-idx-1;
        ll l=idx-lnb[idx]-1;
        ll mn=min(l,r),mx=max(l,r);
        diff[2][1        ]+=val;
        diff[2][1+mn+1   ]-=val;
        diff[2][1+mx+1   ]+=val;
        diff[2][1+mn+mx+2]-=val;
    }
    for(ll i=1;i>=0;i--){
        for(ll j=1;j<=n+2;j++){
            diff[i][j]=diff[i][j-1]+diff[i+1][j];
        }
    }
    for(ll i=1;i<=n;i++){
        cout<<diff[0][i]<<endl;
    }
}

signed main() {
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}