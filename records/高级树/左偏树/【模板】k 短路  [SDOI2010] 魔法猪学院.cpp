//https://www.luogu.com.cn/problem/P2483
//@@@
//dijkstra,leftist_tree,dp,priority_queue
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

typedef struct leftist_tree_node{
	ll to;
	double cost;
	leftist_tree_node* lc;
	leftist_tree_node* rc;
	ll dist;
	leftist_tree_node(ll to=0,double cost=0):to(to),cost(cost),lc(nullptr),rc(nullptr),dist(-1) {}
	leftist_tree_node(ll to,double cost,leftist_tree_node* lc,leftist_tree_node* rc,ll dist):to(to),cost(cost),lc(lc),rc(rc),dist(dist) {}	
	
	leftist_tree_node* clone(){
		return new leftist_tree_node(to,cost,lc,rc,dist);
	}
}node;

node* clone(node* p){
	return p?p->clone():nullptr;
}

ll to(node* p){
	return p?p->to:0;
}

double cost(node* p){
	return p?p->cost:0.0;
}

node* lc(node* p){
	return p?p->lc:nullptr;
}

node* rc(node* p){
	return p?p->rc:nullptr;
}

ll dist(node* p){
	return p?p->dist:-1;
}

void set_to(node* p,ll v){
	if(p) p->to=v;
}

void set_cost(node* p,double v){
	if(p) p->cost=v;
}

void set_lc(node* p,node* v){
	if(p) p->lc=v;
}

void set_rc(node* p,node* v){
	if(p) p->rc=v;
}

void set_dist(node* p,ll v){
	if(p) p->dist=v;
}

node* merge(node* x,node* y){
	if(!x||!y) return x?x:y?y:nullptr;
	if(cost(x)>cost(y)) swap(x,y);
	node* h=clone(x);
	set_rc(h,merge(rc(h),y));
	if(dist(lc(h))<dist(rc(h))) swap(h->lc,h->rc);
	set_dist(h,dist(rc(h))+1);
	return h;
}

void solve(){
	ll n,m;
	double money;
	cin>>n>>m>>money;
	vector<vector<tuple<double,ll,ll>>> g(n+1),rg(n+1);
    for(ll i=1;i<=m;i++){
		ll u,v;
		double w;
        cin>>u>>v>>w;
        if(u!=n){
			g[u].emplace_back(w,v,i);
			rg[v].emplace_back(w,u,i);
        }
    }

	vector<ll> path(n+1);
	vector<double> dis(n+1,LLONG_MAX/2);
	dis[n]=0;
	auto dijkstra=[&](){
		priority_queue<pair<double,ll>,vector<pair<double,ll>>,greater<pair<double,ll>>> pq;
		pq.emplace(0,n);
    	while(!pq.empty()){
    	    auto [disu,u]=pq.top();
			pq.pop();
			if(disu>dis[u]) continue;
			for(auto [w,v,e]:rg[u]){
				if(dis[v]>dis[u]+w){
					dis[v]=dis[u]+w;
					path[v]=e;
					pq.emplace(dis[v],v);
				}
			}
    	}
	};
    dijkstra();

	vector<node*> root(n+1);
	auto merge_road=[&](){
		priority_queue<pair<double,ll>,vector<pair<double,ll>>,greater<pair<double,ll>>> pq;
    	for(ll i=1;i<=n;i++){
			pq.emplace(dis[i],i);
    	}
    	while(!pq.empty()){
			auto [disu,u]=pq.top();
			pq.pop();

			for(auto [w,v,e]:g[u]){
				if(e!=path[u]){
					node* e=new node(v,w+dis[v]-dis[u]);
					root[u]=merge(root[u],e);
				}else{
					root[u]=merge(root[u],root[v]);
				}
			}
    	}
	};
    merge_road();

	ll ans=0;
    auto expand=[&]{
    	money-=dis[1];
    	if(money>=0){
    	    ans++;
			priority_queue<pair<double,node*>,vector<pair<double,node*>>,greater<pair<double,node*>>> pq;
    	    if(root[1]!=0){
				pq.emplace(dis[1]+cost(root[1]),root[1]);
    	    }
    	    while(!pq.empty()){
				auto [w,h]=pq.top();
				pq.pop();
    	        money-=w;
    	        if(money<0){
    	            break;
    	        }
    	        ans++;
    	        if(lc(h)!=0){
					pq.emplace(w-cost(h)+cost(lc(h)),lc(h));
    	        }
    	        if(rc(h)!=0){
					pq.emplace(w-cost(h)+cost(rc(h)),rc(h));
    	        }
    	        if(to(h)!=0&&root[to(h)]!=0){
					pq.emplace(w+cost(root[to(h)]),root[to(h)]);
    	        }
    	    }
    	}
	};
	expand();
    cout<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
	ll T=1;
	while(T--){
		solve();
	}
    return 0;
}