//https://www.luogu.com.cn/problem/P1429
//@@@ 
//closest pair of points(divide and conquer)
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
#define EPS (1e-20)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){ return y<x?x=y,1:0; }
template<class T1,class T2> bool chmax(T1& x,const T2& y){ return y>x?x=y,1:0; }

const ll N=200010;

using Vec=struct Point{
    ld x,y;
};

ld dis(const Point& a,const Point& b){
    return sqrtl((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
vector<Point> A;

ld dfs(ll l,ll r){
    if(l==r) return INF;
    if(l+1==r) return dis(A[l],A[r]);
    ll m=l+r>>1;
    ld d=min(dfs(l,m),dfs(m+1,r));
    vector<Point> B;
    for(ll i=l;i<=r;i++){
        if(fabsl(A[i].x-A[m].x)<d) B.push_back(A[i]);
    }
    sort(B.begin(),B.end(),[](const Point& u,const Point& v){
        return u.y<v.y;
    });
    for(ll i=0;i<B.size();i++){
        for(ll j=i+1;j<B.size()&&(B[j].y-B[i].y)<d;j++){
            chmin(d,dis(B[i],B[j]));
        }
    }
    return d;
}

void solve(){
    ll n;
    cin>>n;
    for(ll i=1;i<=n;i++){
        ld x,y;
        cin>>x>>y;
        A.push_back({x,y});
    }
    sort(A.begin(),A.end(),[](const Point& u,const Point& v){
        return u.x!=v.x?u.x<v.x:u.y<v.y;
    });
    ld ans=dfs(0,n-1);
    cout<<fixed<<setprecision(4)<<ans<<'\n';
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
