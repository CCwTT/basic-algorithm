#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

//build:������ʼ��,if m ���� up
//update:if m down,if ���� up
//query:if m down,ll if ���� 

class segment_tree{
private:
	int n;
	vector<ll> mx;
	vector<ll> set;
	vector<bool> set_lazy;
	vector<ll> add;
public:
	segment_tree(int n):mx(n<<2),set(n<<2),set_lazy(n<<2),add(n<<2) {
		build(1,1,n);
	}
	
	void up(int p){
		mx[p]=max({mx[p<<1],mx[p<<1|1]});
	} 
	
	void down(int p){
		if(set_lazy[p]){
			mx[p<<1]=set[p];
			set[p<<1]=set[p],set_lazy[p<<1]=true,add[p<<1]=0;
			mx[p<<1|1]=set[p];
			set[p<<1|1]=set[p],set_lazy[p<<1|1]=true,add[p<<1|1]=0;
			set_lazy[p]=false;
		}
		if(add[p]){
			mx[p<<1]+=add[p];
			add[p<<1]+=add[p];
			mx[p<<1|1]+=add[p];
			add[p<<1|1]+=add[p];
			add[p]=0;
		}
	}
	
	void build(int p,int l,int r){
		mx[p]=LLONG_MIN/2;
		set[p]=0,set_lazy[p]=false,add[p]=0;
		if(l==r) return;
		int m=l+r>>1;
		build(p<<1,l,m);
		build(p<<1|1,m+1,r);
		up(p);
	}
	
	void update_set(int p,int l,int r,int x,int y,ll k){
		if(x<=l&&r<=y){
			mx[p]=k;
			set[p]=k,set_lazy[p]=true,add[p]=0;
			return;
		}
		int m=l+r>>1;
		down(p);
		if(x<=m) update_set(p<<1,l,m,x,y,k);
		if(y>m) update_set(p<<1|1,m+1,r,x,y,k);
		up(p);
	}
	
	void update_add(int p,int l,int r,int x,int y,ll k){
		if(x<=l&&r<=y){
			mx[p]+=k;
			add[p]+=k;
			return;
		}
		int m=l+r>>1;
		down(p);
		if(x<=m) update_add(p<<1,l,m,x,y,k);
		if(y>m) update_add(p<<1|1,m+1,r,x,y,k);
		up(p);
	}
	
	ll query_mx(int p,int l,int r,int x,int y){
		if(x<=l&&r<=y){
			return mx[p];
		}
		int m=l+r>>1;
		down(p);
		ll res=LLONG_MIN/2;
		if(x<=m) res=max({res,query_mx(p<<1,l,m,x,y)});
		if(y>m) res=max({res,query_mx(p<<1|1,m+1,r,x,y)});
		return res;
	}
};


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int n,Q;
	cin>>n>>Q;
	segment_tree seg(n);
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		seg.update_set(1,1,n,i,i,x);
	} 
	for(;Q;Q--){
		int op;
		cin>>op;
		if(op==1){
			ll l,r,x;
			cin>>l>>r>>x;
			seg.update_set(1,1,n,l,r,x);
		}else if(op==2){
			ll l,r,x;
			cin>>l>>r>>x;
			seg.update_add(1,1,n,l,r,x);
		}else{
			ll l,r;
			cin>>l>>r;
			ll res=seg.query_mx(1,1,n,l,r);
			cout<<res<<endl;
		}
	}
    return 0;
}

//maintain range sum,supporting range modification
//@@@
class segment_tree{
	vector<ll> sum,add;
public:
	segment_tree(ll n):sum(n<<2),add(n<<2) {}

	void up(ll p,ll l,ll r){
		sum[p]=sum[p<<1]+sum[p<<1|1];
	}

	void down(ll p,ll l,ll r){
		ll m=l+r>>1;
		ll ln=m-l+1;
		ll rn=r-m;
		if(add[p]){
			sum[p<<1]+=ln*add[p];
			add[p<<1]+=add[p];
			sum[p<<1|1]+=rn*add[p];
			add[p<<1|1]+=add[p];
			add[p]=0;
		}
	}

