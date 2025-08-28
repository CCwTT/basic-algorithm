//https://ac.nowcoder.com/acm/contest/108306/F
//@@@
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

ll sx1,sy1,sx2,sy2,tx1,ty1,tx2,ty2;

void solve(){
    cin>>sx1>>sy1>>sx2>>sy2>>tx1>>ty1>>tx2>>ty2;
    if(tx1==tx2){
        swap(sx1,sy1);
        swap(sx2,sy2);
        swap(tx1,ty1);
        swap(tx2,ty2);
    }
    if(tx1>tx2){
        swap(tx1,tx2);
        swap(ty1,ty2);
    }
    ll ans=0;
    if(sx1==sx2){
        ans++;
        if(sy1<sy2){
            swap(sx1,sx2);
            swap(sy1,sy2);
        }
        if(abs(sy1-ty1)>abs(sy2-ty1)){
            if(sx1<=tx1){
                sx1++;
                sy1=sy2;
            }else{
                sx1--;
                sy1=sy2;
            }
        }else{
            if(sx1<=tx1){
                sx2++;
                sy2=sy1;
            }else{
                sx2--;
                sy2=sy1;
            }
        }
    }
    if(sx1>sx2){
        swap(sx1,sx2);
        swap(sy1,sy2);
    }
    ans+=max(abs(sx1-tx1),abs(sy1-ty1))*2;
    cout<<ans<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}