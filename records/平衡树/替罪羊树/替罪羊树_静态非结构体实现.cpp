//https://www.luogu.com.cn/problem/P3369
//@@@
//balanced tree(scapegoat tree)
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

const double ALPHA=0.7;
const ll MAXN=100001;
ll root=0;
ll cnt=0;
ll key[MAXN];
ll val[MAXN];
ll lc[MAXN];
ll rc[MAXN];
ll sz[MAXN];
ll diff[MAXN];
vector<ll> collect;
ll top;
ll father;
ll side;

ll init(ll k){
	key[++cnt]=k;
	lc[cnt]=rc[cnt]=0;
	val[cnt]=sz[cnt]=diff[cnt]=1;
	return cnt;
}

void up(ll p){
	sz[p]=sz[lc[p]]+sz[rc[p]]+val[p];
	diff[p]=diff[lc[p]]+diff[rc[p]]+(val[p]>0?1:0);
}

void inorder(ll p){
	if(p){
		inorder(lc[p]);
		if(val[p]>0){
			collect.push_back(p);
		}
		inorder(rc[p]);
	}
}

ll build(ll l,ll r){
	if(l>r){
		return 0;
	}
	ll m=(l+r)>>1;
	ll p=collect[m];
	lc[p]=build(l,m-1);
	rc[p]=build(m+1,r);
	up(p);
	return p;
}

void rebuild(){
	if(top!=0){
		collect.clear();
		inorder(top);
		if(collect.size()){
			if(father==0){
				root=build(0,collect.size()-1);
			}else if(side==1){
				lc[father]=build(0,collect.size()-1);
			}else{
				rc[father]=build(0,collect.size()-1);
			}
		}
	}
}

bool balance(ll p){
	return ALPHA*diff[p]>=max(diff[lc[p]],diff[rc[p]]);
}

void insert(ll p,ll fa,ll s,ll k){
	if(p==0){
		if(fa==0){
			root=init(k);
		}else if(s==1){
			lc[fa]=init(k);
		}else{
			rc[fa]=init(k);
		}
	}else{
		if(k==key[p]){
			val[p]++;
		}else if(k<key[p]){
			insert(lc[p],p,1,k);
		}else{
			insert(rc[p],p,2,k);
		}
		up(p);
		if(!balance(p)){
			top=p;
			father=fa;
			side=s;
		}
	}
}

void insert(ll k){
	top=father=side=0;
	insert(root,0,0,k);
	rebuild();
}

ll small(ll p,ll k){
	if(p==0){
		return 0;
	}
	if(key[p]>=k){
		return small(lc[p],k);
	}else{
		return sz[lc[p]]+val[p]+small(rc[p],k);
	}
}

ll get_rank(ll k){
	return small(root,k)+1;
}

ll at(ll p,ll x){
	if(x<=sz[lc[p]]){
		return at(lc[p],x);
	}else if(x>sz[lc[p]]+val[p]){
		return at(rc[p],x-sz[lc[p]]-val[p]);
	}
	return key[p];
}

ll at(ll x){
	return at(root,x);
}

ll prev(ll k){
	ll rank=get_rank(k);
	if(rank==1){
		return LLONG_MIN;
	}else{
		return at(rank-1);
	}
}

ll next(ll k){
	ll rank=get_rank(k+1);
	if(rank==sz[root]+1){
		return LLONG_MAX;
	}else{
		return at(rank);
	}
}

void remove(ll p,ll fa,ll s,ll k){
	if(k==key[p]){
		val[p]--;
	}else if(k<key[p]){
		remove(lc[p],p,1,k);
	}else{
		remove(rc[p],p,2,k);
	}
	up(p);
	if(!balance(p)){
		top=p;
		father=fa;
		side=s;
	}
}

void remove(ll k){
	if(get_rank(k)!=get_rank(k+1)){
		top=father=side=0;
		remove(root,0,0,k);
		rebuild();
	}
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
