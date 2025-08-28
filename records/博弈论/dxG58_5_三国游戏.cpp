//https://www.luogu.com.cn/problem/P1199
//@@@
//game theory
//(0)被标记的含义是这个格子的值是其所在行的最大值且是其所在列的最大值 (1)计算机不可能选到被标记的格子 (2)最大的未被标记的格子要么所在行存在被标记的格子，要么所在列存在被标记的格子 (3)选择最大的未被标记的格子
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

void solve(){
    ll n;
    cin>>n;
    vector a(n+1,vector<ll>(n+1));
    vector mark(n+1,vector<bool>(n+1));
    vector<ll> row(n+1),col(n+1);
    for(ll i=1;i<=n;i++){
        for(ll j=i+1;j<=n;j++){
            cin>>a[i][j];
            a[j][i]=a[i][j];
        }
    }
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=n;j++){
            if(i!=j){
                row[i]=max(row[i],a[i][j]);
                col[j]=max(col[j],a[i][j]);
            }
        }
    }
    ll mx=0,px,py;
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=n;j++){
            if(i!=j){
                mark[i][j]=a[i][j]==row[i]&&a[i][j]==col[j];
                if(!mark[i][j]){
                    if(chmax(mx,a[i][j])){
                        tie(px,py)={i,j};
                    }
                }
            }
        }
    }
    cout<<1<<endl;
    cout<<mx<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
    }
    return 0;
}