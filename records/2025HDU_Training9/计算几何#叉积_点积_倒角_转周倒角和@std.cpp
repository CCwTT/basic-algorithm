//https://acm.hdu.edu.cn/contest/problem?cid=1180&pid=1005
//@@@
//computational geometry,cross product,dot product,directed angle
//对于任意闭合多边形(凸/凹多边形),逆时针转周倒角和为360度,顺时针转周倒角和为-360度
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
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

Vec dir(Point a,Point b){
    return b-a;
}

ll cross(Vec a,Vec b){
    return a.x*b.y-a.y*b.x;
}

ll dot(Vec a,Vec b){
    return a.x*b.x+a.y*b.y;
}

const ll M=1e6+7;
const ld EPS=1e-20;
ll n,cnt,mark[M],id[M]; ld sum;
Point pts[M],P[M];

//倒角(directed angle)
ld dir_ang(Vec a,Vec b){
	return atan2(cross(a,b),dot(a,b));
}

bool cmp(ll i,ll j){
	return P[i].x^P[j].x?P[i].x<P[j].x:P[i].y<P[j].y;
}

void solve(){
    cin>>n;
    ll cnt=0;
    sum=0;
    for(ll i=1;i<=n;i++){
        cin>>pts[i].x>>pts[i].y;
    }
    tie(pts[n+1],pts[n+2])={pts[1],pts[2]};
    for(ll i=1;i<=n;i++){
        sum+=dir_ang(dir(pts[i],pts[i+1]),dir(pts[i+1],pts[i+2]));
    }
    for(ll i=1;i<=n;i++){
        if(dir_ang(dir(pts[i],pts[i+1]),dir(pts[i+1],pts[i+2]))>EPS){
            P[++cnt]=pts[i+1],mark[cnt]=1;
        }
        if(dir_ang(dir(pts[i],pts[i+1]),dir(pts[i+1],pts[i+2]))<-EPS){
            P[++cnt]=pts[i+1],mark[cnt]=0;
        }
    }
    if(sum<0){
        for(int i=1;i<=cnt;i++){
            mark[i]=1-mark[i];
        }
    } 
    iota(id+1,id+cnt+1,1);
    sort(id+1,id+cnt+1,cmp);
    cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++){
        auto [x,y,_]=P[id[i]];
        cout<<x<<" "<<y<<" ";
        if(mark[id[i]]==1){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
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