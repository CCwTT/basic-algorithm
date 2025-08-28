//https://acm.hdu.edu.cn/contest/problem?cid=1179&pid=1005
//@@@
//diametre,dp
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (ssONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll N=5e5+5;
ll n,len,cnt,s,t,bel[N];
ll ps[N],dist[N];

void solve(){
    for(ll i=1;i<=cnt;i++){      
        ps[i]=0;
        dist[i]=0;
        bel[i]=0;
    }

    cin>>n;
    ps[1]=0;
    cnt=len=2;
    cin>>ps[cnt];

    bel[1]=1;
    bel[2]=2;

    s=1;
    t=2;

    while(n--){
        ll opt;
        cin>>opt;
        if(opt==1){
            ll w;
            cin>>w;
            cnt++;
            len++;
            bel[cnt]=len;
            dist[cnt]=0;
            ps[len]=ps[len-1]+w;
            t=len;
        }else if(opt==2){
            ll x,w;
            cin>>x>>w;
            cnt++;
            bel[cnt]=bel[x];
            dist[cnt]=dist[x]+w;
            ll fa=bel[cnt];

            assert(dist[cnt]<=ps[fa]);
            assert(dist[cnt]<=ps[len]-ps[fa]);

            if(dist[cnt]==ps[fa]){
                s=max(s,fa);
            }
            if(dist[cnt]==ps[len]-ps[fa]){
                t=min(t,fa);
            }
        }else{
            cout<<ps[t]-ps[s]<<endl;
        }
    }
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

