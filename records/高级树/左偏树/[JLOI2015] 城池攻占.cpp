//https://www.luogu.com.cn/problem/P3261
//@@@
//lazy tag,leftist tree,fixed-point-dsu
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

const ll MAXN=300001;
ll n,m;
ll defend[MAXN];
ll leader[MAXN];
ll type[MAXN];
ll gain[MAXN];
ll attack[MAXN];
ll first[MAXN];
ll deep[MAXN];
ll top[MAXN];
ll sacrifice[MAXN];
ll die[MAXN];
ll lc[MAXN];
ll rc[MAXN];
ll dist[MAXN];
ll mul[MAXN];
ll add[MAXN];

void init(){
	dist[0]=-1;
	for(ll i=1;i<=m;i++){
		lc[i]=rc[i]=dist[i]=0;
		mul[i]=1;
		add[i]=0;
	}
	for(ll i=1;i<=n;i++){
		sacrifice[i]=top[i]=0;
	}
}

void upgrade(ll p,ll t,ll v){
	if(t==0){
		attack[p]+=v;
		add[p]+=v;
	}else{
		attack[p]*=v;
		mul[p]*=v;
		add[p]*=v;
	}
}

void apply(ll p,ll v1,ll v2){
	if(!p) return;
	attack[p]=attack[p]*v1+v2;
	mul[p]*=v1;
	add[p]=add[p]*v1+v2;
}

void down(ll p){
	if(mul[p]!=1||add[p]!=0){
		apply(lc[p],mul[p],add[p]);
		apply(rc[p],mul[p],add[p]);
		mul[p]=1;
		add[p]=0;
	}
}

ll merge(ll x,ll y){
	if(x==0||y==0) return x+y;
	if(attack[x]>attack[y]){
		swap(x,y);
	}
	down(x);
	rc[x]=merge(rc[x],y);
	if(dist[lc[x]]<dist[rc[x]]){
		swap(lc[x],rc[x]);
	}
	dist[x]=dist[rc[x]]+1;
	return x;
}

ll pop(ll x){
	down(x);
	ll nx=merge(lc[x],rc[x]);
	lc[x]=rc[x]=0;
	dist[x]=-1;
	return nx;
}

void compute(){
	deep[1]=1;
	for(ll i=2;i<=n;i++){
		deep[i]=deep[leader[i]]+1;
	}
	for(ll i=1;i<=m;i++){
		if(top[first[i]]==0){
			top[first[i]]=i;
		}else{
			top[first[i]]=merge(top[first[i]],i);
		}
	}
	for(ll i=n;i>=1;i--){
		while(top[i]!=0&&attack[top[i]]<defend[i]){
			die[top[i]]=i;
			sacrifice[i]++;
			top[i]=pop(top[i]);
		}
		if(top[i]!=0){
			upgrade(top[i],type[i],gain[i]);
			if(top[leader[i]]==0){
				top[leader[i]]=top[i];
			}else{
				top[leader[i]]=merge(top[leader[i]],top[i]);
			}
		}
	}
}

void solve(){
	cin>>n>>m;
	init();
	for(ll i=1;i<=n;i++){
		cin>>defend[i];
	}
	for(ll i=2;i<=n;i++){
		cin>>leader[i]>>type[i]>>gain[i];
	}
	for(ll i=1;i<=m;i++){
		cin>>attack[i]>>first[i];
	}
	compute();
	for(ll i=1;i<=n;i++){
		cout<<sacrifice[i]<<endl;
	}
	for(ll i=1;i<=m;i++){
		cout<<deep[first[i]]-deep[die[i]]<<endl;
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
