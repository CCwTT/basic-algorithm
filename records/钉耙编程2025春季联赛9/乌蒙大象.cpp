//https://acm.hdu.edu.cn/contest/problem?cid=1158&pid=1003
//@@@
//geometry,STL,binary search
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
    ll n;
    cin>>n;
    vector<pair<ll,ll>> a(n+1);
    map<pair<ll,ll>,map<ll,ll>> mp;
    for(ll i=1;i<=n;i++){
        ll x,y;
        cin>>x>>y;
        x*=2,y*=2;
        a[i]={x,y};
    }
    sort(a.begin()+1,a.end());
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=n;j++) if(i!=j){
            auto [x1,y1]=a[i];
            auto [x2,y2]=a[j];
            ll u=y1-y2;
            ll v=x2-x1;
            if(u>0&&v>=0){
                if(lower_bound(a.begin()+1,a.end(),pair<ll,ll>{x1+u,y1+v})
				 !=upper_bound(a.begin()+1,a.end(),pair<ll,ll>{x1+u,y1+v})
			&&	   lower_bound(a.begin()+1,a.end(),pair<ll,ll>{x2+u,y2+v})
			     !=upper_bound(a.begin()+1,a.end(),pair<ll,ll>{x2+u,y2+v})){
                    ll xx=(x1+x2+u)/2;
                    ll yy=(y1+y2+v)/2;
                    mp[{xx,yy}][u*u+v*v]++;
                }
            }
        }
    }
    ll ans=0;
    for(auto &[mid,cnt]:mp){
        for(auto [len2,tot]:cnt){
            ans+=tot*(tot-1)/2;
        }
    }
    cout<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}