//https://ac.nowcoder.com/acm/contest/view-submission?submissionId=78804321
//@@@
//date computation,dp
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

constexpr ll N=1e6+10;
constexpr ll d[]={31,28,31,30,31,30,31,31,30,31,30,31};

bool is_leap(ll y){
    return y%400==0||(y%4==0&&y%100!=0);
}

ll days_in_month(ll y,ll m){
    return d[m-1]+(is_leap(y)&&m==2);
}

ll get_day(ll y,ll m,ll d){
    ll ans=0;
    for(ll i=1970;i<y;i++)
        ans+=365+is_leap(i);
    for(ll i=1;i<m;i++)
        ans+=days_in_month(y,i);
    ans+=d;
    return ans;
}

ll n,dp[N];
char s[50];
const ll md=get_day(1970,1,1);

void solve(){
    cin>>n;
    vector<pll> t(n);
    for(ll i=0;i<n;i++){
        cin>>s;
        ll Y,M,D;
        sscanf(s,"%lld-%lld-%lld",&Y,&M,&D);
        t[i].first=get_day(Y,M,D)-md;
        ll H,m,S;
        cin>>s;
        sscanf(s,"%lld:%lld:%lld",&H,&m,&S);
        t[i].second=H*3600+m*60+S-20*3600;
        if(t[i].second<0){
            t[i].first--;
            t[i].second+=24*3600;
        }
    }
    sort(t.begin(),t.end());
    for(auto [d,s]:t){
        if(s>=22*3600)  //(24-22)+24=26
            dp[d+2]=max(dp[d+2],dp[d+1]+1);
        dp[d+1]=max(dp[d+1],dp[d]+1);
        dp[d]=max(dp[d],dp[d-1]+1);
    }
    ll mx=0;
    for(ll i=0;i<N;i++)
        mx=max(mx,dp[i]);
    cout<<mx<<" "<<1<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    // cin>>T;
    while(T--){
        solve();
    }
    return 0;
}