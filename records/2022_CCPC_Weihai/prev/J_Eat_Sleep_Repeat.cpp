#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node{
    ll x,y;
    bool operator<(const node& o) const{
        return x<o.x;
    }
};

const ll MAXN=1e5+5;
ll n,m;
ll h[MAXN];
node lim[MAXN];
node lim1[MAXN];

ll f(ll bottom,vector<ll>& points,vector<ll>& capacity){
    capacity.push_back(LLONG_MAX);
    ll curh=bottom+1;
    ll curi=0;
    ll res=0;
    for(auto eh:points){
        res+=eh-curh;
        capacity[curi]--;
        if(capacity[curi]==0){
            curi++;
            curh++;
        }
    }
    return res;
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        cin>>h[i];
    }
    sort(h+1,h+n+1);
    for(ll i=1;i<=m;i++){
        cin>>lim[i].x>>lim[i].y;
    }
    m+=2;
    lim[m-1].x=-1;
    lim[m-1].y=0;
    lim[m].x=LLONG_MAX;
    lim[m].y=0;
    sort(lim+1,lim+m+1);
    memcpy(lim1,lim,sizeof(ll)*(m+1));
    ll p=1;
    lim[1]={-1,0};
    for(ll i=2;i<=m;i++){
        if(lim1[i].y==0&&lim1[i-1].y==0&&lim1[i].x==lim1[i-1].x+1){
            lim[p]=lim1[i];
        }else{
            lim[++p]=lim1[i];
        }
    }
    m=p;
    ll pi=1;
    ll ans=0;
    for(ll i=1;i<m;){
        ll j=i+1;
        while(j<=m&&lim[j].y!=0) j++;
        vector<ll> cap,poi;
        while(pi<=n&&h[pi]<lim[j].x){
            poi.push_back(h[pi++]);
        }
        for(ll k=i+1;k<j;k++){
            if(lim[k].x==lim[k-1].x+1){
                cap.push_back(lim[k].y);
            }else{
                break;
            }
        }
        ans=(ans+f(lim[i].x,poi,cap))&1;
        i=j;
    }
    cout<<(ans==1?"Pico":"FuuFuu")<<endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}