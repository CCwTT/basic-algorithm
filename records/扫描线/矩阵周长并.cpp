//https://www.luogu.com.cn/problem/P1856
//@@@
//sweeping line,sgt,discretization
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
        //If there are multiple events at the same x,the events with v 1 should be processed first
        //otherwise,the projection length will change frequently,resulting in incorrect results.
        return x^o.x?x<o.x:v>o.v;
    }
};

class Discretizer{
public:
    vector<ll> disc={LLONG_MIN};
    Discretizer(){}
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

    void clear(){
        disc.clear();
        disc.push_back(LLONG_MIN);
    }
};

class SGT{
public:
    ll n;
    Discretizer& disc;
    vector<ll> length,cover,times;
    SGT(ll sz,Discretizer& disc):n(sz-1),cover(n<<2),times(n<<2),disc(disc){}
    
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
        if(x<=l&&r<=y){
            times[p]+=v;
            up(p,l,r);
            return;
        }
        ll m=l+r>>1;
        if(x<=m) update(p<<1,l,m,x,y,v);
        if(y>m) update(p<<1|1,m+1,r,x,y,v);
        up(p,l,r);
    }
};

ll scan(vector<Event>& event,Discretizer& disc){
    ll m=disc.discretize();
    SGT sgt(m+1,disc);
    sort(event.begin(),event.end());
    ll ans=0;
    for(ll i=0;i<event.size();i++){
        ll lastval=sgt.cover[1];
        ll l=disc.query(event[i].y1);
        ll r=disc.query(event[i].y2)-1;
        sgt.update(1,1,sgt.n,l,r,event[i].v);
        ans+=llabs(sgt.cover[1]-lastval);
    }
    return ans;
}

ll scanY(ll n,vector<Rec>& rec){
    vector<Event> event;
    Discretizer disc;
    for(ll i=1;i<=n;i++){
        auto [x1,y1,x2,y2]=rec[i];
        disc.insert(y1);
        disc.insert(y2);
        event.emplace_back(x1,y1,y2,1);
        event.emplace_back(x2,y1,y2,-1);
    }
    return scan(event,disc);
}

ll scanX(ll n,vector<Rec>& rec){
    vector<Event> event;
    Discretizer disc;
    disc.clear();
    for(ll i=1;i<=n;i++){
        auto [x1,y1,x2,y2]=rec[i];
        disc.insert(x1);
        disc.insert(x2);
        event.emplace_back(y1,x1,x2,1);
        event.emplace_back(y2,x1,x2,-1);
    }
    return scan(event,disc);
}

void solve(){
    ll n;
    cin>>n;
    vector<Rec> rec(n+1);
    for(ll i=1;i<=n;i++){
        cin>>rec[i].x1>>rec[i].y1>>rec[i].x2>>rec[i].y2;
    }
    cout<<scanY(n,rec)+scanX(n,rec)<<endl;
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