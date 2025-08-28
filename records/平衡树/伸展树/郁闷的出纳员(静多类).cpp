//https://www.luogu.com.cn/problem/P1486#submit
//@@@
//balanced tree(splay)
//操作[l,r](中序遍历编号)方法:
//将l-1提为根，将r+1提为根的右子树根，则[l,r]为根的右子树的左子树
//节点编号是固定的，中序遍历编号是动态变化的
//联系节点编号p和中序遍历编号x的方法:
//p=node_at(x)
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
	vector<ll> key,fa,lc,rc,sz;
	ll root=0,cnt=0;
	splay_tree(ll siz):key(siz),fa(siz),lc(siz),rc(siz),sz(siz){}

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

	void insert(ll x){
		key[++cnt]=x;
		sz[cnt]=1;
		if(!root){
			root=cnt;
		}else{
			ll f=0,p=root,sd=0;
			while(p){
				f=p;
				if(x<=key[p]){
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
	}

	ll at(ll x){
		ll p=root,pp=root;
		while(p){
			pp=p;
			if(x<=sz[lc[p]]){
				p=lc[p];
			}else if(x<=sz[lc[p]]+1){
				break;
			}else{
				x-=sz[lc[p]]+1;
				p=rc[p];
			}
		}
		splay(pp,0);
		return key[pp];
	}
};

void solve(){
	ll n,limit;
	cin>>n>>limit;
	ll change=0,enter=0;
	splay_tree spt(n+1);
	for(ll i=1;i<=n;i++){
		char op;
		ll x;
		cin>>op>>x;
		if(op=='I'){
			if(x>=limit){
				enter++;
				spt.insert(x-change);
			}
		}else if(op=='A'){
			change+=x;
		}else if(op=='S'){
			change-=x;
			ll t=limit-change-1;
			ll p=spt.root;
			ll r=0;
			while(p){
				if(spt.key[p]<=t){
					p=spt.rc[p];
				}else{
					r=p;
					p=spt.lc[p];
				}
			}
			if(!r){
				spt.root=0;
			}else{
				spt.splay(r,0);
				spt.lc[spt.root]=0;
				spt.up(spt.root);
			}
		}else if(op=='F'){
			if(x>spt.sz[spt.root]){
				cout<<-1<<endl;
			}else{
				cout<<spt.at(spt.sz[spt.root]-x+1)+change<<endl;
			}
		}
	}
	cout<<enter-spt.sz[spt.root]<<endl;
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
