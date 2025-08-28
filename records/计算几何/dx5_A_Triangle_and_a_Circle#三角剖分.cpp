//http://poj.org/problem?id=2986
//@@@ 
//triangulation
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
#define EPS (1e-20)
#define PI (acos(-1.0))
typedef long long ll;
//typedef __int128 i128;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;

template<class T1,class T2>
bool chmin(T1& x,const T2& y){ return y<x?x=y,1:0; }

template<class T1,class T2>
bool chmax(T1& x,const T2& y){ return y>x?x=y,1:0; }

using Vec=struct Point{
    ld x,y;
    Point(ld x_=0,ld y_=0):x(x_), y(y_){}
    Point operator+(const Point& o) const{
        return Point(x+o.x,y+o.y);
    }
    Point operator-(const Point& o) const{
        return Point(x-o.x,y-o.y);
    }
    ld operator&(const Point& o) const{
        return x*o.x+y*o.y;
    }
    ld operator*(const Point& o) const{
        return x*o.y-y*o.x;
    }
    Point operator*(const ld& k) const{
        return {k*x,k*y};
    }
    Point operator/(const ld& k) const{
        return {x/k,y/k};
    }
    ld len(){
        return sqrt(*this&*this);
    }
    Point norm(){
        return (*this)/len();
    }
};
Vec dir(Point a,Point b){
    return b-a;
}
ld dis(Point a,Point b){
    return dir(a,b).len();
}

using Segment=struct Line{
    Point p1,p2;
};

ld R;
Point pts[4],o;//顶点和圆心

// Point intersection(Line a,Line b){
//     Point p1=a.p1,p2=b.p1;
//     Vec v1=dir(a.p1,a.p2),v2=dir(b.p1,b.p2);
//     ld k=dir(p2,p1)*v2/(v2*v1);
//     return p1+v1*k;
// }

Point intersection(Line a,Line b){
    Point u=a.p1-b.p1;
    Point v=a.p2-a.p1;
    Point w=b.p2-b.p1;
    ld k=(u*w)/(w*v);
    return a.p1+v*k;
}


Vec rotate(Vec a,ld ang){  //逆转角
    return {a.x*cos(ang)-a.y*sin(ang),a.x*sin(ang)+a.y*cos(ang)};
}

bool on_segment(Point p,Segment seg){//p在线段seg上
    auto [a,b]=seg;
    return fabsl(dir(p,a)*dir(p,b))<EPS&&(dir(p,a)&dir(p,b))<=0;
}

ld dir_ang(Vec a,Vec b){
	return atan2(a*b,a&b);
}

tuple<ld,Point,Point> get(Point a,Point b){
    Point e=intersection({a,b},{o,o+rotate(dir(a,b),PI/2)});//垂足
    ld d=dis(o,e);
    if(!on_segment(e,{a,b})) d=min(dis(o,a),dis(o,b));
    if(R<=d) return {d,Point{},Point{}};//线段在圆外
    ld len=sqrt(R*R-dis(o,e)*dis(o,e));
    Point pa=e+dir(b,a).norm()*len;
    Point pb=e+dir(a,b).norm()*len;//pa,pb:线段与圆的两交点
    return {d,pa,pb};//d:圆心到线段的最近距离
}

ld sector(Point a,Point b){//扇形面积
    ld ang=dir_ang(a,b);//[0,Pi]
    return R*R*ang/2;
}

ld get_area(Point a,Point b){//面积的交
    if(fabsl(a*b)<EPS) return 0;//共线
    ld da=dis(o,a),db=dis(o,b);
    if(R>=da&&R>=db) return a*b/2;//ab在圆内
    // Point pa,pb;
    auto [d,pa,pb]=get(a,b);//d:圆心到线段的最近距离
    if(R<=d) return sector(a,b);//ab在圆外
    if(R>=da) return a*pb/2+sector(pb,b);//a在圆内
    if(R>=db) return sector(a,pa)+pa*b/2;//b在圆内
    return sector(a,pa)+pa*pb/2+sector(pb,b);//ab是割线
}

void solve(){
    cout<<fixed<<setprecision(2);
    while(cin>>pts[0].x>>pts[0].y>>pts[1].x>>pts[1].y>>pts[2].x>>pts[2].y>>o.x>>o.y>>R){
        for(ll i=0;i<3;i++) pts[i].x-=o.x,pts[i].y-=o.y;//三角形顶点平移
        o=Point(0,0);//圆心平移到原点
        ld res=0;
        for(ll i=0;i<3;i++) res+=get_area(pts[i],pts[(i+1)%3]);
        cout<<fabsl(res)<<endl;//点可能顺时针
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

