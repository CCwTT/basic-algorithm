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
	vector<ll> key,lc,rc,fa,sz;
	vector<bool> rev;
	ll root=0;
	ll cnt=0;
	splay_tree(ll sz):key(sz),lc(sz),rc(sz),fa(sz),sz(sz),rev(sz){}

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

	void down(ll p){
		if(rev[p]){
			swap(lc[p],rc[p]);
			rev[lc[p]]=!rev[lc[p]];
			rev[rc[p]]=!rev[rc[p]];
			rev[p]=false;
		}
	}

	ll node_at(ll x){
		ll p=root;
		while(p){
			down(p);
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
		sz[cnt]=1;
		fa[cnt]=root;
		rc[root]=cnt;
		splay(cnt,0);
	}

	void reverse(ll l,ll r){
		ll i=node_at(l-1);
		ll j=node_at(r+1);
		splay(i,0);
		splay(j,i);
		rev[lc[rc[root]]]=!rev[lc[rc[root]]];
	}

	vector<ll> inorder(){
		vector<ll> res;
		function<void(ll)> dfs=[&](ll p){
			if(!p) return;
			down(p);
			dfs(lc[p]);
			res.push_back(key[p]);
			dfs(rc[p]);
		};
		dfs(root);
		return res;
	}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	splay_tree spt(n+5);
	spt.insert(0);
	for(ll i=1;i<=n;i++){
		spt.insert(i);
	}
	spt.insert(0);
	for(ll i=1;i<=m;i++){
		ll x,y;
		cin>>x>>y;
		x++,y++;
		spt.reverse(x,y);
	}
	auto ans=spt.inorder();
	for(ll i=1;i<ans.size()-1;i++) cout<<ans[i]<<" ";
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
