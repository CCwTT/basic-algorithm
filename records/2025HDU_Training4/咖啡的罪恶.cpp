#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll N=2e5+5;
ll n,q;
ll a[N];
set<ll> sl,sr;
set<ll> s3,s4,s5;

ll mx[N<<2];
    
inline void up(ll p){
    mx[p]=max(mx[p<<1],mx[p<<1|1]);
}

void modify(ll p,ll l,ll r,ll x,ll v){
    if(l==r){
        mx[p]=v;
        return;
    }
    ll m=l+r>>1;
    if(x<=m) modify(p<<1,l,m,x,v);
    else modify(p<<1|1,m+1,r,x,v);
    up(p);
}

ll query_mx(ll p,ll l,ll r,ll x,ll y){
    if(x<=l&&r<=y) return mx[p];
    ll m=l+r>>1;
    ll res=-inf;
    if(x<=m) res=max(res,query_mx(p<<1,l,m,x,y));
    if(y>m) res=max(res,query_mx(p<<1|1,m+1,r,x,y));
    return res;
}

ll c[N];

inline void add(ll x,ll v){
    while(x<=n){
        c[x]+=v;
        x+=x&-x;
    }
}

inline ll query_sum(ll x){
    ll res=0;
    while(x){
        res+=c[x];
        x-=x&-x;
    }
    return res;
}

ll query_sum(ll x,ll y){
    return query_sum(y)-query_sum(x-1);
}

inline bool check(ll p,ll len){
    if(p<1||p+len-1>n) return false;
    if(len==4){
        if(a[p]==1&&a[p+1]==2&&a[p+2]==1&&a[p+3]==0
        || a[p]==2&&a[p+1]==0&&a[p+2]==2&&a[p+3]==0){
            return true;
        }
        return false;
    }else if(len==5){
        if(a[p]==2&&a[p+1]==1&&a[p+2]==2&&a[p+3]==0&&a[p+4]==0){
            return true;
        }
        return false;
    }else{
        ll x=a[p];
        ll q=p+x;   //无x==len-4
        if(x==len-4&&a[p+1]==2&&a[p+2]==1&&a[q]==1&&(x==3||query_sum(p+3,q-1)==0)&&a[q+1]==0&&a[q+2]==0&&a[q+3]==0){   //query_mx
            return true;
        }
        return false;
    }
}

void init(){   //no init
    fill(c,c+n+1,0);
    fill(mx,mx+(n<<2)+1,0);
    sl.clear();
    sr.clear();
    s3.clear();
    s4.clear();
    s5.clear();
}

void solve(){
    cin>>n>>q;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        add(i,a[i]);
    }
    for(ll i=1;i<=n;i++){
        if(a[i]==1||a[i]==2){
            if(check(i,4)){
                s4.insert(i);
            }else if(check(i,5)){
                s5.insert(i);
            }
        }else if(a[i]>=3){   //else
            s3.insert(i);
            if(check(i,a[i]+4)){
                sl.insert(i);
                sr.insert(i+a[i]+3);
                modify(1,1,n,i+a[i]+3,a[i]+4);
            }
        }
    }

    while(q--){
        ll op;
        cin>>op;
        if(op==1){
            ll x,v;
            cin>>x>>v;
            if(a[x]==v) continue;
            if(a[x]>=3){
                s3.erase(x);
            }
            auto it=s4.upper_bound(x);
            if(it!=s4.begin()){
                it--;
                if(*it+3>=x){
                    s4.erase(it);
                }
            }
            it=s4.upper_bound(x);
            if(it!=s4.begin()){
                it--;
                if(*it+3>=x){ //+4
                    s4.erase(it);
                }
            }
            it=s5.upper_bound(x);
            if(it!=s5.begin()){
                it--;
                if(*it+4>=x){  //+5
                    s5.erase(it);
                }
            }
            it=sl.upper_bound(x);
            if(it!=sl.begin()){
                it--;
                auto it2=sr.lower_bound(*it);
                if(*it<=x&&x<=*it2){
                    sl.erase(it);
                    sr.erase(it2);
                    modify(1,1,n,*it2,0);
                }
            }
            add(x,v-a[x]);
            a[x]=v;
            if(v==0){
                if(check(x-1,4)){
                    s4.insert(x-1);
                }
                if(check(x-3,4)){
                    s4.insert(x-3);
                }else if(check(x-3,5)){
                    s5.insert(x-3);
                }else if(check(x-4,5)){
                    s5.insert(x-4);
                }else{
                    it=s3.upper_bound(x);
                    if(it!=s3.begin()){
                        it--;
                        if(check(*it,a[*it]+4)){
                            sl.insert(*it);
                            sr.insert(*it+a[*it]+3);
                            modify(1,1,n,*it+a[*it]+3,a[*it]+4);
                        }
                    }
                }
            }else if(v==1){
                if(check(x,4)){
                    s4.insert(x);
                }else if(check(x-2,4)){
                    s4.insert(x-2);
                }else if(check(x-1,5)){
                    s5.insert(x-1);
                }else if(x-2>=1&&check(x-2,a[x-2]+4)){
                    sl.insert(x-2);
                    sr.insert(x+a[x-2]+1); //x-2+a[x-2]+4-1
                    modify(1,1,n,x+a[x-2]+1,a[x-2]+4);
                }else{
                    it=s3.upper_bound(x);
                    if(it!=s3.begin()){
                        it--;
                        if(check(*it,a[*it]+4)){
                            sl.insert(*it);
                            sr.insert(*it+a[*it]+3);
                            modify(1,1,n,*it+a[*it]+3,a[*it]+4);
                        }
                    }
                }
            }else if(v==2){
                if(check(x,4)){
                    s4.insert(x);
                }
                if(check(x-1,4)){
                    s4.insert(x-1);
                }else if(check(x-2,4)){
                    s4.insert(x-2);
                }else if(check(x,5)){
                    s5.insert(x);
                }else if(check(x-2,5)){
                    s5.insert(x-2);
                }else if(x-1>=1&&check(x-1,a[x-1]+4)){
                    sl.insert(x-1);
                    sr.insert(x+a[x-1]+2); //x-1+a[x-1]+4-1
                    modify(1,1,n,x+a[x-1]+2,a[x-1]+4);
                }
            }else{
                s3.insert(x);
                if(check(x,a[x]+4)){
                    sl.insert(x);
                    sr.insert(x+a[x]+3);
                    modify(1,1,n,x+a[x]+3,a[x]+4);
                }
            }
        }else{
            ll l,r;
            ll ans=0;
            cin>>l>>r;
            auto it=s4.lower_bound(l);
            if(it!=s4.end()){
                if(*it+3<=r){
                    ans=max(ans,4ll);
                }
            }
            it=s5.lower_bound(l);
            if(it!=s5.end()){
                if(*it+4<=r){
                    ans=max(ans,5ll);
                }
            }
            it=sl.lower_bound(l);
            if(it!=sl.end()){
                auto it2=sr.lower_bound(*it);  //l 
                if(*it2<=r){
                    ans=max(ans,query_mx(1,1,n,*it2,r));
                }
            }
            cout<<ans<<endl;
        }
    }
    init();
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