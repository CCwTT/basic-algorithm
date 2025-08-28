//https://www.luogu.com.cn/problem/P5055
//@@@
//balanced tree(fhq-treap)
//所有持久化的操作都标记出来了
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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rnd(ll l,ll r){
	return uniform_int_distribution<ll>(l,r)(rng);
}

const ll MAXN=200001;
const ll MAXM=MAXN*100;  //persistent

ll root[MAXN];  //persistent
ll cnt=0;
ll key[MAXM];
ll lc[MAXM];
ll rc[MAXM];
ll sz[MAXM];
ll sum[MAXM];
ll priority[MAXM];
bool rev[MAXM];

ll copy(ll p){   //persistent
	key[++cnt]=key[p];   
	lc[cnt]=lc[p];
	rc[cnt]=rc[p];
	sz[cnt]=sz[p];
	sum[cnt]=sum[p];
	rev[cnt]=rev[p];
	priority[cnt]=priority[p];
	return cnt;
}

void up(ll p){
	sz[p]=sz[lc[p]]+sz[rc[p]]+1;
	sum[p]=sum[lc[p]]+sum[rc[p]]+key[p];
}

void down(ll p){
	if(rev[p]){
		swap(lc[p],rc[p]);
		if(lc[p]){
			lc[p]=copy(lc[p]);  //persistent
			rev[lc[p]]^=1;
		}
		if(rc[p]){
			rc[p]=copy(rc[p]);  //persistent
			rev[rc[p]]^=1;
		}
		rev[p]=false;
	}
}

void split(ll p,ll t,ll& l,ll& r){
	if(!p){
		l=r=0;
		return;
	}
	p=copy(p);  //persistent
	down(p);
	if(sz[lc[p]]+1<=t){
		l=p;
		split(rc[p],t-sz[lc[p]]-1,rc[l],r);
	}else{
		r=p;
		split(lc[p],t,l,lc[r]);
	}
	up(p);
}

ll merge(ll l,ll r){
	if(!l||!r) return l+r;
	if(priority[l]>=priority[r]){
		l=copy(l);  //persistent
		down(l);
		rc[l]=merge(rc[l],r);
		up(l);
		return l;
	}else{
		r=copy(r);  //persistent
		down(r);   
		lc[r]=merge(l,lc[r]);
		up(r);
		return r;
	}
}

void solve(){
	ll n;
	cin>>n;
	ll last_ans=0;
	for(ll i=1;i<=n;i++){
		ll vs,op;
		ll x,y=0;
		cin>>vs>>op>>x;
		x^=last_ans;
		if(op!=2){
			cin>>y;
			y^=last_ans;
		}
		ll lm=0,r=0,l=0,m=0;
		if(op==1){
			split(root[vs],x,l,r);
			key[++cnt]=y;
			sz[cnt]=1;
			sum[cnt]=y;
			priority[cnt]=rnd(1,100000);
			root[i]=merge(merge(l,cnt),r);  //persistent
		}else if(op==2){
			split(root[vs],x,lm,r);
			split(lm,x-1,l,m);
			root[i]=merge(l,r);     //persistent
		}else if(op==3){
			split(root[vs],y,lm,r);
			split(lm,x-1,l,m);
			rev[m]^=1;
			root[i]=merge(merge(l,m),r);  //persistent
		}else{
            root[i]=root[vs];       //persistent
			split(root[vs],y,lm,r);
			split(lm,x-1,l,m);
			last_ans=sum[m];
			cout<<last_ans<<endl;
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
