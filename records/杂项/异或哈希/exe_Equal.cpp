//https://ac.nowcoder.com/acm/contest/108300/E
//@@@
//xor hash(linear sieve+dp+hash)
//link:records\2025NewCoder_Training3\Equal.cpp
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// ll rnd(ll l,ll r){
//     return rng()%(r-l+1)+l;
// }

const ll MAXN=1e6+5;
const ll MAXM=5e6+5;
ll a[MAXN];
ll n;

vector<ll> primes;
bool np[MAXM];
ll hsh[MAXM];

int init=[]{
    for(ll i=2;i<MAXM;i++){
        if(!np[i]){
            primes.push_back(i);
            hsh[i]=rng();
        }
        for(auto p:primes){
            if(p*i>=MAXM) break;
            np[p*i]=true;
            hsh[p*i]=hsh[i]^hsh[p];
            if(i%p==0) break;
        }
    }
    return 0;
}();

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++) cin>>a[i];
    if(n&1){
        cout<<"YES"<<endl;
        return;
    }
    if(n==2){
        cout<<(a[1]==a[2]?"YES":"NO")<<endl;
        return;
    }
    int eor=0;
    for(ll i=1;i<=n;i++){
        eor^=hsh[a[i]];
    }
    cout<<(eor?"NO":"YES")<<endl;
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