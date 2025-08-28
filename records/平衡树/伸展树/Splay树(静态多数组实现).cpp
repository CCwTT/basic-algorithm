//https://www.luogu.com.cn/problem/P3369#submit
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

const ll MAXN=1e5+1;

ll root=0;
ll cnt=0;
ll key[MAXN];
ll fa[MAXN];
ll lc[MAXN];
ll rc[MAXN];
ll sz[MAXN];

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
		if(lc[f]){
			fa[lc[f]]=f;
		}
		rc[p]=f;
	}else{
		rc[f]=lc[p];
		if(rc[f]){
			fa[rc[f]]=f;
		}
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

ll node_at(ll rk){
	ll p=root;
	while(p){
		if(rk<=sz[lc[p]]){
			p=lc[p];
		}else if(rk<=sz[lc[p]]+1){
			return p;
		}else{
			rk-=sz[lc[p]]+1;
			p=rc[p];
		}
	}
	return 0;
}

void insert(ll k){
	key[++cnt]=k;
	sz[cnt]=1;
	if(!root){
		root=cnt;
		return;
	}
	ll f=0,p=root,sd=0;
	while(p){
		f=p;
		if(k<=key[p]){
			sd=0;
			p=lc[p];
		}else{
			sd=1;
			p=rc[p];
		}
	}
	if(sd==0){
		lc[f]=cnt;
	}else{
		rc[f]=cnt;
	}
	fa[cnt]=f;
	splay(cnt,0);
}

ll get_rank(ll k){
	ll p=root,pp=root;
	ll res=0;
	while(p){
		pp=p;
		if(k<=key[p]){
			p=lc[p];
		}else{
			res+=sz[lc[p]]+1;
			p=rc[p];
		}
	}
	splay(pp,0);
	return res+1;
}

ll at(ll x){
	ll p=node_at(x);
	splay(p,0);
	return key[p];
}

ll prev(ll k){
	ll p=root,pp=root;
	ll res=LLONG_MIN;
	while(p){
		pp=p;
		if(k<=key[p]){
			p=lc[p];
		}else{
			res=max(res,key[p]);
			p=rc[p];
		}
	}
	splay(pp,0);
	return res;
}

ll next(ll k){
	ll p=root,pp=root;
	ll res=LLONG_MAX;
	while(p){
		pp=p;
		if(k>=key[p]){
			p=rc[p];
		}else{
			res=min(res,key[p]);
			p=lc[p];
		}
	}
	splay(pp,0);
	return res;
}

void remove(ll k){
	ll rk=get_rank(k);
	if(rk==get_rank(k+1)) return;
	ll p=node_at(rk);
	splay(p,0);
	if(!lc[p]){
		root=rc[p];
	}else if(!rc[p]){
		root=lc[p];
	}else{
		ll q=node_at(rk+1);
		splay(q,p);
		lc[q]=lc[p];
		fa[lc[q]]=q;
		up(q);
		root=q;
	}
	if(root){
		fa[root]=0;
	}
}

void solve(){
	ll n;
	cin>>n;
	for(ll i=0;i<n;i++){
		ll op,x;
		cin>>op>>x;
		if(op==1){
			insert(x);
		}else if(op==2){
			remove(x);
		}else if(op==3){
			cout<<get_rank(x)<<endl;
		}else if(op==4){
			cout<<at(x)<<endl;
		}else if(op==5){
			cout<<prev(x)<<endl;
		}else{
			cout<<next(x)<<endl;
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
