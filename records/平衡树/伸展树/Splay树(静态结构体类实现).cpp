//https://www.luogu.com.cn/problem/P3369
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

class splay_tree{         //capsulation
public:                   //capsulation
	struct node{
		ll key,lc,rc,fa,sz;
	};
	ll root=0;
	ll cnt=0;
	vector<node> a;
	splay_tree(ll sz):a(sz) {}

	void up(ll p){
		a[p].sz=a[a[p].lc].sz+a[a[p].rc].sz+1;
	}

	ll side(ll p){
		return a[a[p].fa].lc==p?0:1;
	}

	void rotate(ll p){
		ll f=a[p].fa,g=a[f].fa;
		if(side(p)==0){
			a[f].lc=a[p].rc;
			if(a[f].lc){
				a[a[f].lc].fa=f;
			}
			a[p].rc=f;
		}else{
			a[f].rc=a[p].lc;
			if(a[f].rc){
				a[a[f].rc].fa=f;
			}
			a[p].lc=f;
		}
		if(g){
			if(side(f)==0){
				a[g].lc=p;
			}else{
				a[g].rc=p;
			}
		}
		a[f].fa=p;
		a[p].fa=g;
		up(f);
		up(p);
	}

	void splay(ll p,ll tar){
		ll f=a[p].fa,g=a[f].fa;
		while(f!=tar){
			if(g!=tar){
				if(side(p)==side(f)){
					rotate(f);
				}else{
					rotate(p);
				}
			}
			rotate(p);
			f=a[p].fa;
			g=a[f].fa;
		}
		if(tar==0){
			root=p;
		}
	}

	ll node_at(ll x){
		ll p=root;
		while(p){
			if(x<=a[a[p].lc].sz){
				p=a[p].lc;
			}else if(x<=a[a[p].lc].sz+1){
				return p;
			}else{
				x-=a[a[p].lc].sz+1;
				p=a[p].rc;
			}
		}
		return 0;
	}

	void insert(ll k){
		a[++cnt].key=k;
		a[cnt].sz=1;
		if(!root){
			root=cnt;
			return;
		}
		ll f=0,p=root,sd=0;
		while(p){
			f=p;
			if(k<=a[p].key){
				sd=0;
				p=a[p].lc;
			}else{
				sd=1;
				p=a[p].rc;
			}
		}
		if(sd==0){
			a[f].lc=cnt;
		}else{
			a[f].rc=cnt;
		}
		a[cnt].fa=f;
		splay(cnt,0);
	}

	ll get_rank(ll k){
		ll p=root,pp=root;
		ll res=0;
		while(p){
			pp=p;
			if(k<=a[p].key){
				p=a[p].lc;
			}else{
				res+=a[a[p].lc].sz+1;
				p=a[p].rc;
			}
		}
		splay(pp,0);
		return res+1;
	}

	ll at(ll x){
		ll p=node_at(x);
		splay(p,0);
		return a[p].key;
	}

	ll prev(ll k){
		ll p=root,pp=root;
		ll res=LLONG_MIN;
		while(p){
			pp=p;
			if(k<=a[p].key){
				p=a[p].lc;
			}else{
				res=max(res,a[p].key);
				p=a[p].rc;
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
			if(k>=a[p].key){
				p=a[p].rc;
			}else{
				res=min(res,a[p].key);
				p=a[p].lc;
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
		if(!a[p].lc){
			root=a[p].rc;
		}else if(!a[p].rc){
			root=a[p].lc;
		}else{
			ll q=node_at(rk+1);
			splay(q,p);
			a[q].lc=a[p].lc;
			a[a[q].lc].fa=q;
			up(q);
			root=q;
		}
		if(root){
			a[root].fa=0;
		}
	}
};  //capsulation

void solve(){
	ll n;
	cin>>n;
	splay_tree splay(n+1);    //capsulation
	for(ll i=0;i<n;i++){
		ll op,x;
		cin>>op>>x;
		if(op==1){
			splay.insert(x);	 //capsulation
		}else if(op==2){
			splay.remove(x);	 //capsulation
		}else if(op==3){
			cout<<splay.get_rank(x)<<endl;	 //capsulation
		}else if(op==4){
			cout<<splay.at(x)<<endl;	 //capsulation
		}else if(op==5){
			cout<<splay.prev(x)<<endl;	 //capsulation
		}else{
			cout<<splay.next(x)<<endl;	 //capsulation
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
