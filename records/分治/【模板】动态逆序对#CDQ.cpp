//https://www.luogu.com.cn/problem/P3157
//@@@ 
//cdq
//analysis:对答案有贡献的点对(i,j):
// ti<tj && pi<pj && vi>vj 或 ti<tj && pi>pj && vi<vj
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
    ll t,p,v,w; // 时间,位置,值,单位贡献
};

const ll N=1e5+5;
const ll M=5e4+5;
ll n,m;

ll a[N];      
ll pos[N];
ll b[M];      

Node c[N+M]; 
ll cnt=0;
ll tr[N];
ll ans[M];

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

void merge(ll l,ll m,ll r){
    ll i=l-1;
    for(ll j=m+1;j<=r;j++){
        while(i+1<=m&&c[i+1].p<c[j].p){
            i++;
            fw_update(c[i].v,c[i].w);
        }
        ans[c[j].t]+=c[j].w*(fw_query(n)-fw_query(c[j].v));
    }
    for(ll k=l;k<=i;k++){
        fw_update(c[k].v,-c[k].w);
    }
    i=m+1;
    for(ll j=r;j>m;j--){
        while(i-1>=l&&c[i-1].p>c[j].p){
            i--;
            fw_update(c[i].v,c[i].w);
        }
        ans[c[j].t]+=c[j].w*fw_query(c[j].v-1);
    }
    for(ll k=m;k>=i;k--){
        fw_update(c[k].v,-c[k].w);
    }
    sort(c+l,c+r+1,[&](const Node&x,const Node&y){
        return x.p<y.p;
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
    for(ll i=1;i<=n;i++){
        cnt++;
        c[cnt]={0,i,a[i],1}; 
    }
    for(ll i=1;i<=m;i++){
        cnt++;
        c[cnt]={i,pos[b[i]],b[i],-1};
    }
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        cin>>a[i];       
        pos[a[i]]=i;
    }
    for(ll i=1;i<=m;i++){
        cin>>b[i];      
    }
    prepare();
    cdq(1,cnt);
    for(ll i=1;i<m;i++){
        ans[i]+=ans[i-1];
    }
    for(ll i=0;i<m;i++){
        cout<<ans[i]<<'\n';
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