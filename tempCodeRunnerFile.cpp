#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define INF (LLONG_MAX/2)
#define EPS (1e-20)
typedef long long int;
typedef __int128 i128;
typedef long double ld;
typedef pair<int,int> pint;
typedef array<int,3> al3;
typedef vector<int> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const int N=3e5+5;
const int V=1e6+5;
int n,m,v;

struct Node{
    int typ;
    int x,y;
    int id;
};

Node A[N<<1],B[N<<1]; int cnt;
int ans[N]; int cnt_ans;

int tr[V];

void fw_update(int x,int v){
    while(x<=v){
        chmax(tr[x],v);
        x+=x&-x;
    }
}

int fw_query(int x){
    int res=-INF;
    while(x>0){
        chmax(res,tr[x]);
        x&=x-1;
    }
    return res;
}

void fw_clear(int x){
    while(x<=v){
        tr[x]=-INF;
        x+=x&-x;
    }
}

void merge(int l,int m,int r){
    int i,j;
    for(i=l,j=m+1;j<=r;j++){
        while(i<=m&&A[i].x<=A[j].x){
            if(A[i].typ==1){
                fw_update(A[i].y,A[i].x+A[i].y);
            }
            i++;
        }
        if(A[j].typ==2){
            chmin(ans[A[j].id],A[j].x+A[j].y-fw_query(A[j].y));
        }
    }
    for(int k=l;k<i;k++){
        if(A[k].typ==1){
            fw_clear(A[k].y);
        }
    }
    sort(A+l,A+r+1,[&](const auto& u,const auto& v){
        return u.x<v.x;
    });
}

void cdq(int l,int r){
    if(l==r) return;
    int m=l+r>>1;
    cdq(l,m);
    cdq(m+1,r);
    merge(l,m,r);
}

void to1(){
    copy(B+1,B+cnt+1,A+1);
    cdq(1,cnt);
}

void to2(){
    copy(B+1,B+cnt+1,A+1);
    for(int i=1;i<=cnt;i++){
        A[i].x=-A[i].x+v;
    }
    cdq(1,cnt);
}

void to3(){
    copy(B+1,B+cnt+1,A+1);
    for(int i=1;i<=cnt;i++){
        A[i].x=-A[i].x+v;
        A[i].y=-A[i].y+v;
    }
    cdq(1,cnt);
}

void to4(){
    copy(B+1,B+cnt+1,A+1);
    for(int i=1;i<=cnt;i++){
        A[i].y=-A[i].y+v;
    }
    cdq(1,cnt);
}

void solve(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        x++,y++;
        B[++cnt]={1,x,y};
        chmax(v,x);
        chmax(v,y);
    }
    for(int i=1;i<=m;i++){
        int op,x,y;
        cin>>op>>x>>y;
        x++,y++;
        B[++cnt]={op,x,y};
        if(op==2){
            B[cnt].id=++cnt_ans;
        }
        chmax(v,x);
        chmax(v,y);
    }
    v++;
    for(int i=1;i<V;i++) tr[i]=-INF;
    for(int i=1;i<=cnt_ans;i++) ans[i]=INF;
    to1();
    to2();
    to3();
    to4();
    for(int i=1;i<=cnt_ans;i++){
        cout<<ans[i]<<endl;
    }
}

void clear(){}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T=1;
    //cin>>T;
    while(T--){
        solve();
        clear();
    }
    return 0;
}