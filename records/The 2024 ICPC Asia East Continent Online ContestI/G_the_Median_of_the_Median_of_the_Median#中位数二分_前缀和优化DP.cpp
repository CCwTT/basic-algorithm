#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
#define EPS (1e-20)
typedef long long ll;
typedef __int128 i128;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll MOD=998244353;

const ll N=2005;
ll n;
ll A[N],a[N],b[N][N],c[N][N];
ll sum1[N],sum2[N][N];
ll sorted[N];

bool check(ll x){
    for(ll i=1;i<=n;i++){
        a[i]=A[i]>=x;
    }
    for(ll i=1;i<=n;i++){
        sum1[i]=sum1[i-1]+a[i];
    }
    for(ll i=1;i<=n;i++){
        b[i][i]=a[i];
    }
    for(ll len=2;len<=n;len++){
        for(ll i=1,j=i+len-1;j<=n;i++,j++){
            b[i][j]=(len/2+1<=(sum1[j]-sum1[i-1]));
        }
    }
    for(ll j=1;j<=n;j++){
        for(ll i=1;i<=j;i++){
            sum2[i][j]=sum2[i-1][j]+b[i][j];
        }
    }
    for(ll i=1;i<=n;i++){
        c[i][i]=b[i][i];
    }
    for(ll len=2;len<=n;len++){
        for(ll i=1,j=i+len-1;j<=n;i++,j++){
            c[i][j]=c[i][j-1]+sum2[j][j]-sum2[i-1][j];
        }
    }
    ll d=0;
    for(ll i=1;i<=n;i++){
        for(ll j=i;j<=n;j++){
            d+=c[i][j]>=(j-i+1)*(j-i+2)/2/2+1;
        }
    }
    return d>=n*(n+1)/2/2+1;
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>A[i];
        sorted[i]=A[i];
    }
    sort(sorted+1,sorted+n+1);
    ll l=1,r=n,ans;
    while(l<=r){
        ll m=l+r>>1;
        if(check(sorted[m])){
            ans=sorted[m];
            l=m+1;
        }else{
            r=m-1;
        }
    }
    cout<<ans<<endl;
}

void clear(){}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
        clear();
    }
    return 0;
}