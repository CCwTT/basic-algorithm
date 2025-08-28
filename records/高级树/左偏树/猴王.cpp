//https://www.luogu.com.cn/problem/P1456
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
	ll n;
	vector<ll> key,lc,rc,fa,dist,f;
	leftist_tree(ll sz):n(sz-1),key(sz),lc(sz),rc(sz),fa(sz),dist(sz,-1),f(sz){
		iota(f.begin(),f.end(),0);
	}

	ll find(ll x){
		return f[x]==x?x:f[x]=find(f[x]);
	}

	ll merge(ll x,ll y){
		if(x==0||y==0) return x+y;
		if(key[x]<key[y]||(key[x]==key[y]&&x>y)){
			swap(x,y);
		}
		rc[x]=merge(rc[x],y);
		fa[rc[x]]=x;
		if(dist[lc[x]]<dist[rc[x]]){
			swap(lc[x],rc[x]);
		}
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

	ll remove(ll x){
		ll fx=find(x);
		f[lc[x]]=lc[x];
		f[rc[x]]=rc[x];
		ll y=merge(lc[x],rc[x]);
		ll z=fa[x];
		f[x]=y;
		fa[y]=z;
		if(fx!=x){
			f[y]=fx;
			if(lc[z]==x){
				lc[z]=y;
			}else{
				rc[z]=y;
			}
			for(ll d=dist[y];dist[z]>d+1;d++,z=fa[z]){
				dist[z]=d+1;
				if(dist[lc[z]]<dist[rc[z]]){
					swap(lc[z],rc[z]);
				}
			}
		}
		fa[x]=lc[x]=rc[x]=dist[x]=0;
		return f[y];
	}

	void add(ll x,ll v){
		ll y=remove(x);
		key[x]=max(key[x]+v,0ll);
		f[y]=f[x]=merge(y,x);
	}

	ll fight(ll x,ll y){
		ll fx=find(x),fy=find(y);
		if(fx==fy) return -1;
		ll x1=pop(fx);
		ll y1=pop(fy);
		key[fx]/=2;
		key[fy]/=2;
		f[fx]=f[fy]=f[x1]=f[y1]=merge(merge(x1,fx),merge(y1,fy));
		return key[f[fx]];
	}
};

void solve(){
	ll n;
	while(cin>>n){
		leftist_tree ltt(n+1);
		for(ll i=1;i<=n;i++){
			cin>>ltt.key[i];
		}
		ll m;
		cin>>m;
		for(ll i=1;i<=m;i++){
			ll x,y;
			cin>>x>>y;
			cout<<ltt.fight(x,y)<<endl;
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
