//https://ac.nowcoder.com/acm/contest/108304/I
//@@@
// M×V=V' matrix quick power
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;

const ll N=32;
const ll MOD=998244353;

ll qpow(ll x,ll n){
    ll res=1;
    while(n){
        if(n&1) res=res*x%MOD;
        x=x*x%MOD;
        n>>=1;
    }
    return res;
}

ll inv(ll x){
    return qpow(x,MOD-2);
}

ll n,K;

struct mat{
    ll n,m;
    vector<vector<ll>> a;
    mat(ll n=0,ll m=0,bool op=0):n(n),m(m){
        a.assign(n,vector<ll>(m,0));
        if(op) for(ll i=0;i<n;i++) a[i][i]=1;
    }
    inline vector<ll>& operator[](ll i){
        return a[i];
    }
    inline const vector<ll>& operator[](ll i) const{
        return a[i];
    }
    inline mat operator*(const mat& b) const{
        mat c(n,b.m);
        for(ll i=0;i<n;i++){
            for(ll j=0;j<b.m;j++){
                for(ll k=0;k<m;k++){
                    (c[i][j]+=a[i][k]*b[k][j])%=MOD;
                }
            }
        }
        return c;
    }
};

mat qpow(mat x,ll n){
    mat res(x.n,x.m,1);
    while(n){
        if(n&1) res=res*x;
        x=x*x;
        n>>=1;
    }
    return res;
}

void solve(){
    cin>>n>>K;
    unordered_set<ll> D;
    for(ll i=0;i<K;i++){
        ll x;
        cin>>x;
        D.insert(x);
    }
    mat M(N,N);
    mat vec(N,1);
    for(auto x:D){
        vec[x][0]++;
        for(ll k=0;k<16;k++){
            M[k+x&15][k]++;
            M[(k+x&15)|16][k|16]++;
            M[k+x&15|16][k]+=k+x>>4;

            M[k*x&15][k]++;
            M[k*x&15|16][k|16]+=x;
            M[k*x&15|16][k]+=k*x>>4;

            M[k&x][k]++;

            M[k|x][k]++;
            M[k|x|16][k|16]++;

            M[k^x][k]++;
            M[k^x|16][k|16]++;
        }
    }
    vec=qpow(M,n-1)*vec;
    ll fz=0,inv_fm=0;
    for(ll i=0;i<16;i++){
        (fz+=vec[i][0]*i)%=MOD;
    }
    for(ll i=16;i<32;i++){
        (fz+=16*vec[i][0])%=MOD;
    }
    inv_fm=inv(qpow(D.size(),n))*inv(qpow(5,n-1))%MOD;
    cout<<fz*inv_fm%MOD<<endl;
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