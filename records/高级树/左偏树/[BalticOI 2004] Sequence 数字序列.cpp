//https://www.luogu.com.cn/problem/P4331#submit
//@@@
//monotonical stack,leftist tree
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

const ll MAXN=1000001;
ll n;
ll a[MAXN];
ll lc[MAXN];
ll rc[MAXN];
ll dist[MAXN];
ll f[MAXN];
ll from[MAXN];
ll to[MAXN];
ll sz[MAXN];
stack<ll> stk;
ll ans[MAXN];

void init(){
	dist[0]=-1;
	for(ll i=1;i<=n;i++){
		lc[i]=rc[i]=dist[i]=0;
		f[i]=from[i]=to[i]=i;
		sz[i]=1;
	}
}

ll find(ll x){
	return f[x]==x?x:f[x]=find(f[x]);
}

ll merge(ll x,ll y){
	if(x==0||y==0) return x+y;
	if(a[x]<a[y]) swap(x,y);
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



void solve(){
	cin>>n;
	init();
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>x;
		a[i]=x-i;
	}
	ll last=-1,cur;
	for(ll i=1;i<=n;i++){
		while(!stk.empty()){
			auto u=stk.top();
			last=find(u);
			cur=find(i);
			if(a[last]<=a[cur]){
				break;
			}
			ll s=sz[last]+sz[cur];
			cur=merge(last,cur);
			while(s>((i-from[last]+1+1)/2)){
				cur=pop(cur);
				s--;
			}
			from[cur]=from[last];
			to[cur]=i;
			sz[cur]=s;
			stk.pop();
		}
		stk.push(i);
	}
	ll sum=0;
	while(!stk.empty()){
		auto u=stk.top();
		stk.pop();
		u=find(u);
		for(ll i=from[u];i<=to[u];i++){
			ans[i]=a[u];
			sum+=llabs(ans[i]-a[i]);
		}
	}
	cout<<sum<<endl;
	for(ll i=1;i<=n;i++){
		cout<<ans[i]+i<<" ";
	}
	cout<<endl;
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