	void build(ll p,ll l,ll r,vector<ll>& a){
		if(l==r){
			sum[p]=a[p];
		}else{
			ll m=l+r>>1;
			build(p<<1,l,m,a);
			build(p<<1|1,m+1,r,a);
			up(p,l,r);
		}
		add[p]=0;
	}

	void update(ll p,ll l,ll r,ll x,ll y,ll v){
		if(x<=l&&r<=y){
			sum[p]+=(r-l+1)*v;
			add[p]+=v;
			return;
		}
		ll m=l+r>>1;
		down(p,l,r);
		if(x<=m) update(p<<1,l,m,x,y,v);
		if(y>m) update(p<<1|1,m+1,r,x,y,v);
		up(p,l,r);
	}

	ll query(ll p,ll l,ll r,ll x,ll y){
		if(x<=l&&r<=y){
			return sum[p];
		}
		ll m=l+r>>1;
		down(p,l,r);
		ll ans=0;
		if(x<=m) ans+=query(p<<1,l,m,x,y);
		if(y>m) ans+=query(p<<1|1,m+1,r,x,y);
		return ans;
	}
};

//maintain range maximum and second maximum and their indices
//supporting single-point modification only
//@@@
class segment_tree{
	vector<ll> mx,sem,idx1,idx2;
public:
	segment_tree(ll n):mx(n<<2),sem(n<<2),idx1(n<<2),idx2(n<<2) {}

	void up(ll p,ll l,ll r){
    if(mx[p<<1]>mx[p<<1|1]){
      mx[p]=mx[p<<1];
      sem[p]=max(sem[p<<1],mx[p<<1|1]);
      idx1[p]=idx1[p<<1];
      idx2[p]=sem[p]==sem[p<<1]?idx2[p<<1]:idx1[p<<1|1];
    }else if(mx[p<<1]<mx[p<<1|1]){
      mx[p]=mx[p<<1|1];
      sem[p]=max(mx[p<<1],sem[p<<1|1]);
      idx1[p]=idx1[p<<1|1];
      idx2[p]=sem[p]==mx[p<<1]?idx1[p<<1]:idx2[p<<1|1];
    }else{
      mx[p]=mx[p<<1];
      sem[p]=max(sem[p<<1],sem[p<<1|1]);
      idx1[p]=idx1[p<<1];
      idx2[p]=sem[p]==sem[p<<1]?idx2[p<<1]:idx2[p<<1|1];
    }
	}

	void build(ll p,ll l,ll r,vector<ll>& a){
		if(l==r){
			mx[p]=a[l];
      sem[p]=-1;
      idx1[p]=l;
      idx2[p]=-1;
		}else{
			ll m=l+r>>1;
			build(p<<1,l,m,a);
			build(p<<1|1,m+1,r,a);
			up(p,l,r);
		}
	}

	void update(ll p,ll l,ll r,ll x,ll v){
		if(l==r){
			mx[p]=v;
      sem[p]=-1;
      idx1[p]=l;
      idx2[p]=-1;
			return;
		}
		ll m=l+r>>1;
		if(x<=m) update(p<<1,l,m,x,v);
		else update(p<<1|1,m+1,r,x,v);
		up(p,l,r);
	}

	tuple<ll,ll,ll,ll> query(ll p,ll l,ll r,ll x,ll y){
		if(x<=l&&r<=y){
			return {mx[p],sem[p],idx1[p],idx2[p]};
		}
		ll m=l+r>>1;
		if(y<=m) return query(p<<1,l,m,x,y);
    	else if(x>m) return query(p<<1|1,m+1,r,x,y);
    	else{
    	  auto [lmx,lsem,lidx1,lidx2] =query(p<<1,l,m,x,m);
    	  auto [rmx,rsem,ridx1,ridx2]=query(p<<1|1,m+1,r,m+1,y);
    	  ll maxx,semm,id1,id2;
    	  if(lmx>rmx){
    	    maxx=lmx;
    	    semm=max(lsem,rmx);
    	    id1=lidx1;
    	    id2=semm==lsem?lidx2:ridx1;
    	  }else if(lmx<rmx){
    	    maxx=rmx;
    	    semm=max(lmx,rsem);
    	    id1=ridx1;
    	    id2=semm==lmx?lidx1:ridx2;
    	  }else{
    	    maxx=lmx;
    	    semm=max(lsem,rsem);
    	    id1=lidx1;
    	    id2=semm==lsem?lidx2:ridx2;
    	  }
    	  return {maxx,semm,id1,id2};
    	}
	}
};

