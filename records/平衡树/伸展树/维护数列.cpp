//https://www.luogu.com.cn/problem/P2042
//@@@
//balanced tree(splay),lazy tag,pool
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MAXN=500005;
ll root=0;
ll a[MAXN];
ll key[MAXN],lc[MAXN],rc[MAXN],fa[MAXN],sz[MAXN],sum[MAXN],all[MAXN],pre[MAXN],suf[MAXN];
bool rev[MAXN];
bool rst[MAXN];
ll rst_val[MAXN];
vector<ll> pool;

void up(ll p){
   sz[p]=sz[lc[p]]+sz[rc[p]]+1;
   sum[p]=sum[lc[p]]+sum[rc[p]]+key[p];
   all[p]=max(max(all[lc[p]],all[rc[p]]),suf[lc[p]]+key[p]+pre[rc[p]]);
   pre[p]=max(pre[lc[p]],sum[lc[p]]+key[p]+pre[rc[p]]);
   suf[p]=max(suf[rc[p]],suf[lc[p]]+key[p]+sum[rc[p]]);
}

ll side(ll p){
   return lc[fa[p]]==p?0:1;
}

void rotate(ll p){
   ll f=fa[p],g=fa[f];
   if(side(p)==0){
		lc[f]=rc[p];
       	if(lc[f]!=0){
           fa[lc[f]]=f;
       	}
       	rc[p]=f;
   }else{
       rc[f]=lc[p];
       if(rc[f]!=0){
           fa[rc[f]]=f;
       }
       lc[p]=f;
   }
   if(g!=0){
       if(side(f)==0){
           lc[g]=p;
       }else{
           rc[g]=p;
       }
   }
   fa[f]=p;
   fa[p]=g;
   up(f);
   up(p);
}

void splay(ll p,ll tar){
   while(fa[p]!=tar){
       ll f=fa[p],g=fa[f];
       if(g!=tar){
           if(side(p)==side(f)){
               rotate(f);
           }else{
               rotate(p);
           }
       }
       rotate(p);
   }
   if(tar==0){
       root=p;
   }
}

void rst_update(ll p,ll val){
   if(p){
       rst[p]=true;
       rst_val[p]=val;
       key[p]=val;
       sum[p]=sz[p]*val;
       all[p]=max(sum[p],val);
       pre[p]=max(sum[p],0ll);
       suf[p]=max(sum[p],0ll);
   }
}

void rst_reverse(ll p){
   if(p){
       swap(pre[p],suf[p]);
       rev[p]^=1;
   }
}

void down(ll p){
   if(rst[p]){
       rst_update(lc[p],rst_val[p]);
       rst_update(rc[p],rst_val[p]);
       rst[p]=false;
   }
   if(rev[p]){
       swap(lc[p],rc[p]);
       rst_reverse(lc[p]);
       rst_reverse(rc[p]);
       rev[p]=false;
   }
}

ll new_node(ll val){
   ll p=pool.back();
   pool.pop_back();
   sz[p]=1;
   key[p]=sum[p]=all[p]=val;
   pre[p]=suf[p]=max(val,0ll);
   fa[p]=lc[p]=rc[p]=0;
   rst[p]=rev[p]=false;
   return p;
}

ll build(ll l,ll r){
   ll mid=(l+r)/2;
   ll root=new_node(a[mid]);
   if(l<mid){
       lc[root]=build(l,mid-1);
       fa[lc[root]]=root;
   }
   if(mid<r){
       rc[root]=build(mid+1,r);
       fa[rc[root]]=root;
   }
   up(root);
   return root;
}

ll node_at(ll x){
   ll p=root;
   while(p!=0){
       down(p);
       if(sz[lc[p]]+1==x){
           return p;
       }else if(sz[lc[p]]>=x){
           p=lc[p];
       }else{
           x-=sz[lc[p]]+1;
           p=rc[p];
       }
   }
   return 0;
}

void insert(ll x,ll len){
   if(x==0){
       root=build(1,len);
   }else{
       ll l=node_at(x);
       ll r=node_at(x+1);
       splay(l,0);
       splay(r,l);
       lc[r]=build(1,len);
       fa[lc[r]]=r;
       up(r);
       up(l);
   }
}

void recycle(ll p){
   if(p!=0){
       pool.push_back(p);
       recycle(lc[p]);
       recycle(rc[p]);
   }
}

void remove(ll x,ll len){
   ll l=node_at(x-1);
   ll r=node_at(x+len);
   splay(l,0);
   splay(r,l);
   recycle(lc[r]);
   lc[r]=0;
   up(r);
   up(l);
}

void reset(ll x,ll len,ll v){
   ll l=node_at(x-1);
   ll r=node_at(x+len);
   splay(l,0);
   splay(r,l);
   rst_update(lc[r],v);
   up(r);
   up(l);
}

void reverse(ll x,ll len){
   ll l=node_at(x-1);
   ll r=node_at(x+len);
   splay(l,0);
   splay(r,l);
   rst_reverse(lc[r]);
   up(r);
   up(l);
}

ll query_sum(ll x,ll len){
   ll l=node_at(x-1);
   ll r=node_at(x+len);
   splay(l,0);
   splay(r,l);
   return sum[lc[r]];
}

ll query_max(){
   return all[root];
}

void solve(){
	ll n,m;
   cin>>n>>m;
   for(ll i=1;i<=MAXN;i++){
       pool.push_back(i);
   }
   a[1]=a[n+2]=all[0]=LLONG_MIN/2;
   for(ll i=2;i<=n+1;i++){
       cin>>a[i];
   }
   insert(0,n+2);
   string op;
   for(ll i=0;i<m;i++){
       cin>>op;
       if(op=="MAX-SUM"){
           cout<<query_max()<<endl;
       }else{
           ll pos,len,c;
           cin>>pos>>len;
           pos++;
           if(op=="INSERT"){
               for(ll j=1;j<=len;j++){
                   cin>>a[j];
               }
               insert(pos,len);
           }else if(op=="DELETE"){
               remove(pos,len);
           }else if(op=="MAKE-SAME"){
               cin>>c;
               reset(pos,len,c);
           }else if(op=="REVERSE"){
               reverse(pos,len);
           }else if(op=="GET-SUM"){
               cout<<query_sum(pos,len)<<endl;
           }
       }
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
