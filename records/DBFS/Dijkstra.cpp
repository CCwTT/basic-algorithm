//https://vjudge.net/contest/714395#problem/C
//@@@
//non-weighted,1-indexed/
vector<ll> dijkstra(vector<vector<ll>> &g,ll s){
	vector<ll> dis(g.size(),LLONG_MAX/2);
	dis[s]=0;
	priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq;		
	pq.emplace(0,s);
	while(!pq.empty()){
		auto [disx,x]=pq.top();
		pq.pop();
		if(disx>dis[x]) continue;
		for(auto y:g[x]){
			if(dis[y]>dis[x]+1){
				dis[y]=dis[x]+1;
				pq.emplace(dis[x]+1,y);
			}
		}	
	}
	return dis;
}

//@@@
//weighted,0-indexed
vector<ll> dijkstra(vector<vector<pair<ll,ll>>> &g,ll s){
	vector<ll> dis(g.size(),LLONG_MAX/2);
	dis[s]=0;
	priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<>> pq;		
	pq.emplace(0,s);
	while(!pq.empty()){
		auto [disx,x]=pq.top();
		pq.pop();
		if(disx>dis[x]) continue;
		for(auto [y,w]:g[x]){
			if(dis[y]>dis[x]+w){
				dis[y]=dis[x]+w;
				pq.emplace(dis[x]+w,y);
			}
		}	
	}
	return dis;
}

//weighted,1-indexed
vector<ll> dijkstra(vector<vector<pair<ll,ll>>> &g,ll s){
	vector<ll> dis(g.size(),LLONG_MAX/2);
	dis[s]=0;
	priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<>> pq;		
	pq.emplace(0,s);
	while(!pq.empty()){
		auto [disx,x]=pq.top();
		pq.pop();
		if(disx>dis[x]) continue;
		for(auto [y,w]:g[x]){
			if(dis[y]>dis[x]+w){
				dis[y]=dis[x]+w;
				pq.emplace(dis[x]+w,y);
			}
		}	
	}
	return dis;
}