//seg+binary search
//https://www.lanqiao.cn/problems/2089/learning/?isWithAnswer=true
class segment_tree{
public:
	vector<ll>& a;
	vector<ll> mn;
	segment_tree(vector<ll>& a):a(a){
		ll n=a.size()-1;
		mn.assign(n<<2,LLONG_MAX);
		build(1,1,n);
	}

	void up(ll p){
		mn[p]=min(mn[p<<1],mn[p<<1|1]);	
	}
	
	void build(ll p,ll l,ll r){
		if(l==r){
			mn[p]=a[l];
			return;
		}
		ll m=l+r>>1;
		build(p<<1,l,m);
		build(p<<1|1,m+1,r);	
		up(p);
	};
	
	void update(ll p,ll l,ll r,ll x,ll v){
		if(l==r){
			mn[p]=v;
			return;
		}
		ll m=l+r>>1;
		if(x<=m) update(p<<1,l,m,x,v);
		else update(p<<1|1,m+1,r,x,v);
		up(p);
	}
	
	bool check(ll p,ll L){
		if(mn[p]==LLONG_MAX) return false;
		if(L>2e9) return true;
		return mn[p]<=L*L;
	}
	
	ll idx;
	bool query(ll p,ll l,ll r,ll x,ll y,ll L){
		if(l==r){
			idx=l;
			return check(p,L);
		}
		ll m=l+r>>1;
		if(x<=m&&check(p<<1,L)&&query(p<<1,l,m,x,y,L)) return true;
		if(y>m&&check(p<<1|1,L)&&query(p<<1|1,m+1,r,x,y,L)) return true;
		return false;
	}
};
//#define int long long
//#define N 100005
//int n,w[N];
//struct node{
//	int l,r,sum,add;
//}tr[N*4];
//
//void pushup(int p){
//	tr[p].sum=tr[p<<1].sum+tr[p<<1|1].sum;
//} 
//
//void pushdown(int p){
//	if(tr[p].add){
//		tr[p<<1].sum+=tr[p].add*(tr[p<<1].r-tr[p<<1].l+1);
//		tr[p<<1|1].sum+=tr[p].add*(tr[p<<1|1].r-tr[p<<1|1].l+1);
//		tr[p<<1].add+=tr[p].add;
//		tr[p<<1|1].add+=tr[p].add;
//		tr[p].add=0;
//	}
//}
//
//void build(int p,int l,int r){
//	
//	
//	if(l==r){
//		tr[p]={l,r,w[l],0};
//		return;
//	}
//	tr[p]={l,r,-1,0};
//	int m=l+r>>1;
//	build(p<<1,l,m);
//	build(p<<1|1,m+1,r);
//	pushup(p);
//}
//
//void update(int p,int x,int y,int k){
//	if(x<=tr[p].l&&tr[p].r<=y){
//		tr[p].sum+=(tr[p].r-tr[p].l+1)*k;
//		tr[p].add+=k;
//		return;
//	}
//	int m=tr[p].l+tr[p].r>>1;
//	pushdown(p);
//	if(x<=m) update(p<<1,x,y,k);
//	if(y>m) update(p<<1|1,x,y,k);
//	pushup(p);
//}
//
//int query(int p,int x,int y){
//	if(x<=tr[p].l&&tr[p].r<=y){
//		return tr[p].sum;
//	}
//	int m=tr[p].l+tr[p].r>>1;
//	pushdown(p);
//	int sum=0;
//	if(x<=m) sum+=query(p<<1,x,y);
//	if(y>m) sum+=query(p<<1|1,x,y);
//	return sum;
//}
//
//signed main(){
//    ios::sync_with_stdio(false);
//    cin.tie(0);cout.tie(0);
//    int n,m;
//    cin>>n>>m;
//    for(int i=1;i<=n;i++){
//    	cin>>w[i];
//	}
//	build(1,1,n);
//	for(int i=0;i<m;i++){
//		int op;
//		cin>>op;
//		if(op==1){
//			int x,y,k;
//			cin>>x>>y>>k;
//			update(1,x,y,k); 
//		}else{
//			int x,y;
//			cin>>x>>y;
//			cout<<query(1,x,y)<<endl;
//		}
//	}
//    return 0;
//}

