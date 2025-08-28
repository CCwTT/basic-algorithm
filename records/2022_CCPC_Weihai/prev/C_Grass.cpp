#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MAXN=1e5+5;
ll n;
ll x[MAXN];
ll y[MAXN];
set<pair<ll,ll>> s;

bool check(ll p){
    s.clear();
    for(ll i=1;i<=4;i++){
        ll dx=x[p]-x[i];
        ll dy=y[p]-y[i];
        ll dd=__gcd(dx,dy);
        s.insert({dx/dd,dy/dd});
    }
    return s.size()>1;
}

ll find(ll p){
    vector<ll> tab={1,2,3,4,p};
    for(ll i=0;i<5;i++){
        s.clear();
        for(ll j=0;j<5;j++) if(i!=j){
            ll dx=x[tab[i]]-x[tab[j]];
            ll dy=y[tab[i]]-y[tab[j]];
            ll dd=llabs(__gcd(dx,dy));
            s.insert({dx/dd,dy/dd});
        }
        if(s.size()==4) return tab[i];
    }
    assert(false);
    return -1;
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>x[i]>>y[i];
    }
    if(n<5){
        cout<<"NO"<<endl;
        return;
    }
    for(ll i=5;i<=n;i++){
        if(check(i)){
            cout<<"YES"<<endl;
            ll centre=find(i);
            cout<<x[centre]<<" "<<y[centre]<<endl;
            for(ll j=1;j<=4;j++) if(j!=centre){
                cout<<x[j]<<" "<<y[j]<<endl;
            }
            if(i!=centre){
                cout<<x[i]<<" "<<y[i]<<endl;
            }
            return;
        }
    }
    cout<<"NO"<<endl;
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