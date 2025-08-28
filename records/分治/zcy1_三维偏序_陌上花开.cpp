//https://www.luogu.com.cn/problem/P3810
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

struct Node{
    ll a,b,c;
    ll id;
};

const ll N=1e5+5;
const ll K=2e5+5;
ll n,k;

Node A[N];
ll f[N];
ll ans[N];

ll tr[K];
void fw_update(ll x,ll v){
    while(x<K){
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

void merge(ll l,ll m,ll r){
    ll i=l-1,j=m+1;
    while(j<=r){
        while(i+1<=m&&A[i+1].b<=A[j].b){
            i++;
            fw_update(A[i].c,1);
        }
        f[A[j].id]+=fw_query(A[j].c);
        j++;
    }
    for(ll k=l;k<=i;k++){
        fw_update(A[k].c,-1);
    }
    sort(A+l,A+r+1,[&](const Node& u,const Node& v){
        return u.b<v.b;
    });
}

void cdq(ll l,ll r){
    if(l==r) return;
    ll m=l+r>>1;;
    cdq(l,m);
    cdq(m+1,r);
    merge(l,m,r);
}

void prepare(){
    sort(A+1,A+n+1,[&](const Node& u,const Node& v){
        return u.a!=v.a?u.a<v.a:u.b!=v.b?u.b<v.b:u.c<v.c;
    });
    for(ll i=1,j=1;i<=n;i=++j){
        while(j+1<=n&&A[i].a==A[j+1].a&&A[i].b==A[j+1].b&&A[i].c==A[j+1].c){
            j++;
        }
        for(ll k=i;k<=j;k++){
            f[A[k].id]=j-k;
        }
    }
}

void solve(){
    cin>>n>>k;
    for(ll i=1;i<=n;i++){
        A[i].id=i;
        cin>>A[i].a>>A[i].b>>A[i].c;
    }
    prepare();
    cdq(1,n);
    for(ll i=1;i<=n;i++){
        ans[f[i]]++;
    }
    for(ll i=0;i<n;i++){
        cout<<ans[i]<<endl;
    }
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
