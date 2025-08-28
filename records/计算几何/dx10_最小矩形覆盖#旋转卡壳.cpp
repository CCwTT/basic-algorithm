//https://www.luogu.com.cn/problem/P3187
//@@@ 
//rotating calipers(minimum rectangle cover)
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
        return (*this)/len();
    }
};

Vec dir(Point a,Point b){
    return b-a;
}

ld dis(Point a,Point b){
    return dir(a,b).len();
}

ld cross(Point a,Point b,Point c){
    return dir(a,b)*dir(a,c);
}

ld dot(Point a,Point b,Point c){
    return dir(a,b)&dir(a,c);
}

void standardize(ld& x){
    if(fabsl(x)<EPS) x=0;
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

Vec rotate(Vec a,ld beta){  //逆转角
    return {a.x*cos(beta)-a.y*sin(beta),a.x*sin(beta)+a.y*cos(beta)};
}

vector<Point> pts(4);
ld area=INF;
void rotating_capilars(vector<Point> A){
    ll n=A.size();
    A.push_back(A[0]);
    ll u=1,r=1,l;
    for(ll i=0;i<n;i++){
        while(cross(A[i],A[i+1],A[u])<cross(A[i],A[i+1],A[u+1])) u=(u+1)%n;
        while(dot(A[i],A[i+1],A[r])<dot(A[i],A[i+1],A[r+1])) r=(r+1)%n;
        if(i==0) l=u;
        while(dot(A[i+1],A[i],A[l])<dot(A[i+1],A[i],A[l+1])) l=(l+1)%n;
        ld len=dis(A[i],A[i+1]);
        ld H=cross(A[i],A[i+1],A[u])/len;
        ld R=dot(A[i],A[i+1],A[r])/len;
        ld L=dot(A[i+1],A[i],A[l])/len;
        ld W=L+R-len;
        if(chmin(area,H*W)){
            pts[0]=A[i]+dir(A[i],A[i+1])/len*R;
            pts[3]=A[i+1]+dir(A[i+1],A[i])/len*L;
            Vec e=rotate(dir(A[i],A[i+1]),PI/2).norm();
            pts[1]=pts[0]+e*H;
            pts[2]=pts[3]+e*H;
        }
    }
}

void solve(){
    ll n;
    cin>>n;
    vector<Point> A;
    for(ll i=0;i<n;i++){
        ld x,y;
        cin>>x>>y;
        A.push_back({x,y});
    }
    A=convex_hull(A);
    rotating_capilars(A);
    cout<<fixed<<setprecision(5)<<area<<endl;
    for(ll i=0;i<4;i++){
        standardize(pts[i].x);
        standardize(pts[i].y);
        cout<<fixed<<setprecision(5)<<pts[i].x<<" "<<pts[i].y<<endl;
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