//https://www.luogu.com.cn/problem/P3834
//@@@
//persistent segment tree
#include<bits/stdc++.h>
using namespace std;
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
        sort(disc.begin()+1,disc.end());
        disc.erase(unique(disc.begin(),disc.end()),disc.end());
        return disc.size()-1;
    }

    ll query(ll x){
        return lower_bound(disc.begin(),disc.end(),x)-disc.begin();
    }
}; 
discretizer disc;

struct node{
    ll sz;
    node* lc,*rc;
    node(){}
    node(ll sz,node* lc,node* rc):sz(sz),lc(lc),rc(rc){}
};
node* nulptr=new node(0,nulptr,nulptr);
node* new_node(){
    return new node(0,nulptr,nulptr);
}
node* new_node(ll sz,node* lc,node* rc){
    return new node(sz,lc,rc);
}
node* clone(node* p){
    return new_node(p->sz,p->lc,p->rc);
}

class persistent_segment_tree{
public:
    ll n;
    vector<ll>& a;
    vector<node*> root;
    persistent_segment_tree(ll roots,ll sz,vector<ll>& a):n(sz-1),a(a),root(roots){
        root[0]=build(1,n);
    }

    void up(node* p){
        p->sz=p->lc->sz+p->rc->sz;
    }

    node* build(ll l,ll r){
        node* p=new_node();
        if(l==r){
            p->sz=0;
            return p;
        }
        ll m=l+r>>1;
        p->lc=build(l,m);
        p->rc=build(m+1,r);
        up(p);
        return p;
    }

    node* update(node* p,ll l,ll r,ll x){
        node* q=clone(p);
        if(l==r){
            q->sz++;
            return q;
        }
        ll m=l+r>>1;
        if(x<=m) q->lc=update(p->lc,l,m,x);
        else q->rc=update(p->rc,m+1,r,x);
        up(q);
        return q;
    }

    ll query(node* p,node* q,ll l,ll r,ll rk){
        if(l==r){
            return l;
        }
        ll lsize=q->lc->sz-p->lc->sz;
        ll m=l+r>>1;
        if(rk<=lsize) return query(p->lc,q->lc,l,m,rk);
        else return query(p->rc,q->rc,m+1,r,rk-lsize);
    }
};


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll n,m;
    cin>>n>>m;
    vector<ll> a(n+1);
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    for(ll i=1;i<=n;i++){
        disc.insert(a[i]);
    }
    ll N=disc.discretize();
    persistent_segment_tree seg(n+1,N+1,a);
    for(ll i=1,x;i<=n;i++){
        x=disc.query(a[i]);
        seg.root[i]=seg.update(seg.root[i-1],1,N,x);
    }
    for(ll i=1;i<=m;i++){
        ll l,r,k;
        cin>>l>>r>>k;
        ll x=seg.query(seg.root[l-1],seg.root[r],1,N,k);
        cout<<disc.disc[x]<<'\n';
    }
    return 0;
}