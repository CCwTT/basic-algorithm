//https://www.luogu.com.cn/problem/P3369
//@@@
//balanced tree(treap)
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
ll cnt=0;
ll root=0;
ll key[MAXN];
ll val[MAXN];
ll lc[MAXN];
ll rc[MAXN];
ll sz[MAXN];
ll priority[MAXN];

void up(ll p){
	sz[p]=sz[lc[p]]+sz[rc[p]]+val[p];
}

ll left_rotate(ll p){
	ll tmp=rc[p];
	rc[p]=lc[tmp];
	lc[tmp]=p;
	up(p);
	up(tmp);
	return tmp;
}

ll right_rotate(ll p){
	ll tmp=lc[p];
	lc[p]=rc[tmp];
	rc[tmp]=p;
	up(p);
	up(tmp);
	return tmp;
}

ll insert(ll p,ll k){
	if(!p){
		key[++cnt]=k;
		val[cnt]=sz[cnt]=1;
		priority[cnt]=ran(1,100000);
		return cnt;
	}
	if(k==key[p]){
		val[p]++;
	}else if(k<key[p]){
		lc[p]=insert(lc[p],k);
	}else{
		rc[p]=insert(rc[p],k);
	}
	up(p);
	if(lc[p]&&priority[lc[p]]>priority[p]){
		return right_rotate(p);
	}
	if(rc[p]&&priority[rc[p]]>priority[p]){
		return left_rotate(p);
	}
	return p;
}

void insert(ll k){
	root=insert(root,k);
}

ll small(ll p,ll k){
	if(!p){
		return 0;
	}
	if(k<=key[p]){
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
	}else if(x<=sz[lc[p]]+val[p]){
		return key[p];
	}else{
		return at(rc[p],x-sz[lc[p]]-val[p]);
	}
}

ll at(ll x){
	return at(root,x);
}

ll prev(ll p,ll k){
	if(!p){
		return LLONG_MIN;
	}
	if(k<=key[p]){
		return prev(lc[p],k);
	}else{
		return max(key[p],prev(rc[p],k));
	}
}

ll prev(ll k){
	return prev(root,k);
}

ll next(ll p,ll k){
	if(!p){
		return LLONG_MAX;
	}
	if(k>=key[p]){
		return next(rc[p],k);
	}else{
		return min(key[p],next(lc[p],k));
	}
}

ll next(ll k){
	return next(root,k);
}

ll remove(ll p,ll k){
	if(k<key[p]){
		lc[p]=remove(lc[p],k);
	}else if(k>key[p]){
		rc[p]=remove(rc[p],k);
	}else{
		if(val[p]>1){
			val[p]--;
		}else{
			if(!lc[p]&&!rc[p]){
				return 0;
			}else if(lc[p]&&!rc[p]){
				p=lc[p];
			}else if(!lc[p]&&rc[p]){
				p=rc[p];
			}else{
				if(priority[lc[p]]>=priority[rc[p]]){
					p=right_rotate(p);
					rc[p]=remove(rc[p],k);
				}else{
					p=left_rotate(p);
					lc[p]=remove(lc[p],k);
				}
			}
		}
	}
	up(p);
	return p;
}

void remove(ll k){
	if(get_rank(k)!=get_rank(k+1)){
		root=remove(root,k);
	}
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
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
    return 0;
}
