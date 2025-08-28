//https://codeforces.com/problemset/problem/165/E
//@@@
//SOSDP,Eratosthenes sieve 
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;
typedef unsigned long long ull;

const ll MAXN=2e7+7;
const ull mod=1ull<<32;
ll n;
ll a[MAXN];
bool np[MAXN];

#define uint unsigned int
uint seed;
inline uint getnext(){
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}

void solve(){
    cin>>n>>seed;
    for(ll i=1;i<=n;i++){
        a[i]=getnext();
    }
    for(ll mask=2;mask<=n;mask++){
        if(!np[mask]){
            for(ll nmask=mask;nmask<=n;nmask+=mask){
                np[nmask]=1;
                a[nmask]+=a[nmask/mask];
                a[nmask]%=mod;
            }
        }
    }
    ll ans=0;
    for(ll i=1;i<=n;i++){
        ans^=a[i];
    }
    cout<<ans<<endl;
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