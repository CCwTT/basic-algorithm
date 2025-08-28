//https://www.luogu.com.cn/problem/P2596#submit
//@@@
//balanced tree(splay)
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

class splay_tree{
public:
	vector<ll> key,lc,rc,fa,sz,mp;
	ll root=0;
	ll cnt=0;
	splay_tree(ll sz):key(sz),lc(sz),rc(sz),fa(sz),sz(sz),mp(sz) {}

	void up(ll p){
		sz[p]=sz[lc[p]]+sz[rc[p]]+1;
	}

	ll side(ll p){
		return lc[fa[p]]==p?0:1;
	}

	void rotate(ll p){
		ll f=fa[p],g=fa[f];
		if(side(p)==0){
			lc[f]=rc[p];
			if(lc[f]) fa[lc[f]]=f;
			rc[p]=f;
		}else{
			rc[f]=lc[p];
			if(rc[f]) fa[rc[f]]=f;
			lc[p]=f;
		}
		if(g){
			if(side(f)==0){
				lc[g]=p;
			}else{
				rc[g]=p;
			}
		}
		fa[f]=p;
		fa[p]=g;
		up(f);
		up(p);
	}

	void splay(ll p,ll tar){
		ll f=fa[p],g=fa[f];
		while(f!=tar){
			if(g!=tar){
				if(side(p)==side(f)){
					rotate(f);
				}else{
					rotate(p);
				}
			}
			rotate(p);
			f=fa[p];
			g=fa[f];
		}
		if(tar==0){
			root=p;
		}
	}

	ll node_at(ll x){
		ll p=root;
		while(p){
			if(x<=sz[lc[p]]){
				p=lc[p];
			}else if(x<=sz[lc[p]]+1){
				return p;
			}else{
				x-=sz[lc[p]]+1;
				p=rc[p];
			}
		}
		return 0;
	}

	void insert(ll k){
		key[++cnt]=k;
		mp[k]=cnt;
		sz[cnt]=1;
		fa[cnt]=root;
		rc[root]=cnt;
		splay(cnt,0);
	}

	ll small(ll k){
		ll p=mp[k];
		splay(p,0);
		return sz[lc[p]];
	}

	ll at(ll x){
		ll p=node_at(x);
		splay(p,0);
		return key[p];
	}

	void move(ll a,ll b){
		ll l=node_at(a-1);
		ll r=node_at(a+1);
		splay(l,0);
		splay(r,l);
		ll i=lc[r];
		lc[r]=0;
		up(r);
		up(l);
		l=node_at(b-1);
		r=node_at(b);
		splay(l,0);
		splay(r,l);
		lc[r]=i;
		fa[i]=r;
		up(r);
		up(l);
	}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	splay_tree spt(n+5);
	spt.insert(0);
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>x;
		spt.insert(x);
	}
	spt.insert(0);
	n+=2;
	for(ll i=1;i<=m;i++){
		string op;
		ll x0;
		cin>>op>>x0;
		ll x=spt.small(x0)+1;
		if(op=="Top"){
			spt.move(x,2);
		}else if(op=="Bottom"){
			spt.move(x,n-1);
		}else if(op=="Insert"){
			ll t;
			cin>>t;
			spt.move(x,x+t);
		}else if(op=="Ask"){
			cout<<x-2<<endl;
		}else{
			cout<<spt.at(x0+1)<<endl;
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
