//https://www.luogu.com.cn/problem/P3919
//动态方法被卡时间了呜呜呜~
//persistent segment tree
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node{
	ll val;
	node* lc,*rc;
	node(){}
	node(ll val,node* lc,node* rc):val(val),lc(lc),rc(rc){}
};
node* nulptr=new node(0,nulptr,nulptr);
node* new_node(){
	return new node(0,nulptr,nulptr);
}
node* new_node(ll val,node* lc,node* rc){
	return new node(val,lc,rc);
}

class persistent_segment_tree{
public:
    ll n;
    vector<ll>& a;
    vector<node*> root;
    persistent_segment_tree(ll sz,vector<ll>& a):a(a),n(sz-1),root(sz){
        root[0]=build(1,n);
    }

    node* clone(node* p){
		return new_node(p->val,p->lc,p->rc);
    }

    node* build(ll l,ll r){
        node* p=new_node();
        if(l==r){
            p->val=a[l];
            return p;
        }
        ll m=l+r>>1;
        p->lc=build(l,m);
        p->rc=build(m+1,r);
        return p;
    }

    node* update(node* p,ll l,ll r,ll x,ll v){
        node* q=clone(p);
        if(l==r){
            q->val=v;
            return q;
        }
        ll m=l+r>>1;
        if(x<=m) q->lc=update(p->lc,l,m,x,v);
        else q->rc=update(p->rc,m+1,r,x,v);
        return q;
    }

    ll query(node* p,ll l,ll r,ll x){
        if(l==r){
            return p->val;
        }
        ll m=l+r>>1;
        if(x<=m) return query(p->lc,l,m,x);
        else return query(p->rc,m+1,r,x);
    }
};

void solve(){
    ll n,m;
    cin>>n>>m;
    vector<ll> a(n+1);
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    persistent_segment_tree seg(n+1,a);
    for(ll i=1;i<=m;i++){
        ll vs,op,x,y;
        cin>>vs>>op;
        if(op==1){
            cin>>x>>y;
            seg.root[i]=seg.update(seg.root[vs],1,n,x,y);
        }else{
            cin>>x;
            seg.root[i]=seg.root[vs];
            cout<<seg.query(seg.root[vs],1,n,x)<<'\n';
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

