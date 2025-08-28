//https://codeforces.com/problemset/problem/1045/G
//@@@ 
//cdq
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

const ll N=1e5+5;
ll n,K,m;

struct Node{
    ll x,y,iq;
    ll l,r;
};

Node A[N];

struct discretizer{
    vector<ll> disc;
    discretizer(){
        disc.push_back(LLONG_MIN);
    }
    void insert(ll x){
        disc.push_back(x);
    }
    ll discretize(){
        sort(disc.begin()+1,disc.end());
        disc.erase(unique(disc.begin(),disc.end()),disc.end());
        return disc.size()-1;
    }
    ll get_rank(ll x){
        return lower_bound(disc.begin(),disc.end(),x)-disc.begin();
    }
}disc;

ll tr[N];

void fw_update(ll x,ll v){
    while(x<N){
        tr[x]+=v;
        x+=x&-x;
    }
}

ll fw_query(ll x){
    ll res=0;
    while(x>0){
        res+=tr[x];
        x&=x-1;
    }
    return res;
}

ll fw_query(ll l,ll r){
    return fw_query(r)-fw_query(l-1);
}

void prepare(){
    for(ll i=1;i<=n;i++){
        disc.insert(A[i].x);
    }
    m=disc.discretize();
    for(ll i=1;i<=n;i++){
        A[i].l=lower_bound(disc.disc.begin(),disc.disc.end(),A[i].x-A[i].y)-disc.disc.begin();
        A[i].r=upper_bound(disc.disc.begin(),disc.disc.end(),A[i].x+A[i].y)-disc.disc.begin()-1;
        A[i].x=disc.get_rank(A[i].x);
    }
    sort(A+1,A+n+1,[&](const auto& u,const auto& v){
        return u.y>v.y; //Mistake made here before:u.y<v.y
    });
}

ll merge(ll l,ll m,ll r){
    ll i1=l,i2=l;
    ll res=0;
    for(ll j=m+1;j<=r;j++){
        while(i1<=m&&A[i1].iq<A[j].iq-K){
            fw_update(A[i1].x,-1);
            i1++;
        }
        while(i2<=m&&A[i2].iq<=A[j].iq+K){
            fw_update(A[i2].x,1);
            i2++;
        }
        res+=fw_query(A[j].l,A[j].r);
    }
    for(ll k=i1;k<i2;k++){
        fw_update(A[k].x,-1);
    }
    sort(A+l,A+r+1,[&](const auto& u,const auto& v){
        return u.iq<v.iq;
    });
    return res;
}

ll cdq(ll l,ll r){
    if(l==r) return 0;
    ll m=l+r>>1;
    return cdq(l,m)+cdq(m+1,r)+merge(l,m,r);
}

void solve(){
    cin>>n>>K;
    for(ll i=1;i<=n;i++){
        cin>>A[i].x>>A[i].y>>A[i].iq;
    }
    prepare();
    cout<<cdq(1,n)<<endl;
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