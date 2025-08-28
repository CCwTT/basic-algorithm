//https://www.luogu.com.cn/problem/P4093
//@@@ 
//dp optimized by cdq
//not left right mid,but left mid right
//If resorting by some criterion is needed in merge,assistant array is needed in order not to change the way to compute dp from left to right 辅助数组!
/*
记dp[i]为以第i项结尾的子序列最长长度。
则有转移：dp[i]=max_{j<i}(dp[j])+1，同时还要满足 rv[j] ≤ v[i] 和 v[j] ≤ lv[i]。
其中rv[i]表示第i项最大能变成的值,lv[i]表示第i项最小能变成的值。
按照项从小到大转移，形成了天然的时间顺序，同时还要满足两个偏序限制。
算上时间顺序，这是一个三维偏序问题,用CDQ分治+树状数组就能解决。
*/
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
ll n,m;

struct Node{
    ll i,v,lv,rv;
};

Node A[N];
ll dp[N];
ll v[N],lv[N],rv[N];

ll tr[N];

void fw_update(ll x,ll v){
    while(x<N){
        chmax(tr[x],v);
        x+=x&-x;
    }
}

ll fw_query(ll x){
    ll res=0;
    while(x>0){
        chmax(res,tr[x]);
        x&=x-1;
    }
    return res;
}

void fw_clear(ll x){
    while(x<N){
        tr[x]=0;
        x+=x&-x;
    }
}

void merge(ll l,ll m,ll r){
    for(ll i=l;i<=r;i++){
        A[i]={i,v[i],lv[i],rv[i]};
    }
    sort(A+l,A+m+1,[&](const auto& u,const auto& v){
        return u.v<v.v;
    });
    sort(A+m+1,A+r+1,[&](const auto& u,const auto& v){
        return u.lv<v.lv;
    });
    ll i,j;
    for(i=l,j=m+1;j<=r;j++){
        while(i<=m&&A[i].v<=A[j].lv){
            fw_update(A[i].rv,dp[A[i].i]);
            i++;
        }
        chmax(dp[A[j].i],fw_query(A[j].v)+1);
    }
    for(ll k=l;k<i;k++){
        fw_clear(A[k].rv);
    }
}

void cdq(ll l,ll r){
    if(l==r) return;
    ll m=l+r>>1;
    cdq(l,m);
    merge(l,m,r);
    cdq(m+1,r);
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        cin>>v[i];
        lv[i]=v[i];
        rv[i]=v[i];
    }
    for(ll i=1;i<=m;i++){
        ll idx,val;
        cin>>idx>>val;
        chmin(lv[idx],val);
        chmax(rv[idx],val);
    }
    fill(dp+1,dp+n+1,1);
    cdq(1,n);
    cout<<*max_element(dp+1,dp+n+1)<<endl;
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