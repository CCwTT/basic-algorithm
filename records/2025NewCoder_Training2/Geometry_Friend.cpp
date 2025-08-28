#include <bits/stdc++.h>
using namespace std;
//#define endl '\n
#define inf LLONG_MAX/2
typedef long long ll;

struct Point{
    ll x,y;
    Point(ll x=0,ll y=0):x(x),y(y) {}
    ll dist2_from(Point o){
        return (x-o.x)*(x-o.x)+(y-o.y)*(y-o.y);
    }
    long double angle_from(Point o){
        return atan2l(y-o.y,x-o.x);
    }
};

struct Vec{
    ll x,y;
    Vec(ll x=0,ll y=0):x(x),y(y) {}
    Vec(Point a,Point b):x(b.x-a.x),y(b.y-a.y) {}
    ll cross(const Vec& o){
        return x*o.y-y*o.x;
    }
};

void solve(){
    ll n;
    Point s;
    cin>>n>>s.x>>s.y;
    vector<Point> pts(n);
    for(auto& [x,y]:pts){
        cin>>x>>y;
    }
    bool out=false;
    for(ll i=0;i<n;i++){
        if(Vec(pts[i],pts[(i+1)%n]).cross(Vec(pts[i],s))<0){
            out=true;
            break;
        }
    }
    if(out){
        cout<<2*M_PI<<endl;
        return;
    }
    ll mx_dis=0;
    for(auto& pt:pts){
        mx_dis=max(mx_dis,pt.dist2_from(s));
    }
    vector<long double> ag;
    for(auto& pt:pts){
        if(pt.dist2_from(s)==mx_dis){
            ag.push_back(pt.angle_from(s));
        }
    }
    sort(ag.begin(),ag.end());
    long double ans=0;
    for(ll i=0;i<ag.size()-1;i++){
        ans=max(ans,ag[i+1]-ag[i]);
    }
    ans=max(ans,ag[0]-ag.back()+2*M_PI);
    cout<<ans<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cout<<fixed<<setprecision(15);
    ll T=1;
    cin>>T; 
    while(T--){
        solve();
    }
    return 0;
}