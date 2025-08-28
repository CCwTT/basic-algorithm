//https://www.luogu.com.cn/problem/P2252
//wrong
//game theory(Wythoff's game)
//打表打出来应该能看出max(i,j)和min(i,j)存在一定的比例关系,先博闻强记吧,"长大了再学习"
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

ll sg[31][31];

ll mex(vector<ll>& vec){
    sort(vec.begin(),vec.end());
    vec.erase(unique(vec.begin(),vec.end()),vec.end());
    for(ll i=0;i<vec.size();i++){
        if(vec[i]!=i) return i;
    }
    return vec.size();
}

int init=[]{
    for(ll i=0;i<=30;i++){
        for(ll j=0;j<=30;j++) if(i||j){
            vector<ll> vec;
            for(ll k=0;k<i;k++){
                vec.push_back(sg[k][j]);
            }
            for(ll k=0;k<j;k++){
                vec.push_back(sg[i][k]);
            }
            for(ll k=1;k<=min(i,j);k++){
                vec.push_back(sg[i-k][j-k]);
            }
            sg[i][j]=mex(vec);
            // if(!sg[i][j]){
            //     cout<<i<<" "<<j<<" "<<1.0*max(i,j)/min(i,j)<<endl;
            // }
        }
    }
    return 0;
}();

void solve(){
    // for(ll i=0;i<=30;i++){
    //     for(ll j=0;j<=30;j++){
    //         cout<<sg[i][j]<<" ";
    //     }
    //     cout<<" endl"<<endl;
    // }
    // cout<<endl;
    ll x,y;
    cin>>x>>y;
    if(x<y) swap(x,y);
    cout<<((ll)((sqrt(5)+1)/2*(x-y))!=y?1:0)<<endl;
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