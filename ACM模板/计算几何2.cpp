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

#define PI (acos(-1.0))

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
    bool operator==(const Point& o) const{
        return x==o.x&&y==o.y;
    }
    bool operator<(const Point& o) const{
        return x!=o.x?x<o.x:y<o.y;
    }
    ld len(){
        return sqrt(*this&*this);
    }
    Point norm(){
        return len()?(*this)/len():*this;
    }
};

Vec dir(Point a,Point b){
    return b-a;
}

ld dis(Point a,Point b){
    return dir(a,b).len();
}

using Segment=struct Line{
    Point s,t;
    Line(Point _s=0,Point _t=0):s(_s),t(_t) {}
    ld theta() const{
        return atan2(t.y-s.y,t.x-s.x);
    }
};

ld cross(Point a,Point b,Point c){
    return dir(a,b)*dir(a,c);
}

ld cross(Line L,Point p){
    return dir(L.s,L.t)*dir(L.s,p);
}

ld dot(Point a,Point b,Point c){
    return dir(a,b)&dir(a,c);
}

bool collinear(Point a,Point b,Point c){
    return cross(a,b,c)==0;
}

ld dir_ang(Vec a,Vec b){
	return atan2(a*b,a&b);
}

ld inc_ang(Vec a,Vec b){
    return acos((a&b)/a.len()/b.len());
}

/*
ld dir_ang(Vec a,Vec b){
	ld res=inc_ang(a,b);
    if(a*b<0) res=-res;
    return res;
}
    
ld inc_ang(Vec a,Vec b){
    return fabsl(dir_ang(a,b));
}
*/


bool intersect_ls(Line a,Segment b){
    return cross(a.s,a.t,b.s)*cross(a.s,a.t,b.t)<=0;
}

bool intersect_ll(Line a,Line b){
    return intersect_ls(a,Segment(b))||intersect_ls(b,Segment(a));
}

bool intersect_ss(Segment a,Segment b){
    return intersect_ls(Line(a),b)&&intersect_ls(Line(b),a);
}

Point intersection(const Line& L,const Line& J){ //直线交点
    Vec u=L.s-J.s;
    Vec v=L.t-L.s;
    Vec w=J.t-J.s;
    ld t=(u*w)/(w*v);
    return L.s+v*t;
}

Vec rotate(Vec a,ld beta){  //逆转角
    return {a.x*cos(beta)-a.y*sin(beta),a.x*sin(beta)+a.y*cos(beta)};
}

bool on_segment(Point p,Segment seg){//p在线段seg上
    auto [a,b]=seg;
    return fabsl(dir(p,a)*dir(p,b))<EPS&&(dir(p,a)&dir(p,b))<=0;
}

Line midperp(Point a,Point b){
    return {(a+b)/2,(a+b)/2+rotate(dir(a,b),PI/2)};
}

struct Circle{
    Point c;
    ld r;
    Circle(Point c_=Point(),ld r_=0): c(c_), r(r_){}
};

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
        while(dq.size()>1&&cross(lines[i],intersection(dq.back(),dq[(ll)dq.size()-2]))<=0/*<0*/) dq.pop_back();
        while(dq.size()>1&&cross(lines[i],intersection(dq.front(),dq[1]))<=0/*<0*/) dq.pop_front();
        dq.push_back(lines[i]);
    }
    while(dq.size()>2&&cross(dq.front(),intersection(dq.back(),dq[(ll)dq.size()-2]))<=0) dq.pop_back();
    return vector<Line>(dq.begin(),dq.end());
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