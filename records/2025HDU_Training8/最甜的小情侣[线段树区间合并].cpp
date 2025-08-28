//https://acm.hdu.edu.cn/contest/view-code?cid=1179&rid=13277
//@@@
//segment tree(interval coalescing)
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll N=1e6+10;
const ll MOD=998244353;

ll tr[N][4][4];
ll a[N],n,q;

void up(ll p,ll l,ll r){
    ll mid=l+r>>1;
    ll lenl=mid-l+1,lenr=r-mid,len=r-l+1;
    for(ll i=0;i<=3;i++){
        for(ll j=0;j<=3;j++){ 
            tr[p][i][j]=0;
        }
    }
    for(ll i=0;i<=min(3ll,lenl);i++){
        for(ll j=0;j<=min(3ll,lenr);j++){
            if(i==lenl&&j==lenr){
                if(i+j<=3)
                    tr[p][i+j][i+j]=tr[p<<1][i][i]+tr[p<<1|1][j][j];
                continue;
            }
            if(i==lenl){
                for(ll k=0;k<=min(3-i,lenr);k++)
                    tr[p][i+k][j]=max(tr[p][i+k][j],tr[p<<1][i][i]+tr[p<<1|1][k][j]);
                continue;
            }
            if(j==lenr){
                for(ll k=0;k<=min(3-j,lenl);k++)
                    tr[p][i][j+k]=max(tr[p][i][j+k],tr[p<<1][i][k]+tr[p<<1|1][j][j]);
                continue;
            }
            ll mx=0;
            for(ll k=3;k>=0;k--){
                mx=max(mx,tr[p<<1|1][3-k][j]);
                tr[p][i][j]=max(tr[p][i][j],tr[p<<1][i][k]+mx);
            }
        }
    }
}

void build(ll p,ll l,ll r){
    if(l==r){
        tr[p][1][1]=a[l];
        return;
    }
    ll m=l+r>>1;
    build(p<<1,l,m);
    build(p<<1|1,m+1,r);
    up(p,l,r);
}

void update(ll p,ll l,ll r,ll x,ll v){
    if(l==r){
        tr[p][1][1]=v;
        a[l]=v;
        return;
    }
    ll m=l+r>>1;
    if(x<=m) update(p<<1,l,m,x,v);
    else update(p<<1|1,m+1,r,x,v);
    up(p,l,r);
}


ll get_ans(){
    ll res=0;
    if(n<=3){
        for(ll i=1;i<=n;i++){
            res+=a[i];
        }
        return res;
    }
    for(ll i=0;i<=3;i++){
        for(ll j=0;j<=3;j++){
            if(i+j>3) continue;
            res=max(res,tr[1][i][j]);
        }
    }
    return res;
}

void solve(){
    cin>>n>>q;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    cout<<get_ans()<<endl;
    while(q--){
        ll x,v;
        cin >> x >> v;
        update(1,1,n,x,v);
        cout<<get_ans()<<endl;
    }
    for(ll i=0;i<=4*n;i++){
        for(ll x=0;x<=3;x++){
            for(ll y=0;y<=3;y++){
                tr[i][x][y]=0;
            }
        }
    }
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