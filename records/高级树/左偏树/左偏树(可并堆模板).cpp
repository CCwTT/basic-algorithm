//https://www.luogu.com.cn/problem/P3377#submit
//@@@
//leftist_tree
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

class leftist_tree{
public:
	vector<ll> key,lc,rc,dist,f;
	leftist_tree(ll sz):key(sz),lc(sz),rc(sz),dist(sz,-1),f(sz){
		iota(f.begin(),f.end(),0);
	}

	ll find(ll x){
		return f[x]==x?x:f[x]=find(f[x]);
	}

	ll merge(ll x,ll y){
		if(x==0||y==0) return x+y;
		if(key[x]>key[y]||(key[x]==key[y]&&x>y)) swap(x,y);
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
		lc[x]=rc[x]=0;
		dist[x]=-1;
		key[x]=-1;
		return f[x];
	}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	leftist_tree ltt(n+1);
	for(ll i=1;i<=n;i++){
		cin>>ltt.key[i];
	}
	for(ll i=1;i<=m;i++){
		ll op;
		cin>>op;
		if(op==1){
			ll x,y;
			cin>>x>>y;
			if(ltt.key[x]==-1||ltt.key[y]==-1) continue;
			ll fx=ltt.find(x);
			ll fy=ltt.find(y);
			if(fx==fy) continue;
			ltt.merge(fx,fy);
		}else{
			ll x;
			cin>>x;
			if(ltt.key[x]==-1){
				cout<<-1<<endl;
				continue;
			}
			ll fx=ltt.find(x);
			cout<<ltt.key[fx]<<endl;
			ltt.pop(fx);
		}
	}
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