//class segment_tree{
//#define pl (p<<1)
//#define pr (p<<1|1)
//private:
//	int n;
//	vector<int> l,r;
//	vector<ll> sum,add;
//public:
//	segment_tree() {}
//	segment_tree(int n):n(n),l(n<<2),r(n<<2),sum(n<<2),add(n<<2) {
//		build(1,1,n);
//	}
//	
//	void up(int p){
//		sum[p]=sum[pl]+sum[pr];
//	}
//	
//	void down(int p){
//		if(add[p]){
//			sum[pl]+=add[p]*(r[pl]-l[pl]+1);
//			sum[pr]+=add[p]*(r[pr]-l[pr]+1);
//			add[pl]+=add[p];
//			add[pr]+=add[p];
//			add[p]=0;
//		}
//	}
//	
//	void build(int p,int x,int y){
//		l[p]=x,r[p]=y;
//		sum[p]=add[p]=0;
//		if(x==y){
//			return;
//		}
//		int m=x+y>>1;
//		build(pl,x,m);
//		build(pr,m+1,y);
//		up(p);
//	}
//
//	void update(int p,int x,int y,int k){
//		if(x<=l[p]&&r[p]<=y){
//			sum[p]+=(r[p]-l[p]+1)*k;
//			add[p]+=k;
//			return;
//		}	
//		int m=l[p]+r[p]>>1;
//		down(p);
//		if(x<=m) update(pl,x,y,k);
//		if(y>m) update(pr,x,y,k);
//		up(p);
//	}	
//	
//	ll query(int p,int x,int y){
//		if(x<=l[p]&&r[p]<=y){
//			return sum[p];
//		}
//		int m=l[p]+r[p]>>1;
//		down(p);
//		ll sum=0;
//		if(x<=m) sum+=query(pl,x,y);
//		if(y>m) sum+=query(pr,x,y);
//		return sum;
//	}
//}; 
//
//class segment_tree{
//#define pl (p<<1)
//#define pr (p<<1|1)
//private:
//	int n;
//	vector<int> l,r;
//	vector<ll> sum,reset;
//	vector<bool> lazy;
//public:
//	segment_tree() {}
//	segment_tree(int n):n(n),l(n<<2),r(n<<2),sum(n<<2),reset(n<<2),lazy(n<<2){
//		build(1,1,n);
//	}
//	
//	void up(int p){
//		sum[p]=sum[pl]+sum[pr];
//	}
//	
//	void down(int p){
//		if(lazy[p]){
//			sum[pl]=reset[p]*(r[pl]-l[pl]+1);
//			sum[pr]=reset[p]*(r[pr]-l[pr]+1);
//			reset[pl]=reset[p];
//			reset[pr]=reset[p];
//			lazy[pl]=true;
//			lazy[pr]=true;
//			reset[p]=0;
//			lazy[p]=false;
//		}
//	}
//	
//	void build(int p,int x,int y){
//		l[p]=x,r[p]=y;
//		sum[p]=reset[p]=0;
//		lazy[p]=false;
//		if(x==y){
//			return;
//		}
//		int m=x+y>>1;
//		build(pl,x,m);
//		build(pr,m+1,y);
//		up(p);
//	}
//
//	void update(int p,int x,int y,int k){
//		if(x<=l[p]&&r[p]<=y){
//			sum[p]=(r[p]-l[p]+1)*k;
//			reset[p]=k;
//			lazy[p]=true;
//			return;
//		}	
//		int m=l[p]+r[p]>>1;
//		down(p);
//		if(x<=m) update(pl,x,y,k);
//		if(y>m) update(pr,x,y,k);
//		up(p);
//	}	
//	
//	ll query(int p,int x,int y){
//		if(x<=l[p]&&r[p]<=y){
//			return sum[p];
//		}
//		int m=l[p]+r[p]>>1;
//		down(p);
//		ll sum=0;
//		if(x<=m) sum+=query(pl,x,y);
//		if(y>m) sum+=query(pr,x,y);
//		return sum;
//	}
//}; 
