//https://acm.hdu.edu.cn/contest/problem?cid=1158&pid=1008
//@@@
//two-dimensional prefix sum/diff
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
    ll n,q;
    cin>>n>>q;
    vector<pair<ll,ll>> A(n+1);
    for(ll i=1;i<=n;++i){
        ll x;
        cin>>x;
        A[i]={x,i};
    }
    sort(A.begin()+1,A.end());
    vector<ll> b(n+1,1);
    vector<vector<ll>> s(n+1,vector<ll>(n+1));
    for(ll i=1;i<=n;++i){
        ll pos=A[i].second;
        b[pos]=0;
        ll l0=pos; while((l0>1)&&(b[l0-1]==0)) --l0;
        ll r0=pos; while((r0<n)&&(b[r0+1]==0)) ++r0;
        if(r0==n) continue;
        ll l1=r0+1;
        ll r1=l1; while((r1<n)&&(b[r1+1]==1)) ++r1;
        //two-dimensional diff array update 
        s[l0][l1]++;
        s[l0][r1+1]--;
        s[pos+1][l1]--;
        s[pos+1][r1+1]++;
    }

	//two-dimensional prefix-sum calculation
    for(ll i=1;i<=n;++i){
        for(ll j=1;j<=n;++j){
            s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
        }
    }

    for(ll i=1;i<=q;++i){
        ll l,r;
        cin>>l>>r;
        cout<<s[l][r]<<"\n";
    }
} 

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll T;
    cin>>T;
    while(T--){
        solve();
    }
}
