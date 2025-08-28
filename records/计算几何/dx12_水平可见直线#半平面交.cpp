//https://www.luogu.com.cn/problem/P3194
//@@@ 
//half plane intersection
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

#define PI (acos(-1.0L))

using Vec=struct Point{
    ld x,y;
    Point(ld x_=0,ld y_=0): x(x_), y(y_){}
    Point operator+(const Point& o) const{ return {x+o.x,y+o.y}; }
    Point operator-(const Point& o) const{ return {x-o.x,y-o.y}; }
    ld operator&(const Point& o) const{ return x*o.x+y*o.y; }//dot
    ld operator*(const Point& o) const{ return x*o.y-y*o.x; }//cross
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

struct Line{
    Point s,t;
    ll id;
    Line(Point _s=0,Point _t=0,ll _id=0): s(_s), t(_t), id(_id){}
    ld theta() const{ return atan2l(t.y-s.y,t.x-s.x); }// 极角(-pi,pi]
};

Vec dir(Point a,Point b){ return b-a; }
ld cross(Point a,Point b,Point c){ return dir(a,b)*dir(a,c); }
ld cross(Line L,Point p){ return cross(L.s,L.t,p); }
ld dot(Point a,Point b,Point c){ return dir(a,b)&dir(a,c); }


// 你指定的交点实现
Point intersection(const Line& L,const Line& J){// 直线交点
    Vec u=L.s-J.s;
    Vec v=L.t-L.s;
    Vec w=J.t-J.s;
    ld t=(u*w)/(w*v);
    return L.s+v*t;
}

vector<Line> half_plane_intersect(vector<Line>& lines){
    if(lines.empty()) return {};

    sort(lines.begin(),lines.end(),[](const Line& u,const Line& v){
        if(fabsl(u.theta()-v.theta())>EPS) return u.theta()<v.theta();
        return cross(u.s,u.t,v.s)<0;
    });

    deque<Line> dq;
    dq.push_back(lines[0]);
    for(ll i=1;i<lines.size();i++){
        if(fabsl(lines[i].theta()-lines[i-1].theta())<EPS) continue;
        while(dq.size()>1&&cross(lines[i],intersection(dq.back(),dq[(ll)dq.size()-2]))<=0) dq.pop_back();
        while(dq.size()>1&&cross(lines[i],intersection(dq.front(),dq[1]))<=0) dq.pop_front();
        dq.push_back(lines[i]);
    }
    while(dq.size()>2&&cross(dq.front(),intersection(dq.back(),dq[(ll)dq.size()-2]))<=0) dq.pop_back();
    return vector<Line>(dq.begin(),dq.end());
}


void solve(){
    ll n;
    cin>>n;
    vector<Line> lines;
    for(int i=1;i<=n;i++){
        ld A,B; //y=Ax+B
        cin>>A>>B;
        Point p0(0,B),p1(1,A+B);
        lines.emplace_back(p0,p1,i);
    }
    auto ans=half_plane_intersect(lines);
    sort(ans.begin(),ans.end(),[](const Line& u,const Line& v){
        return u.id<v.id;
    });
    for(auto [s,t,id]:ans){
        cout<<id<<" ";
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
