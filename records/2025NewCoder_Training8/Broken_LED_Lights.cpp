//https://ac.nowcoder.com/acm/contest/108305/F
//@@@
//status compression dp,time optimization
//lesson:尽量用vector替代unordered_set,unordered_map
//时间优化方式:剪枝(mask分层剪枝),二分
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

constexpr ll N =-1;

const vector<vector<ll>> D={
    {0,1,2,4,5,6},
    {2,5},
    {0,2,3,4,6},
    {0,2,3,5,6},
    {1,2,3,5},
    {0,1,3,5,6},
    {0,1,3,4,5,6},
    {0,2,5},
    {0,1,2,3,4,5,6},
    {0,1,2,3,5,6}
};

vector<ll> tab[4][16];
bool vis[(1<<21)+5];

ll init=[]{
    for(ll i=1;i<=3;i++){
        for(ll mask=0;mask<1<<(i*7);mask++){
            ll cnt=__builtin_popcountll(mask);
            if(cnt<=15){
                tab[i][__builtin_popcountll(mask)].push_back(mask);
            }
        }
    }
    return 0;
}();

ll n,m;

void solve(){
    cin>>n>>m;
    vector<ll> status(n);
    for(ll i=0;i<n;i++){
        string s;
        cin>>s;
        for(ll j=0;j<m;j++){
            ll num=s[j]-'0';
            for(auto x:D[num]){
                status[i]|=1ll<<(x+j*7);
            }
        }
    }
    ll ans=LLONG_MAX/2;
    ll l=0,r=15;
    while(l<=r){
        ll mid=l+r>>1;

        auto check=[&](ll t)->bool{
            for(auto mask:tab[m][t]){
                bool ok=true;
                ll i;
                for(i=0;i<n;i++){
                    if(vis[status[i]&mask]){
                        ok=false;
                        break;
                    }
                    vis[status[i]&mask]=true;
                }
                for(i=min(i,n-1);i>=0;i--){
                    vis[status[i]&mask]=false;
                }
                if(ok) return true;
            }
            return false;
        };

        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
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