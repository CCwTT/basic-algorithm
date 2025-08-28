//https://www.luogu.com.cn/problem/P6242
//@@@
//seg model:press operation,interval history max
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

class segment_tree{
public:
    ll n;
    vector<ll>& a;
    vector<ll> sum,mx,cnt,sem,add1,add2,historyMx,add1_historyMx,add2_historyMx;
    segment_tree(ll sz,vector<ll>& a):a(a),n(sz-1),sum(n<<2),mx(n<<2),cnt(n<<2),sem(n<<2),add1(n<<2),add2(n<<2),historyMx(n<<2),add1_historyMx(n<<2),add2_historyMx(n<<2){
        build(1,1,n);
    }

    void up(ll p){
        historyMx[p]=max(historyMx[p<<1],historyMx[p<<1|1]);
        sum[p]=sum[p<<1]+sum[p<<1|1];
        mx[p]=max(mx[p<<1],mx[p<<1|1]);
        if(mx[p<<1]>mx[p<<1|1]){
            cnt[p]=cnt[p<<1];
            sem[p]=max(sem[p<<1],mx[p<<1|1]);
        }else if(mx[p<<1]<mx[p<<1|1]){
            cnt[p]=cnt[p<<1|1];
            sem[p]=max(mx[p<<1],sem[p<<1|1]);
        }else{
            cnt[p]=cnt[p<<1]+cnt[p<<1|1];
            sem[p]=max(sem[p<<1],sem[p<<1|1]);
        }
    }

    void apply(ll p,ll l,ll r,ll v1,ll v2,ll v1_historyMx,ll v2_historyMx){
        ll len=r-l+1;
        sum[p]+=v1*cnt[p]+v2*(len-cnt[p]);
        sem[p]+=sem[p]==LLONG_MIN?0:v2;
        historyMx[p]=max(historyMx[p],mx[p]+v1_historyMx);
        add1_historyMx[p]=max(add1_historyMx[p],add1[p]+v1_historyMx);
        add2_historyMx[p]=max(add2_historyMx[p],add2[p]+v2_historyMx);
        mx[p]+=v1;
        add1[p]+=v1;
        add2[p]+=v2;
    }

    void down(ll p,ll l,ll r){
        ll m=l+r>>1;
        ll ln=m-l+1;
        ll rn=r-m;
        ll tmp=max(mx[p<<1],mx[p<<1|1]);
        if(mx[p<<1]==tmp){
            apply(p<<1,l,m,add1[p],add2[p],add1_historyMx[p],add2_historyMx[p]);
        }else{
            apply(p<<1,l,m,add2[p],add2[p],add2_historyMx[p],add2_historyMx[p]);
        }
        if(mx[p<<1|1]==tmp){
            apply(p<<1|1,m+1,r,add1[p],add2[p],add1_historyMx[p],add2_historyMx[p]);
        }else{
            apply(p<<1|1,m+1,r,add2[p],add2[p],add2_historyMx[p],add2_historyMx[p]);
        }
        add1[p]=add2[p]=add1_historyMx[p]=add2_historyMx[p]=0;
    }

    void build(ll p,ll l,ll r){
        add1[p]=add2[p]=add1_historyMx[p]=add2_historyMx[p]=0;
        if(l==r){
            sum[p]=mx[p]=historyMx[p]=a[l];
            sem[p]=LLONG_MIN;
            cnt[p]=1;
            return;
        }
        ll m=(l+r)>>1;
        build(p<<1,l,m);
        build(p<<1|1,m+1,r);
        up(p);
    }

    void update_add(ll p,ll l,ll r,ll x,ll y,ll v){
        if(x<=l&&r<=y){
            apply(p,l,r,v,v,v,v);
            return;
        }
        ll m=(l+r)>>1;
        down(p,l,r);
        if(x<=m) update_add(p<<1,l,m,x,y,v);
        if(y>m) update_add(p<<1|1,m+1,r,x,y,v);
        up(p);
    }

    void update_press(ll p,ll l,ll r,ll x,ll y,ll v){
        if(v>=mx[p]) return;
        if(x<=l&&r<=y&&sem[p]<v){
            apply(p,l,r,v-mx[p],0,v-mx[p],0);
            return;
        }
        ll m=(l+r)>>1;
        down(p,l,r);
        if(x<=m) update_press(p<<1,l,m,x,y,v);
        if(y>m) update_press(p<<1|1,m+1,r,x,y,v);
        up(p);
    }

    ll query_sum(ll p,ll l,ll r,ll x,ll y){
        if(x<=l&&r<=y) return sum[p];
        ll m=(l+r)>>1;
        down(p,l,r);
        ll res=0;
        if(x<=m) res+=query_sum(p<<1,l,m,x,y);
        if(y>m) res+=query_sum(p<<1|1,m+1,r,x,y);
        return res;
    }

    ll query_max(ll p,ll l,ll r,ll x,ll y){
        if(x<=l&&r<=y) return mx[p];
        ll m=(l+r)>>1;
        down(p,l,r);
        ll res=LLONG_MIN;
        if(x<=m) res=max(res,query_max(p<<1,l,m,x,y));
        if(y>m) res=max(res,query_max(p<<1|1,m+1,r,x,y));
        return res;
    }

    ll query_history_max(ll p,ll l,ll r,ll x,ll y){
        if(x<=l&&r<=y) return historyMx[p];
        ll m=(l+r)>>1;
        down(p,l,r);
        ll res=LLONG_MIN;
        if(x<=m) res=max(res,query_history_max(p<<1,l,m,x,y));
        if(y>m) res=max(res,query_history_max(p<<1|1,m+1,r,x,y));
        return res;
    }
};

void solve(){
    ll n,m;
    cin>>n>>m;
    vector<ll> a(n+1);
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    segment_tree seg(n+1,a);
    for(ll i=1,op,l,r;i<=m;i++){
        cin>>op>>l>>r;
        if(op==1){
            ll v;
            cin>>v;
            seg.update_add(1,1,n,l,r,v);
        }else if(op==2){
            ll v;
            cin>>v;
            seg.update_press(1,1,n,l,r,v);
        }else if(op==3){
            cout<<seg.query_sum(1,1,n,l,r)<<endl;
        }else if(op==4){
            cout<<seg.query_max(1,1,n,l,r)<<endl;
        }else{
            cout<<seg.query_history_max(1,1,n,l,r)<<endl;
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    solve();
    return 0;
}


//tag