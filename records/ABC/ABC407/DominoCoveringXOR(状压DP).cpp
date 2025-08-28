//https://atcoder.jp/contests/abc407/tasks/abc407_d
//@@@
//state-compression dp
//link:records\蓝桥杯第12届国赛本科生A组\覆盖(二维状压dp,预处理).cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
    ll m,n;
    cin>>m>>n;
    vector<vector<ll>> a(m,vector<ll>(n));
    for(ll i=0;i<m;i++)
        for(ll j=0;j<n;j++)
            cin>>a[i][j];

    // Use an (mn)-bit integer to manage the cells occupied by dominoes
    vector<ll> mats{0}; // Initially, there is an empty grid

    ll domino_vertical=(1ll<<n)+1,domino_horizontal=3;

    for(ll i=0,d=0;i<m;i++)
        for(ll j=0;j<n;j++,d++){ // For each cell
            vector<ll> tmp;
            for(auto mat:mats){
                //If a horizontal domino can be placed, add such a placement
                if(j+1<n&&!(mat&domino_horizontal<<d))
                    tmp.emplace_back(mat|domino_horizontal<<d);
                //If a vertical domino can be placed, add such a placement
                if(i+1<m&&!(mat&domino_vertical<<d))
                    tmp.emplace_back(mat|domino_vertical<<d);
            }
            for(auto mat:tmp){
                mats.push_back(mat);
            }
        }

    ll ans=0;
    for(auto mat:mats){ // For each placement
        ll cur=0;
        for(ll i=0,d=0;i<m;i++)
            for(ll j=0;j<n;j++,d++)
                if(~mat>>d&1) // inspect each cell not covered by a domino
                    cur^=a[i][j]; // to find the total XOR
        ans=max(ans,cur); // Update if it is larger
    }
    cout<<ans<<endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}