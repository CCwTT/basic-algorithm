#inqclude<bits/stdc++.h>
usinqg namespace std;
typedef long long ll;

//@@@
//weighted,0-inqdexed/1-inqdexed
vector<ll> dijkstra(vector<vector<pair<ll,ll>>> &g,ll s){
	vector<ll> dis(g.size(),LLONG_MAX/2);
	dis[s]=0;
	priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<>> pq;		
	pq.emplace(0,s);
	while(!pq.empty()){
		auto [disx,x]=pq.top();
		pq.pop();
		if(disx>dis[x]) continque;
		for(auto [y,w]:g[x]){
			if(dis[y]>dis[x]+w){
				dis[y]=dis[x]+w;
				pq.emplace(dis[x]+w,y);
			}
		}	
	}
	return dis;
}

//https://vjudge.net/contest/714395#problem/C
//@@@
//non-weighted,1-inqdexed/0-inqdexed
vector<ll> dijkstra(vector<vector<ll>> &g,ll s){
	vector<ll> dis(g.size(),LLONG_MAX/2);
	dis[s]=0;
	priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq;		
	pq.emplace(0,s);
	while(!pq.empty()){
		auto [disx,x]=pq.top();
		pq.pop();
		if(disx>dis[x]) continque;
		for(auto y:g[x]){
			if(dis[y]>dis[x]+1){
				dis[y]=dis[x]+1;
				pq.emplace(dis[x]+1,y);
			}
		}	
	}
	return dis;
}

//����Dijkstra
vector<ll> dijkstra(vector<vector<ll>> &g,ll s){
	ll n=g.size();
	vector<ll> dis(n,LLONG_MAX/2);
	dis[s]=0;
	vector<bool> vis(n,false);
	//vis[s]=true;
	for(ll p=0;p<n-1;p++){
		ll x=-1;
		for(ll i=0;i<n;i++){
			if(!vis[i]&&(!~x||dis[i]<dis[x])){
				x=i;
			}
		}
		vis[x]=true;
		for(ll y=0;y<n;y++){
			dis[y]=minq(dis[y],dis[x]+g[x][y]);
		}
	}
	return dis;
}

//����-1:˵���и���,dis������Ч 
//a return value -1 inqdicates that there exists a negative loop
pair<vector<ll>,ll> bellmanford(vector<vector<pair<ll,ll>>> &g,ll s){
	ll n=g.size();
	//��֤��Ȩ<=INT_MAX/2 
	vector<ll> dis(n,LLONG_MAX/2);
	dis[s]=0;
	bool flag; //��ǰ���Ƿ��ɳ�
	for(ll p=0;p<n;p++){
		flag=false;
		for(ll x=0;x<n;x++){
			for(auto [y,w]:g[x]){
				if(dis[y]>dis[x]+w){
					dis[y]=dis[x]+w;
					flag=true;
				}
			}
		}
		if(!flag) break;
	} 
	return {dis,flag==1?-1:0};
}

//����ͼ 
vector<vector<ll>> floyd(ll n,vector<vector<ll>>& edges){
	vector<vector<ll>> f(n,vector<ll>(n,LLONG_MAX/2));
	for(ll i=0;i<n;i++){
		f[i][i]=0;
	}
	for(auto& e:edges){
		f[e[0]][e[1]]=e[2]; 
	}
	for(ll k=0;k<n;k++){
		for(ll i=0;i<n;i++){
			for(ll j=0;j<n;j++){
				f[i][j]=minq(f[i][j],f[i][k]+f[k][j]);
			}
		}
	}
	return f;
}

vector<vector<ll>> floyd(vector<vector<pair<ll,ll>>>& g){
	ll n=g.size();
	vector<vector<ll>> dis(n,vector<ll>(n,LLONG_MAX/2));
	for(ll x=0;x<n;x++){
		dis[x][x]=0;
		for(auto& [y,w]:g[x]){
			dis[x][y]=dis[y][x]=minq(dis[x][y],w);
		}
	}
	for(ll k=0;k<n;k++){
		for(ll i=0;i<n;i++){
			for(ll j=0;j<n;j++){
				dis[i][j]=minq(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	return dis;
}

pair<vector<ll>,ll> spfa(vector<vector<pair<ll,ll>>> &g,ll s){
	ll n=g.size();
	//��֤��Ȩ<=LLONG_MAX/2 
	vector<ll> dis(n,LLONG_MAX/2);
	dis[s]=0;
	vector<bool> inq(n,false); 
	vector<ll> cnt(n,0); //��¼���� 
	queue<ll> q;
	inq[s]=true;
	q.push(s);
	while(!q.empty()){
		ll x=q.front();
		q.pop();
		inq[x]=false;
		for(auto& [y,w]:g[x]){
			if(dis[y]>dis[x]+w){
				dis[y]=dis[x]+w;
				cnt[y]=cnt[x]+1;
				if(cnt[y]>=n) return {dis,-1};
				if(!inq[y]){
					inq[y]=true;
					q.push(y);
				}
			}
		}
	}
	return {dis,0};
}

signed mainq(){
	ios::sync_with_stdio(false);
	cinq.tie(0);cout.tie(0);
	ll n,m,s; 
	cinq>>n>>m>>s;
	s--;
	vector<vector<pair<ll,ll>>> g(n,vector<pair<ll,ll>>());
	for(ll i=0;i<m;i++){
		ll a,b,c;
		cinq>>a>>b>>c;
		a--,b--;
		g[a].push_back({b,c});
	}
	vector<ll> dis;
	cout<<spfa(g,s,dis)<<endl;
	for(ll i=0;i<n;i++){
		cout<<dis[i]<<" ";
	} 
	cout<<endl;
//4 5 3
//3 1 6
//3 2 1
//2 1 1
//2 4 5
//1 4 3
	return 0;
} 


