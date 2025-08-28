//http://poj.org/problem?id=1106
//point-line-relations
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
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll N=155;
using Vec=struct Point{
    ll x,y;
    Point operator-(const Point& o) const{
        return {x-o.x,y-o.y};
    }
};
Point pts[N],o,a;

Vec dir(Point a,Point b){
    return b-a;
}

ll cross(Vec a,Vec b){
    return a.x*b.y-a.y*b.x;
}

ll cross(Point a,Point b,Point c){
    return cross(dir(a,b),dir(a,c));
}

ll dis2(Point a,Point b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

void solve(){
    ll n,m,ans;
    double r;
    while(cin>>o.x>>o.y>>r&&r>=0){
        cin>>m;
        n=ans=0;
        while(m--){
            cin>>a.x>>a.y;
            if(dis2(o,a)<=r*r) pts[++n]=a;
        }
        for(ll i=1;i<=n;i++){
            ll cur=0;
            for(ll j=1;j<=n;j++){
                if(cross(o,pts[i],pts[j])>=0) cur++;
            }
            chmax(ans,cur);
        }
        cout<<ans<<endl;
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