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

mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count());
ll ran(ll l,ll r){
	return l+RNG()%(r-l+1);
}

const ll MAXN=1e5+1;
ll root=0,cnt=0;
ll key[MAXN];
ll val[MAXN];
ll lc[MAXN];
ll rc[MAXN];
ll sz[MAXN];
ll priority[MAXN];

void up(ll p){
	sz[p]=sz[lc[p]]+sz[rc[p]]+val[p];
}

void split(ll p,ll t,ll& l,ll& r){
	if(!p){
		l=r=0;
		return;
	}
	if(key[p]<=t){
		l=p;
		split(rc[p],t,rc[p],r);
	}else{
		r=p;
		split(lc[p],t,l,lc[p]);
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

ll find(ll p,ll k){
	if(!p) return 0;
	if(k==key[p]) return p;
	if(k<key[p]) return find(lc[p],k);
	return find(rc[p],k);
}

void add_count(ll p,ll k,ll v){
	if(k==key[p]){
		val[p]+=v;
	}else if(k<key[p]){
		add_count(lc[p],k,v);
	}else{
		add_count(rc[p],k,v);
	}
	up(p);
}

void insert(ll k){
	if(find(root,k)){
		add_count(root,k,1);
		return;
	}
	ll l=0;
	ll r=0;
	split(root,k,l,r);
	key[++cnt]=k;
	val[cnt]=sz[cnt]=1;
	priority[cnt]=ran(1,100000);
	root=merge(merge(l,cnt),r);
}

void remove(ll k){
	ll p=find(root,k);
	if(!p) return;
	if(val[p]>1){
		add_count(root,k,-1);
	}else{
		ll lm=0;
		ll r=0;
		split(root,k,lm,r);
		ll l=0;
		ll m=0;
		split(lm,k-1,l,m);
		root=merge(l,r);
	}
}

ll small(ll p,ll k){
	if(!p) return 0;
	if(k<=key[p]) return small(lc[p],k);
	return sz[lc[p]]+val[p]+small(rc[p],k);
}

ll get_rank(ll k){
	return small(root,k)+1;
}

ll at(ll p,ll x){
	if(x<=sz[lc[p]]) return at(lc[p],x);
	if(x<=sz[lc[p]]+val[p]) return key[p];
	return at(rc[p],x-sz[lc[p]]-val[p]);
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
