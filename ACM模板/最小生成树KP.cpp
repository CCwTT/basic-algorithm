#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//����LLONG_MAX˵���޷�����MST(��)
//@@@
class Dsu{
public:
	vector<ll> f;
	Dsu(ll n):f(n){
		iota(f.begin(),f.end(),0);
	}
	ll find(ll x){
		return f[x]==x?x:f[x]=find(f[x]);
	}
	void join(ll x,ll y){
		if(!check(x,y)) f[find(y)]=find(x);
	}
	bool check(ll x,ll y){
		return find(x)==find(y);
	}
};
//@@@
ll kruskal(ll n,vector<tuple<ll,ll,ll>>& edges){
	Dsu dsu(n+1);
	sort(edges.begin(),edges.end());
	ll res=0,cnt=0;
	for(auto& edge:edges){
		auto [w,u,v]=edge;
		if(!dsu.check(u,v)){
			dsu.join(u,v);
			res+=w;
			cnt++;
		}
	}
	return cnt==n-1?res:LLONG_MAX;
}

//(��) 
ll prim_normal(vector<vector<pair<ll,ll>>>& g,ll s){
	ll n=g.size();
	ll res=0;
	vector<ll> dis(n,INT_MAX/2);
	dis[s]=0;
	vector<bool> vis(n,false);
	for(ll p=0;p<n;p++){
		ll x=-1;
		for(ll i=0;i<n;i++){
			if(!vis[i]&&(!~x||dis[i]<dis[x])){
				x=i;
			}
		}
		if(dis[x]==INT_MAX/2){
			return LLONG_MAX;
		}
		vis[x]=true;
		res+=dis[x];
		for(auto [y,w]:g[x]){
			if(dis[y]>w) dis[y]=w;
		}
	}
	return res;
}

//(��) 
//ʹ��Prim�㷨һ��Ҫע�⴦���رߣ� 
ll prim_heap(vector<vector<pair<ll,ll>>>& g,ll s){
	ll n=g.size();
	ll res=0;
	ll cnt=0;
	vector<ll> dis(n,INT_MAX/2);
	vector<ll> vis(n,false); 
	dis[s]=0;
	priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<>> pq;
	pq.emplace(0,s);
	while(!pq.empty()){
		auto [disx,x]=pq.top();
		pq.pop();
		if(vis[x]) continue;
		vis[x]=true;
		//if(disx>dis[x]) continue; //���ǲ��Ե�д�� 
		res+=dis[x];
		cnt++;
		for(auto [y,w]:g[x]){
			if(dis[y]>w){
				dis[y]=w;
				pq.emplace(dis[y],y);
			}
		}
	}
	return cnt==n?res:LLONG_MAX;
}

ll prim(vector<vector<pair<ll,ll>>>& g){
	return prim_heap(g,0);
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	ll n,m;
	cin>>n>>m;
	vector<vector<pair<ll,ll>>> g(n);
	vector<tuple<ll,ll,ll>> edges;
	for(ll i=0;i<m;i++){
		ll u,v,w;
		cin>>u>>v>>w;
		u--,v--;
		g[u].emplace_back(v,w);
		g[v].emplace_back(u,w);
		edges.emplace_back(w,u,v);
	} 
	cout<<kruskal(n,edges)<<endl;
	cout<<prim(g)<<endl;
	return 0;
} 


