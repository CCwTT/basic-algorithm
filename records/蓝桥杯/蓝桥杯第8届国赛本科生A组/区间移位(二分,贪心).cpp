//https://www.lanqiao.cn/problems/111/learning/
//@@@
//binary,greedy
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
    ll n;
    cin>>n;
    vector<pair<ll,ll>> intervals(n);
    for(ll i=0;i<n;i++){
        ll x,y;
        cin>>x>>y;
        intervals[i]={x*2,y*2};
    }
    sort(intervals.begin(),intervals.end(),[](const pair<ll,ll> u,const pair<ll,ll> v){
        return u.second<v.second;
    });

    ll l=0,r=20000;
    while(r>=l){
        ll m=l+r>>1;

        auto check=[&](ll k)->bool{
            ll rm=0;
            vector<pair<ll,ll>> tmp(intervals);
            while(true){
                bool flag=false;
                for(ll i=0;i<tmp.size();i++){
                    auto [x,y]=tmp[i];
                    ll len=x-y;
                    if(x-k<=rm&&rm<=y+k){
                        flag=true;
                        if(x+k>=rm)
                            rm+=len;
                        else
                            rm=y+k;
                        tmp.erase(tmp.begin()+i);
                        break;
                    }
                }
                if(rm>=20000||!flag) break;
            }
            return rm>=20000;
        };

        if(check(m)){
            r=m-1;
        }else{
            l=m+1;
        } 
    }
    if(~l&1) cout<<l/2<<endl;
    else cout<<fixed<<setprecision(1)<<(double)l/2<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}