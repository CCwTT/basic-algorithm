
//CLASSIC IDEA:先枚举,剩下的用数据结构维护
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
#define EPS (1e-20)
typedef long long ll;
typedef __int128 i128;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll N=1.5e5+50;
const ll V=1e6+5;
ll a[N];
ll vis[V];
queue<ll> q;
ll nxt[N],last[N];
ll n,ans=0,ans1=0,ans2=0;

struct segment_tree{
    ll n;
    ll mx[N<<2],add[N<<2];

    void init(){
        memset(mx,0,sizeof(ll)*(n<<2));
        memset(add,0,sizeof(ll)*(n<<2));
    }

    void up(ll p){
        mx[p]=max(mx[p<<1],mx[p<<1|1]);
    }

    void put_tag(ll p,ll v){
        mx[p]+=v;
        add[p]+=v;
    }

    void down(ll p){
        if(add[p]){
            put_tag(p<<1,add[p]);
            put_tag(p<<1|1,add[p]);
            add[p]=0;
        }
    }

    void update(ll p,ll l,ll r,ll x,ll y,ll v){
        if(x<=l&&r<=y){
            put_tag(p,v);
            return;
        }
        ll m=l+r>>1;
        down(p);
        if(x<=m) update(p<<1,l,m,x,y,v);
        if(y>m) update(p<<1|1,m+1,r,x,y,v);
        up(p);
    }
    
    ll query(ll p,ll l,ll r,ll x,ll y){
        if(!(1<=x&&x<=y&&y<=n)) return 0;
        if(x<=l&&r<=y) return mx[p];
        ll m=l+r>>1;
        down(p);
        ll res=0;
        if(x<=m) chmax(res,query(p<<1,l,m,x,y));
        if(y>m) chmax(res,query(p<<1|1,m+1,r,x,y));
        return res;
    }
}seg;


void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        q.push(a[i]);
    }
    for(ll i=n;i>=1;i--){
        nxt[i]=vis[a[i]];
        last[i]=vis[a[i]]?last[nxt[i]]:i;
        vis[a[i]]=i;
    }
    for(ll i=1;i<=n;i++){
        auto u=q.front();
        q.pop();
        vis[u]=false;
        q.push(u);
    }
    seg.n=n;
    for(ll i=1;i<=n;i++){
        if(!vis[a[i]]){
            if(!nxt[i]||nxt[i]==last[i]){
                continue;
            }else{
                seg.update(1,1,n,nxt[i]+1,last[i],1);
            }
        }else{
            if(nxt[i]==last[i]){
                seg.update(1,1,n,i+2,last[i],-1);
            }
        }

        vis[a[i]]=true;
        if(chmax(ans,seg.query(1,1,n,i+2,n))){
            ans1=i+1;
        }
    }
    seg.init();
    for(ll i=1;i<=n;i++){
        auto u=q.front();
        q.pop();
        vis[u]=false;
        q.push(u);
    }
    for(ll i=1;i<ans1;i++){
        if(!vis[a[i]]){
            if(!nxt[i]||nxt[i]==last[i]){
                continue;
            }else{
                seg.update(1,1,n,nxt[i]+1,last[i],1);
            }
        }else{
            if(nxt[i]==last[i]){
                seg.update(1,1,n,i+2,last[i],-1);
            }
        }
        vis[a[i]]=true;
    }
    for(ll i=ans1+1;i<=n;i++){
        if(seg.query(1,1,n,i,i)==ans){
            ans2=i;
            break;
        }
    }
    cout<<ans<<endl<<ans1<<" "<<ans2<<endl;
}

void clear(){
    for(ll i=0;i<=n;i++){
        nxt[i]=last[i]=0;
    }
    while(!q.empty()){
        auto u=q.front();
        q.pop();
        vis[u]=false;
    }
    ans=ans1=ans2=0;
    seg.init();
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
        clear();
    }
    return 0;
}