//https://www.luogu.com.cn/problem/P3835
//@@@
//balanced tree(fhq-treap)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rnd(ll l,ll r){
	return l+rng()%(r-l+1);
}

const ll MAXN=5e5+5;
const ll MAXT=MAXN*50;

ll root[MAXN];
ll cnt=0;
ll lc[MAXT];
ll rc[MAXT];
ll priority[MAXT];
ll key[MAXT];
ll sz[MAXT];

ll create(ll k){
	ll p=++cnt;
	lc[p]=rc[p]=0;
	priority[p]=rnd(1,1e9);
	key[p]=k;
	sz[p]=1;
	return p;
}

ll clone(ll p){
	ll q=++cnt;
	lc[q]=lc[p];
	rc[q]=rc[p];
	priority[q]=priority[p];
	key[q]=key[p];
	sz[q]=sz[p];
	return q;
}

void up(ll p){
	sz[p]=sz[lc[p]]+sz[rc[p]]+1;
}

void split(ll p,ll div,ll& l,ll& r){
	if(!p){
		l=r=0;
		return;
	}
	p=clone(p);
	if(key[p]<=div){
		l=p;
		split(rc[p],div,rc[l],r);
	}else{
		r=p;
		split(lc[p],div,l,lc[r]);
	}
	up(p);
}

ll merge(ll l,ll r){
	if(l==0||r==0){
		return l+r;
	}
	if(priority[l]>=priority[r]){
		l=clone(l);
		rc[l]=merge(rc[l],r);
		up(l);
		return l;
	}else{
		r=clone(r);
		lc[r]=merge(l,lc[r]);
		up(r);
		return r;
	}
}

ll insert(ll p,ll k){
	ll l=0;
	ll r=0;
	split(p,k,l,r);
	ll e=create(k);
	return merge(merge(l,e),r);
}

ll remove(ll p,ll k){
	ll lm=0;
	ll r=0;
	split(p,k,lm,r);
	ll l=0;
	ll m=0;
	split(lm,k-1,l,m);
	return merge(merge(l,merge(lc[m],rc[m])),r);
}

ll small(ll p,ll k){
	if(!p) return 0;
	if(k<=key[p]) return small(lc[p],k);
	return sz[lc[p]]+1+small(rc[p],k);
}

ll get_rank(ll p,ll k){
	return small(p,k)+1;
}

ll at(ll p,ll x){
	if(x<=sz[lc[p]]) return at(lc[p],x);
	if(x<=sz[lc[p]]+1) return p;
	return at(rc[p],x-sz[lc[p]]-1);
}

ll prev(ll p,ll k){
	if(!p) return INT_MIN+1;
	if(k<=key[p]) return prev(lc[p],k);
	return max(key[p],prev(rc[p],k));
}

ll next(ll p,ll k){
	if(!p) return INT_MAX;
	if(k>=key[p]) return next(rc[p],k);
	return min(key[p],next(lc[p],k));
}

void solve(){
	ll n;
	cin>>n;
	for(ll i=1;i<=n;i++){
		ll vs,op,x;
		cin>>vs>>op>>x;
		if(op==1){
			root[i]=insert(root[vs],x);
		}else if(op==2){
			root[i]=remove(root[vs],x);
		}else if(op==3){
			root[i]=root[vs];
			cout<<get_rank(root[vs],x)<<endl;
		}else if(op==4){
			root[i]=root[vs];
			cout<<key[at(root[vs],x)]<<endl;
		}else if(op==5){
			root[i]=root[vs];
			cout<<prev(root[vs],x)<<endl;
		}else{
			root[i]=root[vs];
			cout<<next(root[vs],x)<<endl;
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
