//https://codeforces.com/problemset/problem/484/E
//@@@
//persistent segment tree,binary search,discretization,self-defined traversal
//其实做到这道题了，就可以看出可持久化线段树有2大类型:(1)可持久化权值线段树,在原数组上建根数组 (2)以原数组下标范围为单树范围,在其他参数上建根数组，本题属于(2)
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

class discretizer{
public:
    vector<ll> disc;
    discretizer(){
        disc.push_back(LLONG_MIN);
    }

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
discretizer disc;

const ll MAXN=1e5+5;
const ll MAXT=MAXN*30;
ll a[MAXN];
ll root[MAXN];
struct node{
    ll pre,suf,all;
    ll lc,rc;
};
node tr[MAXT];
ll cnt=0;

ll n,m,N;
ll l,r,k,ans;

void up(ll p,ll l,ll r){
    ll m=l+r>>1;
    ll ln=m-l+1;
    ll rn=r-m;
    tr[p].pre=max(tr[tr[p].lc].pre,tr[tr[p].lc].all==ln?ln+tr[tr[p].rc].pre:LLONG_MIN);
    tr[p].suf=max(tr[tr[p].rc].suf,tr[tr[p].rc].all==rn?rn+tr[tr[p].lc].suf:LLONG_MIN);
    tr[p].all=max({tr[tr[p].lc].all,tr[tr[p].rc].all,tr[tr[p].lc].suf+tr[tr[p].rc].pre});
}

void build(ll& p,ll l,ll r){
    p=++cnt;
    if(l==r){
        tr[p].pre=tr[p].suf=tr[p].all=0;
        return;
    }
    ll m=(l+r)>>1;
    build(tr[p].lc,l,m);
    build(tr[p].rc,m+1,r);
    up(p,l,r);
}

void update(ll& p,ll l,ll r,ll pre,ll x,ll v=1){
    p=++cnt,tr[p]=tr[pre];
    if(l==r){
        tr[p].pre=tr[p].suf=tr[p].all=1;
        return;
    }
    ll m=l+r>>1;
    if(x<=m) update(tr[p].lc,l,m,tr[pre].lc,x);
    else update(tr[p].rc,m+1,r,tr[pre].rc,x);
    up(p,l,r);
}

tuple<ll,ll,ll> info;
void query(ll p,ll l,ll r,ll x,ll y){
    if(x<=l&&r<=y){
        auto [pre,suf,all]=info;
        info={
            max(pre,(all==l-x)?pre+tr[p].pre:LLONG_MIN),
            max(tr[p].suf,(tr[p].all==r-l+1)?tr[p].suf+suf:LLONG_MIN),
            max({all,tr[p].all,suf+tr[p].pre})
        };
        return;
    }
    ll m=l+r>>1;
    if(x<=m) query(tr[p].lc,l,m,x,y);
    if(y>m) query(tr[p].rc,m+1,r,x,y);
    return;
}

bool check(ll w){
    info={0,0,0};
    query(root[w],1,n,l,r);
    auto [pre,suf,all]=info;
    return all>=k;
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        disc.insert(a[i]);
    }
    N=disc.discretize();
    for(ll i=1;i<=n;i++){
        a[i]=disc.query(a[i]);
    }
    build(root[N+1],1,n);
    vector<ll> indices(n+1);
    iota(indices.begin(),indices.end(),0);
    sort(indices.begin()+1,indices.end(),[&](ll i,ll j){
        return a[i]>a[j];
    });
    ll i0=1;
    for(ll i=N;i>=1;i--){
        root[i]=root[i+1];
        ll j0=i0+1;
        while(j0<=n&&a[indices[j0]]>=i) j0++;
        for(ll k0=i0;k0<j0;k0++){
            ll k=indices[k0];
            update(root[i],1,n,root[i],k);
        }
        i0=j0;
    }
    cin>>m;
    for(ll i=1;i<=m;i++){
        ans=0;
        cin>>l>>r>>k;
        ll left=1,right=N;
        while(left<=right){
            ll mid=left+right>>1;
            if(check(mid)){
                ans=mid;
                left=mid+1;
            }else{
                right=mid-1;
            }
        }
        cout<<disc.disc[ans]<<endl;
    }
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
