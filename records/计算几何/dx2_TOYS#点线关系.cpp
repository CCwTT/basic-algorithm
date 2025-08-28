//http://poj.org/problem?id=2318
//point-line-relations
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define INF (LLONG_MAX/2)
#define EPS (1e-20)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll N=5005;
using Vec=struct Point{
    ll x,y;
    Point operator-(const Point& o) const{
        return {x-o.x,y-o.y};
    }
};
Point a[N],b[N];

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

ll n,m;
ll ans[N];

ll find(Point p){
    ll l=0,r=n;
    ll res=0;
    while(l<=r){
        ll mid=l+r>>1;
        if(cross(b[mid],a[mid],p)<=0){
            res=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    return res;
}

void solve(){
    bool flag=0;
    while(cin>>n&&n){
        ll x1,y1,x2,y2;
        cin>>m>>x1>>y1>>x2>>y2;
        a[0]={x1,y1};
        b[0]={x1,y2};
        for(ll i=1;i<=n;i++){
            ll u,l;
            cin>>u>>l;
            a[i]={u,y1};
            b[i]={l,y2};
        }
        memset(ans,0,sizeof(ans));
        while(m--){
            ll x,y;
            cin>>x>>y;
            ans[find({x,y})]++;
        }
        if(flag==0) flag=1;
        else cout<<endl;
        for(ll i=0;i<=n;i++){
            cout<<i<<": "<<ans[i]<<endl;
        }
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