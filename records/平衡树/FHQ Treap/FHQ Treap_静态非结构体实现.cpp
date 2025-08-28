//https://www.luogu.com.cn/problem/P3369
//@@@
//balanced tree(FHQ treap) model
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count());
ll rnd(ll l,ll r){
	return l+RNG()%(r-l+1);
}

const ll MAXN=100001;
ll root=0;
ll cnt=0;
ll key[MAXN];
ll lc[MAXN];
ll rc[MAXN];
ll sz[MAXN];
ll priority[MAXN];

ll create(ll k){
	ll p=++cnt;
	lc[p]=0;
	rc[p]=0;
	key[p]=k;
	sz[p]=1;
	priority[p]=rnd(1,100000);
	return p;
}

void up(ll p){
	sz[p]=sz[lc[p]]+sz[rc[p]]+1;
}

void split(ll p,ll div,ll& l,ll& r){
	if(!p){
		l=r=0;
		return;
	}
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
	if(!l||!r) return l+r;
	if(priority[l]>=priority[r]){
		rc[l]=merge(rc[l],r);
		up(l);
		return l;
	}else{
		lc[r]=merge(l,lc[r]);
		up(r);
		return r;
	}
}

ll insert(ll k){
	ll l=0;
	ll r=0;
	split(root,k,l,r);
	ll e=create(k);
	return merge(merge(l,e),r);
}

ll remove_one(ll k){
	ll lm=0;
	ll r=0;
	split(root,k,lm,r);
	ll l=0;
	ll m=0;
	split(lm,k-1,l,m);
	return merge(merge(l,merge(lc[m],rc[m])),r);
}

ll remove_all(ll k){
	ll lm=0;
	ll r=0;
	split(root,k,lm,r);
	ll l=0;
	ll m=0;
	split(lm,k-1,l,m);
	return merge(l,r);
}

ll small(ll p,ll k){
	if(!p) return 0;
	if(k<=key[p]) return small(lc[p],k);
	return sz[lc[p]]+1+small(rc[p],k);
}

ll get_rank(ll k){
	return small(root,k)+1;
}

ll at(ll p,ll x){
	if(x<=sz[lc[p]]) return at(lc[p],x);
	if(x<=sz[lc[p]]+1) return p;
	return at(rc[p],x-sz[lc[p]]-1);
}

ll at(ll x){
	return at(root,x);
}

ll prev(ll p,ll k){
	if(!p) return LLONG_MIN;
	if(k<=key[p]) return prev(lc[p],k);
	return max(key[p],prev(rc[p],k));
}

ll prev(ll k){
	return prev(root,k);
}

ll next(ll p,ll k){
	if(!p) return LLONG_MAX;
	if(k>=key[p]) return next(rc[p],k);
	return min(key[p],next(lc[p],k));
}

ll next(ll k){
	return next(root,k);
}

void solve(){
	ll n;
	cin>>n;
	for(ll i=1;i<=n;i++){
		ll op,x;
		cin>>op>>x;
		if(op==1){
			root=insert(x);
		}else if(op==2){
			root=remove_one(x);
		}else if(op==3){
			cout<<get_rank(x)<<endl;
		}else if(op==4){
			cout<<key[at(x)]<<endl;
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

