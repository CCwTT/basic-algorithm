//https://atcoder.jp/contests/abc407/tasks/abc407_f
//@@@
//!!!
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
    vector<pair<ll,ll>> A(n);
    for(ll i=0;i<n;i++){
        A[i]={a[i],i};
    }
    sort(A.begin(),A.end());

    vector<vector<ll>> integral(3);

    integral[0].resize(n+3);
    for(ll i=0;i<=n+2;i++){
        integral[0][i]=0;
    }
    set<ll> used={-1,n};
    for(ll i=n-1;i>=0;i--){
        auto [val,idx]=A[i];

        auto itge=used.lower_bound(idx);
        auto itle=itge; --itle;

        // how many elements (on left/right) can a[idx] absorb as a maximum
        ll r=*itge-idx-1;
        ll l=idx-*itle-1;

        ll mn=min(l,r),mx=max(l,r);

        // ans[0 < i <= 1+min] <- i
        // ans[1+min < i <= 1+max] <- 1+min
        // ans[1+max < i <= 1+min+max] <- 1+min - (i - (1+max))
        // ans[1+min+max < i] <- 0

        // ans'[0 < i <= 1+min] <- +1
        // ans'[1+min < i <= 1+max] <- 0
        // ans'[1+max < i <= 1+min+max] <- -1
        // ans'[1+min+max < i] <- 0

        // ans''[1] <- +1
        // ans''[1+min+1] <- -1
        // ans''[1+max+1] <- -1
        // ans''[1+min+max+1] <- +1
        integral[0][1        ]+=val*(+1);
        integral[0][1+mn+1   ]+=val*(-1);
        integral[0][1+mx+1   ]+=val*(-1);
        integral[0][1+mn+mx+2]+=val*(+1);
        used.insert(idx);
    }
    for(ll i=1;i<=2;i++){
        integral[i].resize(n+3);
        integral[i][0]=0;
        for(ll j=1;j<=n+2;j++){
            integral[i][j]=integral[i][j-1]+integral[i-1][j];
        }
    }
    vector<ll> ans(n+1,0);
    for(ll i=1;i<=n;i++){
        ans[i]=integral[2][i];
    }
    for(ll i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
}

signed main() {
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}