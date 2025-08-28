//https://www.luogu.com.cn/problem/P3755
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
    ll typ;
    ll x,y;
    ll v;
    ll id;
};

const ll N=1e5+5;
Node A[N+(N<<2)]; ll cnt=0;
Node tmp[N+(N<<2)];
ll ans[N];

ll n,m;

void merge(ll l,ll m,ll r){
    ll i,j;
    ll sum=0;
    for(i=l-1,j=m+1;j<=r;j++){
        while(i+1<=m&&A[i+1].y<=A[j].y){
            i++;
            if(A[i].typ==1){
                sum+=A[i].v;
            }
        }
        if(A[j].typ==2){
            ans[A[j].id]+=sum*A[j].v;
        }
    }
    i=l,j=m+1;
    ll k=l;
    while(i<=m&&j<=r) tmp[k++]=A[i].y<=A[j].y?A[i++]:A[j++];
    while(i<=m) tmp[k++]=A[i++];
    while(j<=r) tmp[k++]=A[j++];
    for(k=l;k<=r;k++) A[k]=tmp[k];
}

void cdq(ll l,ll r){
    if(l==r) return;
    ll m=l+r>>1;
    cdq(l,m);
    cdq(m+1,r);
    merge(l,m,r);
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        ll x,y,v;
        cin>>x>>y>>v;
        A[++cnt]={1,x,y,v};
    }
    for(ll i=1;i<=m;i++){
        ll x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        A[++cnt]={2,x2,y2,1,i};
        A[++cnt]={2,x1-1,y1-1,1,i};
        A[++cnt]={2,x1-1,y2,-1,i};
        A[++cnt]={2,x2,y1-1,-1,i};
    }
    sort(A+1,A+cnt+1,[&](const Node& u,const Node& v){
        return u.x^v.x?u.x<v.x:u.typ<v.typ;
    });
    cdq(1,cnt);
    for(ll i=1;i<=m;i++){
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