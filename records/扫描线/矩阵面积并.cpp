//https://www.luogu.com.cn/record/216906925
//@@@
//sweeping event,sgt,discretization
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Rec{
    ll x1,y1,x2,y2;
};

struct Event{
    ll x,y1,y2,v;
    Event(ll x=0,ll y1=0,ll y2=0,ll v=0):x(x),y1(y1),y2(y2),v(v){}
    bool operator<(const Event& o) const{
        return x<o.x;
    }
};

class Discretizer{
public:
    vector<ll> disc={LLONG_MIN};
    void insert(ll x){
        disc.push_back(x);
    }

    ll discretize(){
        sort(disc.begin(),disc.end());
        disc.erase(unique(disc.begin(),disc.end()),disc.end());
        return disc.size()-1;
    }

    ll query(ll x){
        return lower_bound(disc.begin(),disc.end(),x)-disc.begin();
    }
};


class SGT{
public:
    ll n;
    vector<ll> length,cover,times;
    Discretizer& disc;

    SGT(ll sz,Discretizer& disc):n(sz-1),cover(n<<2),times(n<<2),disc(disc) {}

    //If there's build here,then please mind to use build(1,1,n-1) and accordingly below to change to sgt.update(1,1,sgt.n-1,l,r,event[i].v);;

    void up(ll p,ll l,ll r){
        if(times[p]>0){
            cover[p]=disc.disc[r+1]-disc.disc[l];
        }else{
            if(l==r){
                cover[p]=0;   //If not processed like this,then we'll need cover(n<<3)
            }else{
                cover[p]=cover[p<<1]+cover[p<<1|1];
            }
        }
    }

    void update(ll p,ll l,ll r,ll x,ll y,ll v){
        if(x<=l&&r<=y) {
            times[p]+=v;
            up(p,l,r);
            return;
        }
        ll m=(l+r)>>1;
        if(x<=m) update(p<<1,l,m,x,y,v);
        if(y>m) update(p<<1|1,m+1,r,x,y,v);    
        up(p,l,r);
    }
};

void solve(){
    ll n;
    cin>>n;
    vector<Rec> rec(n+1);
    for(ll i=1;i<=n;++i) {
        cin>>rec[i].x1>>rec[i].y1>>rec[i].x2>>rec[i].y2;
    }
    vector<Event> event(2*n+1);
    Discretizer disc;
    for(ll i=1;i<=n;i++) {
        auto [x1,y1,x2,y2]=rec[i];
        disc.insert(y1);
        disc.insert(y2);
        event[i]=Event(x1,y1,y2,1);
        event[i+n]=Event(x2,y1,y2,-1);
    }
    ll m=disc.discretize();
    SGT sgt(m+1,disc);
    sort(event.begin()+1,event.end());
    ll ans=0;
    ll lastx=0;
    for(ll i=1;i<=2*n;i++){
        auto [x,y1,y2,v]=event[i];
        ans+=(ll)sgt.cover[1]*(x-lastx); //The first case cover[1]=0
        sgt.update(1,1,sgt.n,disc.query(y1),disc.query(y2)-1,v); //n-1
        lastx=x;
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