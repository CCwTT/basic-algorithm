//https://ac.nowcoder.com/acm/contest/108304/G
//@@@
//Polya conjecture,linear sieve
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll N=1e6+5;
vector<ll> primes;
bool np[N];
ll a[N];
map<ll,ll> cnt[N];
ll n;
vector<ll> ans;

int init=[]{
    for(ll i=2;i<N;i++){
        if(!np[i]){
            primes.push_back(i);
            a[i]=i;
        }
        for(auto p:primes){
            if(i*p>=N) break;
            np[i*p]=true;
            a[i*p]=p;
            if(i%p==0) break;
        }
    }
    for(ll i=2;i<N;i++){
        cnt[i]=cnt[i/a[i]];
        cnt[i][i/a[i]]++;
        ll cur=0;
        for(auto [x,y]:cnt[i]){
            if(y&1) cur++;
        }
        if(cur&1) ans.push_back(i);
    }
    return 0;
}();

void solve(){
    cin>>n;
    for(ll i=0;i<n/2;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
    }
    return 0;
}