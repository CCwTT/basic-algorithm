//https://www.luogu.com.cn/problem/P4971
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

class leftist_tree{ //Max-heap
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

	ll remove(ll x){
		f[lc[x]]=lc[x];
		f[rc[x]]=rc[x];
		ll h=find(x);
		f[x]=merge(lc[x],rc[x]);
		
		if(x==h){
			fa[f[x]]=0;
			f[f[x]]=f[x];
		}else{
			fa[f[x]]=fa[x];
			f[f[x]]=h;
			if(lc[fa[x]]==x){
				lc[fa[x]]=f[x];
			}else{
				rc[fa[x]]=f[x];
			}
		}
		ll p=f[x];
        while(fa[p]&&dist[p]+1<dist[fa[p]]){
            dist[fa[p]]=dist[p]+1;
            if(dist[rc[fa[p]]]>dist[lc[fa[p]]]){
                swap(lc[fa[p]],rc[fa[p]]);
            }
            p=fa[p];
        }
		dist[x]=-1;
		fa[x]=lc[x]=rc[x]=dist[x]=0;
		return f[f[x]];
	}

	void add(ll x,ll v){
	    f[x]=remove(x);
	    key[x]=max(0ll,key[x]+v);
	    f[x]=f[f[x]]=merge(x,f[x]);
	}

	ll compute(ll w){
		ll res=0;
		ll mx=0;
		for(ll i=1;i<=n;i++){
			if(f[i]==i){
				res+=key[i];
				if(key[i]>mx){
					mx=key[i];
				}
			}
		}
		if(w==2){
			res-=mx;
		}else if(w==3){
			res+=mx;
		}
		return res;
	}
};

void solve(){
	ll t,w,K;
	cin>>t>>w>>K;
	for(ll i=1;i<=t;i++){
		ll n,m;
		cin>>n>>m;
		leftist_tree ltt(n+1);
		for(ll j=1;j<=n;j++){
			cin>>ltt.key[j];
		}
		for(ll j=1;j<=m;j++){
			ll op,a,b;
			cin>>op;
			if(op==2){
				cin>>a;
				ltt.add(a,-ltt.key[a]);
			}else if(op==3){
				cin>>a>>b;
				ltt.add(ltt.find(a),-b);
			}else{
				cin>>a>>b;
				if(ltt.find(a)!=ltt.find(b)){
					ltt.merge(ltt.find(a),ltt.find(b));
				}
			}
		}
		ll ans=ltt.compute(w);
		if(ans==0){
			cout<<"Gensokyo "<<ans<<endl;
		}else if(ans>K){
			cout<<"Hell "<<ans<<endl;
		}else{
			cout<<"Heaven "<<ans<<endl;
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
