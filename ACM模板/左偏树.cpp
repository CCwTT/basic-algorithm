class leftist_tree{  //Max-heap
public:
	ll n;
	vector<ll> key,lc,rc,fa,dist,f;
	leftist_tree(ll sz):n(sz-1),key(sz),lc(sz),rc(sz),fa(sz),dist(sz,-1),f(sz){
		iota(f.begin(),f.end(),0);
	}

	ll find(ll x){
		return f[x]==x?x:f[x]=find(f[x]);
	}

	ll merge(ll x,ll y){  //Max-heap
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
		key[x]=dist[x]=-1;
        lc[x]=rc[x]=fa[x]=0;
		return f[x];
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
	    key[x]+=v;
	    f[x]=f[f[x]]=merge(x,f[x]);
	}
};