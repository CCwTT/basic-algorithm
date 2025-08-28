//https://www.luogu.com.cn/problem/P3369
//@@@
//avl
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

const ll MAXN=100001;

ll key[MAXN];
ll val[MAXN];
ll lc[MAXN];
ll rc[MAXN];
ll height[MAXN];
ll sz[MAXN];

ll cnt=0;
ll root=0;

void up(ll p){
	sz[p]=sz[lc[p]]+sz[rc[p]]+val[p];
	height[p]=max(height[lc[p]],height[rc[p]])+1;
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

ll maintain(ll p){
	ll lh=height[lc[p]];
	ll rh=height[rc[p]];
	if(lh-rh>1){
		if(height[lc[lc[p]]]>=height[rc[lc[p]]]){
			p=right_rotate(p);
		}else{
			lc[p]=left_rotate(lc[p]);
			p=right_rotate(p);
		}
	}else if(rh-lh>1){
		if(height[rc[rc[p]]]>=height[lc[rc[p]]]){
			p=left_rotate(p);
		}else{
			rc[p]=right_rotate(rc[p]);
			p=left_rotate(p);
		}
	}
	return p;
}

ll insert(ll p,ll x){
	if(p==0){
		key[++cnt]=x;
		val[cnt]=sz[cnt]=height[cnt]=1;
		return cnt;
	}
	if(key[p]==x){
		val[p]++;
	}else if(key[p]>x){
		lc[p]=insert(lc[p],x);
	}else{
		rc[p]=insert(rc[p],x);
	}
	up(p);
	return maintain(p);
}

void insert(ll x){
	root=insert(root,x);
}

ll get_rank(ll p,ll x){
	if(p==0){
		return 1;
	}
	if(x==key[p]){
		return sz[lc[p]]+1;
	}else if(x<key[p]){
        return get_rank(lc[p],x);
    }else{
		return sz[lc[p]]+val[p]+get_rank(rc[p],x);
	}
}

ll get_rank(ll x){
	return get_rank(root,x);
}

ll remove_leftmost(ll p,ll leftmost){
	if(p==leftmost){
		return rc[p];
	}else{
		lc[p]=remove_leftmost(lc[p],leftmost);
		up(p);
		return maintain(p);
	}
}

ll remove(ll p,ll x){
	if(key[p]<x){
		rc[p]=remove(rc[p],x);
	}else if(key[p]>x){
		lc[p]=remove(lc[p],x);
	}else{
		if(val[p]>1){
			val[p]--;
		}else{
			if(lc[p]==0&&rc[p]==0){
				return 0;
			}else if(lc[p]!=0&&rc[p]==0){
				p=lc[p];
			}else if(lc[p]==0&&rc[p]!=0){
				p=rc[p];
			}else{
				ll leftmost=rc[p];
				while(lc[leftmost]!=0){
					leftmost=lc[leftmost];
				}
				rc[p]=remove_leftmost(rc[p],leftmost);
				lc[leftmost]=lc[p];
				rc[leftmost]=rc[p];
				p=leftmost;
			}
		}
	}
	up(p);
	return maintain(p);
}

void remove(ll x){
	if(get_rank(x)!=get_rank(x+1)){
		root=remove(root,x);
	}
}

ll at(ll p,ll x){
	if(sz[lc[p]]>=x){
		return at(lc[p],x);
	}else if(sz[lc[p]]+val[p]>=x){
        return key[p];
    }else{
		return at(rc[p],x-sz[lc[p]]-val[p]);
	}
}

ll at(ll x){
	return at(root,x);
}

ll prev(ll p,ll x){
	if(p==0){
		return LLONG_MIN;
	}
	if(key[p]>=x){
		return prev(lc[p],x);
	}else{
		return max(key[p],prev(rc[p],x));
	}
}

ll prev(ll x){
	return prev(root,x);
}

ll next(ll p,ll x){
	if(p==0){
		return LLONG_MAX;
	}
	if(key[p]<=x){
		return next(rc[p],x);
	}else{
		return min(key[p],next(lc[p],x));
	}
}

ll next(ll x){
	return next(root,x);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll n;
	cin>>n;
	for(ll i=1,op,x;i<=n;i++){
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
