//https://www.luogu.com.cn/problem/P4288
//@@@ 
//minimum enclosing circle
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

template<class T1,class T2>
bool chmin(T1& x,const T2& y){ return y<x?x=y,1:0; }

template<class T1,class T2>
bool chmax(T1& x,const T2& y){ return y>x?x=y,1:0; }

#define PI (acosl(-1.0l))

ld deg2rad(ld deg){
    return deg*PI/180.0l;
}

using Vec=struct Point{
    ld x,y;
    Point(ld x_=0,ld y_=0): x(x_), y(y_){}
    Point operator+(const Point& o) const{ return Point(x+o.x,y+o.y); }
    Point operator-(const Point& o) const{ return Point(x-o.x,y-o.y); }
    ld operator&(const Point& o) const{ return x*o.x+y*o.y; }// dot
    ld operator*(const Point& o) const{ return x*o.y-y*o.x; }// cross
    Point operator*(const ld& k) const{ return {k*x,k*y}; }
    Point operator/(const ld& k) const{ return {x/k,y/k}; }
    bool operator==(const Point& o) const{ return x==o.x&&y==o.y; }
    bool operator<(const Point& o) const{ return x!=o.x?x<o.x:y<o.y; }
    ld len() const{ return sqrtl((*this)&(*this)); }

    Point norm() const{
        ld L=len();
        return L?(*this)/L:*this;
    }
};

Vec dir(Point a,Point b){ return b-a; }
ld dis(Point a,Point b){ return dir(a,b).len(); }

using Segment=struct Line{
    Point s,t;
    Line(Point _s=Point(),Point _t=Point()): s(_s), t(_t){}
    ld theta() const{ return atan2l(t.y-s.y,t.x-s.x); }
};

ld cross(Point a,Point b,Point c){ return dir(a,b)*dir(a,c); }

Point intersection(const Line& L,const Line& J){
    Vec u=L.s-J.s;
    Vec v=L.t-L.s;
    Vec w=J.t-J.s;
    ld k=(u*w)/(w*v);
    return L.s+v*k;
}

Vec rotate(Vec a,ld beta){
    return {a.x*cosl(beta)-a.y*sinl(beta),a.x*sinl(beta)+a.y*cosl(beta)};
}

struct Circle{
    Point c;
    ld r;
    Circle(Point c_=Point(),ld r_=0): c(c_), r(r_){}
};

Line midperp(Point a,Point b){
    Point m=(a+b)/2;
    return {m,m+rotate(dir(a,b), PI/2)};
}

struct minimum_enclosing_circle{
    vector<Point> A;
    minimum_enclosing_circle(const vector<Point>& _A): A(_A){}

    Circle cover(Point a,Point b){
        return Circle((a+b)/2,dis(a,b)/2);
    }

    Circle cover(Point a,Point b,Point c){
        //共线时退化为最长边的两点圆,避免中垂线平行
        if(fabsl(cross(a,b,c))<EPS){
            ld ab=dis(a,b),ac=dis(a,c),bc=dis(b,c);
            if(ab>=ac&&ab>=bc) return cover(a,b);
            if(ac>=ab&&ac>=bc) return cover(a,c);
            return cover(b,c);
        }
        auto mp1=midperp(a,b);
        auto mp2=midperp(a,c);
        Point o=intersection(mp1,mp2);
        return Circle(o,dis(o,a));
    }

    Circle solve(){
        ll n=(ll)A.size();
        mt19937_64 rng(random_device{}());
        shuffle(A.begin(),A.end(),rng);

        Circle C(A[0],0);
        for(ll i=1;i<n;i++){
            if(C.r+EPS<dis(C.c,A[i])){
                C=Circle(A[i],0);
                for(ll j=0;j<i;j++){
                    if(C.r+EPS<dis(C.c,A[j])){
                        C=cover(A[i],A[j]);
                        for(ll k=0;k<j;k++){
                            if(C.r+EPS<dis(C.c,A[k])){
                                C=cover(A[i],A[j],A[k]);
                            }
                        }
                    }
                }
            }
        }
        return C;
    }
};

void solve(){
    ll n;
    cin>>n;
    vector<Point> A(n);
    for(auto& [x,y]:A){
        cin>>x>>y;
    }
    ld a,b;
    cin>>a>>b;
    ld ang=-deg2rad(a);
    for(auto& pt:A){
        pt=rotate(pt,ang);
        pt.x/=b;
    }
    minimum_enclosing_circle solver(A);
    Circle C=solver.solve();
    cout<<fixed<<setprecision(3)<<C.r<<endl;
}

void clear(){}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
        clear();
    }
    return 0;
}
