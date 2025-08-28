//https://codeforces.com/problemset/problem/165/E
//>~<
//SOSDP,prefix sum
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;
typedef unsigned long long ull;

const ll MAXN=2e7+7;
const ll MAXT=8e7;
const ull mod=1ull<<32;
ll n;
ll a[MAXN];
constexpr ull len[]={1,32,20,13,11,9,8,7,7,7};
constexpr ull pw[]={1,32,640,8320,91520,823680,6589440,46126080,322822560,2260177920};

#define uint unsigned int
uint seed;
inline uint getnext(){
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        a[i]=getnext();
    }
    for(ll d=1;d<9;d++){
        for(ll mask=0;mask<pw[9];mask++){

        }
    }
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