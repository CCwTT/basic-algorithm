#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MAXN=5e4+5;
ll n,k;
ll a[MAXN];  //
ll b[21];    
ll c[21];
ll A,B;

bool check(ll x){
    memcpy(c,b,sizeof(b));
    priority_queue<ll> pq;
    for(ll i=1;i<=n;i++){
        pq.push(a[i]*x);
    }
    ll i=k;
    while(i!=0&&!pq.empty()){
        ll u=pq.top();
        pq.pop();
        ll t=max(1ll,min(c[i],u/(1ll<<(i-1))));
        u-=t*(1ll<<(i-1));
        if(u>0){
            pq.push(u);
        }
        c[i]-=t;
        if(c[i]<=0){
            i--;
        }
    }
    return pq.empty();
}

void solve(){
    A=B=0;
    cin>>n>>k;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        A+=a[i];
    }
    for(ll i=1;i<=k;i++){
        cin>>b[i];
        B+=b[i]*(1ll<<(i-1));
    }
    ll ans=0;
    ll left=0,right=B/A;
    while(left<=right){
        ll mid=left+right>>1;
        if(check(mid)){
            ans=mid;
            left=mid+1;
        }else{
            right=mid-1;
        }
    }
    cout<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
}