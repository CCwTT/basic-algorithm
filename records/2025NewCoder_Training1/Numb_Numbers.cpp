#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

constexpr ll MAXN=200010,M=1e6+10;
ll n,q;
ll a[MAXN],backup[MAXN],c[MAXN];
pair<ll,ll> d[MAXN];
ll cnt;

struct node{
    ll sz;
    ll lc;
    ll rc;
}tr[(2*MAXN)<<2];


ll query(ll k,ll l,ll r,ll p,ll q){
    if(!k)return 0;
    if(p==l&&q==r)return tr[k].sz;
    ll mid=l+r>>1;
    if(q<=mid)return query(tr[k].lc,l,mid,p,q);
    else if(p>mid)return query(tr[k].rc,mid+1,r,p,q);
    else return query(tr[k].lc,l,mid,p,mid)
        +query(tr[k].rc,mid+1,r,mid+1,q);
}


void modify(ll&k,ll l,ll r,ll p,ll v){
    if(!k) k=++cnt;
    tr[k].sz+=v;
    if(l==r)return;
    ll mid=l+r>>1;
    if(p<=mid)modify(tr[k].lc,l,mid,p,v);
    else modify(tr[k].rc,mid+1,r,p,v);
}


ll query_km(ll k,ll l,ll r,ll v){
    if(l==r)return l;
    ll mid=l+r>>1;
    ll x=tr[tr[k].rc].sz;
    if(v<=x)return query_km(tr[k].rc,mid+1,r,v);
    else return query_km(tr[k].lc,l,mid,v-x);
}


void solve(){
    cin>>n>>q;
    cnt=0;
    for(ll i=1;i<=n;i++) cin>>a[i];
    for(ll i=1;i<=n;i++) backup[i]=a[i];
    ll root=0;
    ll p,v;
    vector<ll> disc(a+1,a+n+1);
    ll b=ceil((n-1)/2.0);
    for(ll i=1,p,v;i<=q;i++){
        cin>>p>>v;
        d[i]={p,v};
        backup[p]+=v;
        disc.push_back(backup[p]);
    }
    sort(disc.begin(),disc.end());
    disc.erase(unique(disc.begin(),disc.end()),disc.end());
    unordered_map<ll,ll> mp;
    for(ll i=0;i<disc.size();i++)
        mp[disc[i]]=i+1;
    for(ll i=1;i<=n;i++)
        modify(root,1,M,mp[a[i]],1);
    for(ll i=1;i<=q;i++){
        auto[p,v]=d[i];
        modify(root,1,M,mp[a[p]],-1);
        a[p]+=v;
        modify(root,1,M,mp[a[p]],1);
        ll val=query_km(root,1,M,b);
        ll res=query(root,1,M,1,val-1);
        cout<<res<<endl;
    }
    memset(tr,0,sizeof(node)*(cnt+10));
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
