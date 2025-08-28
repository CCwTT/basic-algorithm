//https://www.luogu.com.cn/problem/P2163
//@@@ 
//cdq(2-dimensional)
//对答案有贡献的(i,j): xi<=xj && yi<=yj 
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

template<class T1,class T2>
bool chmin(T1& x,const T2& y){ return y<x?x=y,1:0; }

template<class T1,class T2>
bool chmax(T1& x,const T2& y){ return y>x?x=y,1:0; }

struct Node{
    int typ;// was op
    int x;
    int y;
    int w;// was v
    int id;// was q
};

const int MAXN=5e5*5+5;
int n,m;
Node A[MAXN];
int cnt=0;
Node tmp[MAXN];
int ans[MAXN];

void merge(int l,int m,int r){
    int i=l-1,j,sum=0;
    for(j=m+1;j<=r;j++){
        while(i+1<=m&&A[i+1].y<=A[j].y){
            i++;
            if(A[i].typ==1){
                sum++;
            }
        }
        if(A[j].typ==2){
            ans[A[j].id]+=sum*A[j].w;
        }
    }
    i=l,j=m+1;
    int k=l;
    while(i<=m&&j<=r){
        tmp[k++]=A[i].y<=A[j].y?A[i++]:A[j++];
    }
    while(i<=m){
        tmp[k++]=A[i++];
    }
    while(j<=r){
        tmp[k++]=A[j++];
    }
    for(int t=l;t<=r;t++){
        A[t]=tmp[t];
    }
}

void cdq(int l,int r){
    if(l==r){
        return;
    }
    int mid=(l+r)/2;
    cdq(l,mid);
    cdq(mid+1,r);
    merge(l,mid,r);
}

void solve(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        A[++cnt]={1,x,y};
    }
    for(int i=1;i<=m;i++){
        int x1,y1,x2,y2;
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
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<'\n';
    }
}

void clear(){}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
        clear();
    }
    return 0;
}
