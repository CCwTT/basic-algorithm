//https://acm.hdu.edu.cn/contest/problem?cid=1176&pid=1002
//@@@
//binary search
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=2e5+5;
ll n,m,k,p;
ll a[N];

bool check(ll x){
    ll cnt=0;
    vector<ll> vec;
    for(ll i=1;i<=n;i++){
        if(a[i]>=x*k){
            cnt+=x;
        }else{
            cnt+=a[i]/k;
            vec.push_back(a[i]%k);
        }
    }
    if(cnt>=x*p) return x*p*k>=m;
    ll sum=cnt*k;
    for(ll i=0;i<min((ll)vec.size(),x*p-cnt);i++){
        sum+=vec[i];
    }
    return sum>=m;
}

void solve(){
    cin>>n>>m>>k>>p;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1,[](const auto& u,const auto& v){
        return u%k>v%k;
    });
    ll l=1,r=1e18,ans;
    while(l<=r){
        ll mid=l+r>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
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