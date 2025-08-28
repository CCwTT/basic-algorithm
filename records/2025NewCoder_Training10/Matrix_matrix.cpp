//https://ac.nowcoder.com/acm/contest/108307/I
//constructive algorithm
/*
先判断什么时候无解。注意到当某数 i 是 n 的倍数的时候，这个数无法
在竖直方向上行走。而当它是 m 的倍数的时候，这个数无法在水平方向上
行走。所以 i = lcm(m, n) 只能等于 nm。所以 n, m 不互质的时候无解。
接下来，构造所有 n, m 互质的情况。先把 1 ∼ m 放到第一行上。直接
从 1 开始左右左右摇摆填充即可。
接下来，一行填满之后我们需要换到另一行。考虑和水平时一样，每次
上下摇摆。此时走到的行号相对于第一行的位移是 {0, m, −m, 2m, −2m, ...}，
是一个模 n 完系（由于 n, m 互质），因此一定不会回到之前填过的某一行。
在新的行上继续摇摆即可。
First, determine when there is no solution. Notice that when a number i is a multiple of n, this number cannot move vertically. And when it is a multiple of m, this number cannot move horizontally. So i = lcm(m, n) can only be equal to nm. Therefore, when n and m are not coprime, there is no solution.
Next, construct all cases where n and m are coprime. First, place the numbers from 1 to m in the first row. Just fill them in by swinging left and right starting from 1.
Next, after one row is filled, we need to move to another row. Consider the same way as when moving horizontally, swing up and down each time. At this time, the displacement of the row number relative to the first row is {0, m, -m, 2m, -2m, ...}, which is a complete residue system modulo n (since n and m are coprime). So it will definitely not return to a previously filled row. Just continue to swing on the new row.
*/
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

constexpr ll N=1e6+5;
ll n,m;
bool vis1[N],vis2[N];

void solve(){
    cin>>n>>m;
    if(gcd(n,m)!=1){
        cout<<"NO"<<endl;
        return;
    }
    cout<<"YES"<<endl;
    vector<vl> ans(n,vl(m));
    ll x=0,y=0,dx=1,dy=1,t;
    for(ll i=0;i<n;i++){
        for(ll j=0;j<m;j++){
            t=i*m+j+1;
            ans[x][y]=t;
            if(j<m-1){
                y=((y+dy*t)%m+m)%m;
                dy=-dy;
            }
        }
        x=((x+dx*t)%n+n)%n;
        dx=-dx;
    }
    for(ll i=0;i<n;i++){
        for(ll j=0;j<m;j++){
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }
}

void clear(){

}

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