//https://www.luogu.com.cn/problem/P5094
//@@@ 
//cdq
//这道题也可以用树状数组做
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
    ll v,x;
};

const ll N=5e4+5;
ll n;
Node A[N];
Node tmp[N];

ll merge(ll l,ll m,ll r){
    ll i,j;
    ll lsum=0,rsum=0,res=0;
    for(i=l;i<=m;i++){
        rsum+=A[i].x;
    }
    for(i=l,j=m+1;j<=r;j++){
        while(i<=m&&A[i].x<A[j].x){
            rsum-=A[i].x;
            lsum+=A[i].x;
            i++;
        }
        res+=A[j].v*((i-l)*A[j].x-lsum+rsum-(m-i+1)*A[j].x);
    }
    i=l,j=m+1;
    ll k=l;
    while(i<=m&&j<=r) tmp[k++]=A[i].x<A[j].x?A[i++]:A[j++];
    while(i<=m) tmp[k++]=A[i++];
    while(j<=r) tmp[k++]=A[j++];
    copy(tmp+l,tmp+r+1,A+l);
    return res;
}

ll cdq(ll l,ll r){
    if(l==r) return 0;
    ll m=l+r>>1;
    return cdq(l,m)+cdq(m+1,r)+merge(l,m,r);
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>A[i].v>>A[i].x;
    }
    sort(A+1,A+n+1,[&](const auto& u,const auto& v){
        return u.v<v.v;
    });
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