#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void Log(vector<ll>& a){
	cout<<"Log: ";
	for(int i=0;i<a.size();i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
const ll MAXN=100001;
ll n,m;
ll leader[MAXN];
ll cost[MAXN];
ll ability[MAXN];
ll lc[MAXN];
ll rc[MAXN];
ll dist[MAXN];
ll f[MAXN];
ll sz[MAXN];
ll sum[MAXN];

ll find(ll x){
	return f[x]==x?x:f[x]=find(f[x]);
}

ll merge(ll x,ll y){
	if(x==0||y==0) return x+y;
	if(cost[x]<cost[y]) swap(x,y);
	rc[x]=merge(rc[x],y);
	if(dist[lc[x]]<dist[rc[x]]) swap(lc[x],rc[x]);
	dist[x]=dist[rc[x]]+1;
	f[lc[x]]=f[rc[x]]=x;
	return x;
}

ll pop(ll x){
	f[lc[x]]=lc[x];
	f[rc[x]]=rc[x];
	f[x]=merge(lc[x],rc[x]);
	lc[x]=rc[x]=dist[x]=0;
	return f[x];
}

void init(){
	dist[0]=-1;
	for(ll i=1;i<=n;i++){
		lc[i]=rc[i]=dist[i]=0;
		sz[i]=1;
		sum[i]=cost[i];
		f[i]=i;
	}
}

void solve(){
	cin>>n>>m;
	for(ll i=1;i<=n;i++){
		cin>>leader[i]>>cost[i]>>ability[i];
	}
	init();
	ll ans=0;
	ll p,psize,h,hsize;
	ll hsum,psum;
	for(ll i=n;i>=1;i--){
		h=find(i);
		hsize=sz[h];
		hsum=sum[h];
		while(hsum>m){
			pop(h);
			hsize--;
			hsum-=cost[h];
			h=find(i);
		}
		ans=max(ans,hsize*ability[i]);
		if(i>1){
			p=find(leader[i]);
			psize=sz[p];
			psum=sum[p];
			f[p]=f[h]=merge(p,h);
			sz[f[p]]=psize+hsize;
			sum[f[p]]=psum+hsum;
		}
	}
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
