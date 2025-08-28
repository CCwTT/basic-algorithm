//https://www.luogu.com.cn/problem/P1452
//@@@ 
//rotating calipers
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define INF (LLONG_MAX/2)
#define EPS (1e-20)
typedef long long ll;
typedef __int128 i128;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

#define PI (acos(-1.0))

using Vec=struct Point{
    ll x,y;
    Point(ll x_=0,ll y_=0):x(x_), y(y_){}
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
    Point operator/(const ll& k) const{
        return {x/k,y/k};
    }
    bool operator==(const Point& o) const{
        return x==o.x&&y==o.y;
    }
    bool operator<(const Point& o) const{
        return x!=o.x?x<o.x:y<o.y;
    }
    ll len(){
        return sqrt(*this&*this);
    }
    Point norm(){
        return (*this)/len();
    }
};

Vec dir(Point a,Point b){
    return b-a;
}

ll dis2(Point a,Point b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

ll cross(Point a,Point b,Point c){
    return dir(a,b)*dir(a,c);
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

ll rotating_calipers(vector<Point>& A){
    ll n=A.size();
    ll res=0;
    for(ll i=0,j=1;i<n;i++){
        while(cross(A[i],A[(i+1)%n],A[j])<cross(A[i],A[(i+1)%n],A[(j+1)%n])) j=(j+1)%n;
        chmax(res,dis2(A[i],A[j]));
        chmax(res,dis2(A[(i+1)%n],A[j]));
    }
    return res;
}

ll n;

void solve(){
    cin>>n;
    vector<Point> A;
    for(ll i=0;i<n;i++){
        ll x,y;
        cin>>x>>y;
        A.push_back({x,y});
    }
    A=convex_hull(A);
    n=A.size();
    cout<<rotating_calipers(A)<<endl;
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