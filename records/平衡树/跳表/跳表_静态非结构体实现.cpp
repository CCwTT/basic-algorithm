//https://www.luogu.com.cn/problem/P3369
//@@@
//skip table
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

const ll MAXL=20;
const ll MAXN=100001;
mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count());
ll ran(ll l,ll r){
	return l+RNG()%(r-l+1);
}

ll key[MAXN];
ll val[MAXN];
ll level[MAXN];
ll next_node[MAXN][MAXL+1];
ll cover[MAXN][MAXL+1];
ll cnt;

void build(){
	cnt=1;
	key[cnt]=LLONG_MIN;
	level[cnt]=MAXL;
}

ll random_level(){
	ll res=1;
	while(ran(1,2)==1){
		res++;
	}
	return min(res,MAXL);
}

ll find(ll p,ll h,ll x){
	while(next_node[p][h]!=0&&key[next_node[p][h]]<x){
		p=next_node[p][h];
	}
	if(h==1){
		if(next_node[p][h]!=0&&key[next_node[p][h]]==x){
			return next_node[p][h];
		}else{
			return 0;
		}
	}
	return find(p,h-1,x);
}

void insert_count(ll p,ll h,ll x){
	while(next_node[p][h]!=0&&key[next_node[p][h]]<x){
		p=next_node[p][h];
	}
	if(h==1){
		val[next_node[p][h]]++;
	}else{
		insert_count(p,h-1,x);
	}
	cover[p][h]++;
}

ll insert_node(ll p,ll h,ll q){
	ll right_cnt=0;
	while(next_node[p][h]!=0&&key[next_node[p][h]]<key[q]){
		right_cnt+=cover[p][h];
		p=next_node[p][h];
	}
	if(h==1){
		next_node[q][h]=next_node[p][h];
		next_node[p][h]=q;
		cover[q][h]=val[next_node[q][h]];
		cover[p][h]=val[next_node[p][h]];
		return right_cnt;
	}else{
		ll down_cnt=insert_node(p,h-1,q);
		if(h>level[q]){
			cover[p][h]++;
		}else{
			next_node[q][h]=next_node[p][h];
			next_node[p][h]=q;
			cover[q][h]=cover[p][h]+1-down_cnt-val[q];
			cover[p][h]=down_cnt+val[q];
		}
		return right_cnt+down_cnt;
	}
}

void insert(ll x){
	if(find(1,MAXL,x)!=0){
		insert_count(1,MAXL,x);
	}else{
		key[++cnt]=x;
		val[cnt]=1;
		level[cnt]=random_level();
		insert_node(1,MAXL,cnt);
	}
}

void remove_count(ll p,ll h,ll x){
	while(next_node[p][h]!=0&&key[next_node[p][h]]<x){
		p=next_node[p][h];
	}
	if(h==1){
		val[next_node[p][h]]--;
	}else{
		remove_count(p,h-1,x);
	}
	cover[p][h]--;
}

void remove_node(ll p,ll h,ll q){
	while(next_node[p][h]!=0&&key[next_node[p][h]]<key[q]){
		p=next_node[p][h];
	}
	if(h>level[q]){
		cover[p][h]--;
	}else{
		next_node[p][h]=next_node[q][h];
		cover[p][h]+=cover[q][h]-1;
	}
	if(h>1){
		remove_node(p,h-1,q);
	}
}

void remove(ll x){
	ll q=find(1,MAXL,x);
	if(q!=0){
		if(val[q]>1){
			remove_count(1,MAXL,x);
		}else{
			remove_node(1,MAXL,q);
		}
	}
}

ll small(ll p,ll h,ll x){
	ll right_cnt=0;
	while(next_node[p][h]!=0&&key[next_node[p][h]]<x){
		right_cnt+=cover[p][h];
		p=next_node[p][h];
	}
	if(h==1){
		return right_cnt;
	}else{
		return right_cnt+small(p,h-1,x);
	}
}

ll get_rank(ll x){
	return small(1,MAXL,x)+1;
}

ll at(ll p,ll h,ll x){
	ll cur=0;
	while(next_node[p][h]!=0&&cur+cover[p][h]<x){
		cur+=cover[p][h];
		p=next_node[p][h];
	}
	if(h==1){
		return key[next_node[p][h]];
	}else{
		return at(p,h-1,x-cur);
	}
}

ll at(ll x){
	return at(1,MAXL,x);
}

ll  prev(ll p,ll h,ll x){
	while(next_node[p][h]!=0&&key[next_node[p][h]]<x){
		p=next_node[p][h];
	}
	if(h==1){
		return key[p];
	}else{
		return prev(p,h-1,x);
	}
}

ll prev(ll x){
	return prev(1,MAXL,x);
}

ll next(ll p,ll h,ll x){
	while(next_node[p][h]!=0&&key[next_node[p][h]]<=x){
		p=next_node[p][h];
	}
	if(h==1){
		if(next_node[p][h]==0){
			return LLONG_MAX;
		}
		return key[next_node[p][h]];
	}else{
		return next(p,h-1,x); 
	}
}

ll next(ll x){
	return next(1,MAXL,x);
}

void solve(){
	build();
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
