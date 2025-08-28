//https://ac.nowcoder.com/acm/contest/108303/K
//@@@
//i dont know
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=1e5+5;
ll a[N],b[N];
ll n,ans;

vector<ll> get_factor(ll x){
    vector<ll> res;
    for(ll i=1;i*i<=x;i++){
        if(x%i==0){
            if(i*i<x){
                res.push_back(i);
                res.push_back(x/i);
            }else{
                res.push_back(i);
            }
        }
    }
    return res;
}

vector<ll> factors;
void compute(){
    for(auto x:factors){
        vector<ll> ids;
        for(ll i=1;i<=n;i++){
            if(b[i]%x!=0){
                ids.push_back(i);
            }
        }
        bool ok=false;
        if(ids.size()<=1){
            ok=true;
        }else if(ids.size()==2){
            ll t1=(b[ids[0]]%x+x)%x;
            ll t2=((-b[ids[1]])%x+x)%x;
            ok=t1==t2;
        }
        if(ok){
            ans=max(ans,x);
        }
    }
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    bool flag=true;
    for(ll i=2;i<=n;i++){
        if(a[i]!=a[1]){
            flag=false;
            break;
        }
    }
    if(flag){
        cout<<0<<endl;
        return;
    }
    b[1]=a[1];
    for(ll i=2;i<=n;i++){
        b[i]=a[i]-a[i-1];
    }
    ans=0;
    for(ll i=2;i<=n;i++){
        ans=gcd(ans,b[i]);
    }
    factors=get_factor(a[1]);
    compute();
    factors=get_factor(a[n]);
    compute();
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