//https://acm.hdu.edu.cn/contest/problem?cid=1180&pid=1005
//@@@
//computational geometry,convex hull,collinear
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

using Vec=struct Point{
    ll x,y,id;
    Point(ll x_=0,ll y_=0):x(x_),y(y_){}
    Point operator+(const Point& o) const{
        return Point(x+o.x,y+o.y);
    }
    Point operator-(const Point& o) const{
        return Point(x-o.x,y-o.y);
    }
    bool operator<(const Point& o) const{
        return x==o.x?y<o.y:x<o.x;
    }
};

Point dir(Point a,Point b){
    return b-a;
}

ll cross(Vec a,Vec b){
    return a.x*b.y-a.y*b.x;
}

ll cross(Point a,Point b,Point c){
    return cross(dir(a,b),dir(a,c));
}

bool collinear(Point a,Point b,Point c){
    return cross(a,b,c)==0;
}

vector<Point> convex_hull(vector<Point> A){
    ll n=A.size();
    if(n<=2) return A;
    vector<Point> res(n*2);
    sort(A.begin(),A.end());
    ll cnt=-1;
    for(ll i=0;i<n;i++){
        while(cnt>0&&cross(A[i],res[cnt],res[cnt-1])<=0){
            cnt--;
        }
        res[++cnt]=A[i];
    }
    ll pre=cnt;
    for(ll i=n-2;i>=0;i--){
        while(cnt>pre&&cross(A[i],res[cnt],res[cnt-1])<=0){
            cnt--;
        }
        res[++cnt]=A[i];
    }
    res.resize(cnt);
    return res;
}

void solve(){
    ll n;
    cin>>n;
    auto pts=vector<Point>(n);
    vector<ll> mark(n,-1);
    for(int i=0;i<n;i++){
        cin>>pts[i].x>>pts[i].y;
        pts[i].id=i;
    }
    vector<Point> A;
    ll K=n;
    for(ll i=0;i<n;i++){
        if(collinear(pts[(i-1+n)%n],pts[i],pts[(i+1)%n])){
            K--;
        }else{
            A.push_back(pts[i]);
        }
    }
    auto B=A;
    sort(B.begin(),B.end());
    auto hull=convex_hull(A);
    cout<<K<<endl;
    for(ll i=0;i<A.size();i++){
        auto p=A[i];
        auto pp=A[(i-1+A.size())%A.size()];
        auto np=A[(i+1)%A.size()];
        if(cross(dir(pp,p),dir(p,np))>0){
            mark[p.id]=1;
        }else{
            mark[p.id]=0;
        }
    }
    for(auto& poi:B){
        auto [x,y,id]=poi;
        cout<<x<<" "<<y<<" "<<(mark[id]==mark[hull[0].id]?"YES":"NO")<<endl;
    }
}

void clear(){}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
        clear();
    }
    return 0;
}