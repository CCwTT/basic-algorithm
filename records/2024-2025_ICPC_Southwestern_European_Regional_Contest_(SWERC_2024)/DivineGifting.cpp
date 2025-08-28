//https://vjudge.net/contest/713843#problem/B
//@@@
//DP,pre-processing,plan-seeking
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
    ll n,K;
    cin>>n>>K;
    vector<ll> a(n+1);
    for(ll i=1;i<=n;++i){
        cin>>a[i];
    }
    K=min(K,n);
    auto b=a;
    sort(a.begin()+1,a.end());

    vector<vector<ll>> pre(n+2,vector<ll>(n+2));
    auto pre_process=[&]()->void{
        for(ll r=n;r>=1;--r){
            for(ll l=r;l>=1;--l){
                pre[l][r]=pre[l+1][r]+abs((a[r]-a[l])*(a[r]-a[l]));
            }
        }
    };
    pre_process();

    vector<vector<ll>> f(n+1,vector<ll>(21,LLONG_MAX/2));
    f[0][0]=0; //
    for(ll i=1;i<=n;i++){ //i traverses the sorted days，such as day1，day10，day10，day12...
        for(ll j=0;j<i;j++){ //j traverses the days before i
            for(ll k=1;k<=K;k++){ //k indicates the remaining number of days
                f[i][k]=min(f[i][k],f[j][k-1]+pre[j+1][i]);
            }
        }
    }
    vector<ll> plan;
    ll i=n,k=K;
    while(i>0){
        plan.push_back(i);
        for(ll j=0;j<i;j++){
            if(f[i][k]==f[j][k-1]+pre[j+1][i]){
                i=j,k--;
            }
        }
    }
    reverse(plan.begin(),plan.end());
    vector<ll> ans(n+1);
    for(ll i=0;i<plan.size();i++) plan[i]=a[plan[i]];
    for(ll i=1;i<=n;i++){
        ans[i]=*lower_bound(plan.begin(),plan.end(),b[i]);
    }
    for(ll i=1;i<=n;i++) cout<<ans[i]<<" ";
    cout<<endl;
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
