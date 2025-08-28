//https://www.lanqiao.cn/problems/1040/learning/
//@@@
//sweeping line
#include<bits/stdc++.h>
typedef long long ll; 
using namespace std;

struct Event{
    ll x,y1,y2,v;
    Event(ll x=0,ll y1=0,ll y2=0,ll v=0):x(x),y1(y1),y2(y2),v(v){}
    bool operator<(const Event&o)const{
        return x^o.x?x<o.x:v>o.v;
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
Discretizer disc;

class SGT{
public:
    ll n;
    vector<ll> cover1,cover2,times;
    SGT(ll sz):n(sz-1),cover1(n<<2),cover2(n<<2),times(n<<2) {}
    void up(ll p,ll l,ll r){
        if(times[p]>0){
            if(l==r){
                if(times[p]&1){
                    cover1[p]=disc.disc[r+1]-disc.disc[l];
                    cover2[p]=0;
                }else{
                    cover1[p]=0;
                    cover2[p]=disc.disc[r+1]-disc.disc[l];
                }
            }else{
                if(times[p]&1){
                    cover1[p]=cover2[p<<1]+cover2[p<<1|1];
                    cover2[p]=cover1[p<<1]+cover1[p<<1|1];
                    cover1[p]+=disc.disc[r+1]-disc.disc[l]-cover1[p]-cover2[p];
                }else{
                    cover1[p]=cover1[p<<1]+cover1[p<<1|1];
                    cover2[p]=cover2[p<<1]+cover2[p<<1|1];
                    cover2[p]+=disc.disc[r+1]-disc.disc[l]-cover1[p]-cover2[p];
                }
            }
            
        }else{
            if(l==r){
                cover1[p]=cover2[p]=0;
            }else{
                cover1[p]=cover1[p<<1]+cover1[p<<1|1];
                cover2[p]=cover2[p<<1]+cover2[p<<1|1];
            }
        }
    }

    /* approach 2,when memory is abundant,even better than upper approach
    SGT(ll sz):n(sz-1),cover1(n<<3),cover2(n<<3),times(n<<2) {}                      //3 3
    void up(ll p,ll l,ll r){
        if(times[p]>0){
            if(times[p]&1){
                cover1[p]=cover2[p<<1]+cover2[p<<1|1];
                cover2[p]=cover1[p<<1]+cover1[p<<1|1];
                cover1[p]+=disc.disc[r+1]-disc.disc[l]-cover1[p]-cover2[p];
            }else{
                cover1[p]=cover1[p<<1]+cover1[p<<1|1];
                cover2[p]=cover2[p<<1]+cover2[p<<1|1];
                cover2[p]+=disc.disc[r+1]-disc.disc[l]-cover1[p]-cover2[p];
            }
        }else{
            cover1[p]=cover1[p<<1]+cover1[p<<1|1];
            cover2[p]=cover2[p<<1]+cover2[p<<1|1];
        }
    }
    */

    void update(ll p,ll l,ll r,ll x,ll y,ll v){
        if(l>=x&&r<=y){
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

void solve(){
    ll n;
    cin>>n;
    vector<Event> event;
    for(ll i=1;i<=n;i++){
        ll x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        disc.insert(y1);
        disc.insert(y2);
        event.emplace_back(x1,y1,y2,1);
        event.emplace_back(x2,y1,y2,-1);
    }
    ll m=disc.discretize();
    sort(event.begin(),event.end());
    SGT sgt(m+1);
    ll lastx=0;
    ll ans1=0;
    ll ans2=0;
    for(ll i=0;i<event.size();i++){
        auto [x,y1,y2,v]=event[i];
        ans1+=(x-lastx)*sgt.cover1[1];
        ans2+=(x-lastx)*sgt.cover2[1];
        sgt.update(1,1,sgt.n,disc.query(y1),disc.query(y2)-1,v);
        lastx=event[i].x;
    }
    cout<<ans1<<endl<<ans2<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}