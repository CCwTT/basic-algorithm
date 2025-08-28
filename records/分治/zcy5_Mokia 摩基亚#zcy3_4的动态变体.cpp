//https://www.luogu.com.cn/problem/P4390
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

const ll V=2e6+5;
ll tr[V];

void fw_update(ll x,ll v){
    while(x<V){
        tr[x]+=v;
        x+=x&-x;
    }
}

ll fw_query(ll x){
    ll res=0;
    while(x){
        res+=tr[x];
        x-=x&-x;
    }
    return res;
}

const ll N=2e5+5;
ll n;

struct Node{
    ll typ;
    ll x,y,v;
    ll id;
};

Node A[N]; ll cnt=0;
ll ans[N]; ll cnt_ans=0;

void merge(ll l,ll m,ll r){
    ll i,j;
    for(i=l,j=m+1;j<=r;j++){
        while(i<=m&&A[i].x<=A[j].x){
            if(A[i].typ==1){
                fw_update(A[i].y,A[i].v);
            }
            i++;
        }
        if(A[j].typ==2){
            ans[A[j].id]+=A[j].v*fw_query(A[j].y);
        }
    }
    for(ll k=l;k<i;k++){
        if(A[k].typ==1){
            fw_update(A[k].y,-A[k].v);
        }
    }
    sort(A+l,A+r+1,[&](const auto& u,const auto& v){
        return u.x<v.x;
    });
}

void cdq(ll l,ll r){
    if(l==r) return;
    ll m=l+r>>1;
    cdq(l,m);
    cdq(m+1,r);
    merge(l,m,r);
}

void solve(){
    ll tmp;
    cin>>tmp>>n;
    ll op;
    while(cin>>op&&op!=3){
        if(op==1){
            ll x,y,v;
            cin>>x>>y>>v;
            A[++cnt]={1,x,y,v};
        }else{
            ll x1,y1,x2,y2;
            cin>>x1>>y1>>x2>>y2;
            A[++cnt]={2,x2,y2,1,++cnt_ans};
            A[++cnt]={2,x1-1,y1-1,1,cnt_ans};
            A[++cnt]={2,x1-1,y2,-1,cnt_ans};
            A[++cnt]={2,x2,y1-1,-1,cnt_ans};
        }
    }
    cdq(1,cnt);
    for(ll i=1;i<=cnt_ans;i++){
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