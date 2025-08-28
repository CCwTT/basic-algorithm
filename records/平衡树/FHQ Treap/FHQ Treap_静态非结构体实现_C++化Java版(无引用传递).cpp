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

const ll MAXN=100001;
ll root=0;
ll cnt=0;
ll key[MAXN];
ll lc[MAXN];
ll rc[MAXN];
ll sz[MAXN];
ll priority[MAXN];

void up(ll p){
	sz[p]=sz[lc[p]]+sz[rc[p]]+1;
}

void split(ll p,ll t,ll l,ll r){
	if(!p){
		rc[l]=lc[r]=0;
		return;
	}
	if(key[p]<=t){
		rc[l]=p;
		split(rc[p],t,p,r);
	}else{
		lc[r]=p;
		split(lc[p],t,l,p);
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

void insert(ll k){
	split(root,k,0,0);
	key[++cnt]=k;
	sz[cnt]=1;
	priority[cnt]=ran(1,100000);
	root=merge(merge(rc[0],cnt),lc[0]);
}

void remove(ll k){
	split(root,k,0,0);
	ll lm=rc[0];
	ll r=lc[0];
	split(lm,k-1,0,0);
	ll l=rc[0];
	ll m=lc[0];
	root=merge(merge(l,merge(lc[m],rc[m])),r);
}

ll get_rank(ll k){
	split(root,k-1,0,0);
	ll res=sz[rc[0]]+1;
	root=merge(rc[0],lc[0]);
	return res;
}

ll at(ll p,ll x){
	if(x<=sz[lc[p]]) return at(lc[p],x);
	if(x<=sz[lc[p]]+1) return key[p];
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

