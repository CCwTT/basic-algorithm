//http://poj.org/problem?id=3304
//@@@ 
//line-line-relations
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define INF (LLONG_MAX/2)
#define EPS (1e-20)
typedef long long ll;
// typedef __int128 i128;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

using Vec=struct Point{
    ld x,y;
};

using Segment=struct Line{
    Point p1,p2;
};

ld cross(Point a,Point b,Point c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

bool intersect_ls(Line a,Segment b){
    return cross(a.p1,a.p2,b.p1)*cross(a.p1,a.p2,b.p2)<=0;
}

ll n;
const ll N=105;
Segment A[N];
Point B[N<<1];

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        ld x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        A[i]={{x1,y1},{x2,y2}};
        B[i]={x1,y1};
        B[i+n]={x2,y2};
    }
    for(ll i=1;i<=2*n;i++){
        for(ll j=i+1;j<=2*n;j++){
            if(B[i].x==B[j].x&&B[i].y==B[j].y) continue;
            Line cur={B[i],B[j]};
            bool flag=true;
            for(ll k=1;k<=n;k++){
                if(!intersect_ls(cur,A[k])){
                    flag=false;
                    break;
                }
            }
            if(flag){
                cout<<"Yes!"<<endl;
                return;
            }
        }
    }
    cout<<"No!"<<endl;
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