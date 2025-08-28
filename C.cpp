//https://www.luogu.com.cn/problem/P4196
//@@@ 
//half plane intersection,triangulation
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define INF (LLONG_MAX/2)
#define EPS (1e-12)
typedef long long ll;
typedef __int128 i128;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){ return y<x?x=y,1:0; }
template<class T1,class T2> bool chmax(T1& x,const T2& y){ return y>x?x=y,1:0; }

#define PI (acos(-1.0L))

using Vec=struct Point{
    ld x,y;
    Point(ld x_=0,ld y_=0): x(x_), y(y_){}
    Point operator+(const Point& o) const{ return {x+o.x,y+o.y}; }
    Point operator-(const Point& o) const{ return {x-o.x,y-o.y}; }
    ld operator&(const Point& o) const{ return x*o.x+y*o.y; }
    ld operator*(const Point& o) const{ return x*o.y-y*o.x; }
    Point operator*(const ld& k) const{ return {x*k,y*k}; }
    Point operator/(const ld& k) const{ return {x/k,y/k}; }
    bool operator==(const Point& o) const{ return x==o.x&&y==o.y; }
    bool operator<(const Point& o) const{ return x!=o.x?x<o.x:y<o.y; }
    ld len() const{ return sqrtl((*this)&(*this)); }
    Point norm() const{
        return len()?(*this)/len():*this;
    }
};

struct Line{
    Point s,t;
    Line(Point s_=0,Point t_=0): s(s_), t(t_){}
    ld theta() const{ return atan2l(t.y-s.y,t.x-s.x); }
};

Vec dir(Point a,Point b){ return b-a; }
ld cross(Point a,Point b,Point c){ return dir(a,b)*dir(a,c); }
ld cross(Line L,Point c){ return dir(L.s,L.t)*dir(L.s,c); }
ld dot(Point a,Point b,Point c){ return dir(a,b)&dir(a,c); }

Point intersection(const Line& A,const Line& B){ //直线交点
    Vec u=A.s-B.s;
    Vec v=A.t-A.s;
    Vec w=B.t-B.s;
    ld t=(u*w)/(w*v);
    return A.s+v*t;
}

//半平面交:输入所有半平面(以有向边表示左侧为可行域),输出交多边形面积
vector<Line> half_plane_intersect(vector<Line>& lines){
    if(lines.empty()) return {};

    sort(lines.begin(),lines.end(),[](const Line& u,const Line& v){
        if(fabsl(u.theta()-v.theta())>EPS) return u.theta()<v.theta();
        return cross(u.s,u.t,v.s)<0;
    });

    deque<Line> dq;
    dq.push_back(lines[0]);
    for(size_t i=1;i<lines.size();i++){
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
    for(ll _=0;_<n;_++){
        ll m;
        cin>>m;
        vector<Point> pts(m);
        for(ll i=0;i<m;i++){
            ld x,y;
            cin>>x>>y;
            pts[i]={x,y};
        }
        for(ll i=0;i<m;i++){
            lines.emplace_back(pts[i],pts[(i+1)%m]);
        }
    }
    auto tab=half_plane_intersect(lines);
    
    if(tab.size()<3){
        cout<<"0.000"<<endl;
        return;
    }
    
    //计算交多边形顶点(按队列顺序,两两相交,首尾相接)
    vector<Point> poly;
    poly.reserve(tab.size());
    for(size_t i=0;i<tab.size();i++){
        poly.push_back(intersection(tab[i], tab[(i+1)%tab.size()]));
    }
    
    //多边形面积(以首点为参考三角剖分),保持原有"有符号面积"返回
    ld ans=0;
    for(ll i=1;i+1<poly.size();i++){
        ans+=cross(poly[i],poly[i+1],poly[0])/2;
    }
    cout<<fixed<<setprecision(3)<<ans<<endl;
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