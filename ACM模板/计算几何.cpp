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

using Vec=struct Point{
    ll x,y;
    Point(ll x_=0,ll y_=0):x(x_),y(y_){}
    Point operator+(const Point& o) const{
        return Point(x+o.x,y+o.y);
    }
    Point operator-(const Point& o) const{
        return Point(x-o.x,y-o.y);
    }
    ll operator&(const Point& o) const{
        return x*o.x+y*o.y;
    }
    ll operator*(const Point& o) const{
        return x*o.y-y*o.x;
    }
    Point operator*(const ll& k) const{
        return {k*x,k*y};
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
    ll len(){
        return (ll)sqrt(*this&*this);
    }
    Point norm(){
        return len()?(*this)/len():*this;
    }
};
Vec dir(Point a,Point b){
    return b-a;
}

ll dis2(Point a,Point b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

//a
ll cross(Point a,Point b,Point c){
    return dir(a,b)*dir(a,c);
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

using Segment=struct Line{
    Point p1,p2;
};

bool intersect_ls(Line a,Segment b){
    return cross(a.p1,a.p2,b.p1)*cross(a.p1,a.p2,b.p2)<=0;
}

bool intersect_ll(Line a,Line b){
    return intersect_ls(a,b)||intersect_ls(b,a);
}

bool intersect_ss(Segment a,Segment b){
    return intersect_ls(a,b)&&intersect_ls(b,a);
}

vector<Point> convex_hull(vector<Point> A){
    ll n=A.size();
    if(n<=2) return A;
    vector<Point> res(n*2);
    sort(A.begin(),A.end());
    ll cnt=-1;
    for(ll i=0;i<n;i++){
        while(cnt>0&&cross(res[cnt-1],res[cnt],A[i])<=0){
            cnt--;
        }
        res[++cnt]=A[i];
    }
    ll pre=cnt;
    for(ll i=n-2;i>=0;i--){
        while(cnt>pre&&cross(res[cnt-1],res[cnt],A[i])<=0){
            cnt--;
        }
        res[++cnt]=A[i];
    }
    res.resize(cnt);
    return res;
}

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