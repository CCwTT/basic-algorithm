//https://www.luogu.com.cn/problem/P3369
//@@@
//balanced tree(skiplist)
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

class skip_list{
public:
	static const ll MAXL=20;
	struct Node{
		ll key;
		ll val;
		ll level;
		vector<Node*> next;
		vector<ll> cover; //(]
		Node(ll key,ll val,ll level):key(key),val(val),level(level),cover(level+1,0),next(level+1,nullptr) {}
	};

	Node* root=new Node(LLONG_MIN,1,MAXL);

	ll get_val(Node* p){
		if(!p) return 0;
		return p->val;
	}

	ll random_level(){
		ll res=1;
		while(ran(1,100)<=50&&res<MAXL){
			res++;
		}
		return res;
	}

	Node* find(Node* p,ll h,ll k){
		while(p->next[h]&&p->next[h]->key<k){
			p=p->next[h];
		}
		if(h==1){
			if(p->next[h]&&p->next[h]->key==k){
				return p->next[h];
			}else{
				return nullptr;
			}
		}
		return find(p,h-1,k);
	}

	void insert_add_count(Node* p,ll h,ll k){
		while(p->next[h]&&p->next[h]->key<k){
			p=p->next[h];
		}
		p->cover[h]++;
		if(h==1){
			p->next[h]->val++;
		}else{
			insert_add_count(p,h-1,k);
		}
	}

	ll insert_node(Node* p,ll h,Node* q){
		ll cur_cnt=0;
		while(p->next[h]&&p->next[h]->key<q->key){
			cur_cnt+=p->cover[h];
			p=p->next[h];
		}
		if(h==1){
			q->next[h]=p->next[h];
			p->next[h]=q;
			q->cover[h]=get_val(q->next[h]);
			p->cover[h]=get_val(p->next[h]);
			return cur_cnt;
		}else{
			ll down_cnt=insert_node(p,h-1,q);
			if(h>q->level){
				p->cover[h]++;
			}else{
				q->next[h]=p->next[h];
				p->next[h]=q;
				q->cover[h]=p->cover[h]+1-down_cnt-q->val;
				p->cover[h]=down_cnt+q->val;
			}
			return cur_cnt+down_cnt;
		}
	}

	void insert(ll k){
		if(find(root,MAXL,k)){
			insert_add_count(root,MAXL,k);
		}else{
			Node* q=new Node(k,1,random_level());
			insert_node(root,MAXL,q);
		}
	}

	void remove_count(Node* p,ll h,ll k){
		while(p->next[h]&&p->next[h]->key<k){
			p=p->next[h];
		}
		if(h==1){
			p->next[h]->val--;
		}else{
			remove_count(p,h-1,k);
		}
		p->cover[h]--;
	}

	void remove_node(Node* p,ll h,Node* q){
		while(p->next[h]&&p->next[h]->key<q->key){
			p=p->next[h];
		}
		if(h>q->level){
			p->cover[h]--;
		}else{
			p->next[h]=q->next[h];
			p->cover[h]+=q->cover[h]-1;
		}
		if(h>1){
			remove_node(p,h-1,q);
		}
	}

	void remove(ll k){
		Node* q=find(root,MAXL,k);
		if(q){
			if(q->val>1){
				remove_count(root,MAXL,k);
			}else{
				remove_node(root,MAXL,q);
			}
		}
	}

	ll count_smaller(Node* p,ll h,ll k){
		ll cur_cnt=0;
		while(p->next[h]&&p->next[h]->key<k){
			cur_cnt+=p->cover[h];
			p=p->next[h];
		}
		if(h==1){
			return cur_cnt;
		}else{
			return cur_cnt+count_smaller(p,h-1,k);
		}
	}

	ll get_rank(ll k){
		return count_smaller(root,MAXL,k)+1;
	}

	ll at(Node* p,ll h,ll x){
		ll cur_cnt=0;
		while(p->next[h]&&cur_cnt+p->cover[h]<x){
			cur_cnt+=p->cover[h];
			p=p->next[h];
		}
		if(h==1){
			if(p->next[h]){
				return p->next[h]->key;
			}else{
				return LLONG_MAX;
			}
		}else{
			return at(p,h-1,x-cur_cnt);
		}
	}

	ll at(ll x){
		return at(root,MAXL,x);
	}

	ll prev(Node* p,ll h,ll k){
		while(p->next[h]&&p->next[h]->key<k){
			p=p->next[h];
		}
		if(h==1){
			return p->key;
		}else{
			return prev(p,h-1,k);
		}
	}

	ll prev(ll k){
		return prev(root,MAXL,k);
	}

	ll next(Node* p,ll h,ll k){
		while(p->next[h]&&p->next[h]->key<=k){
			p=p->next[h];
		}
		if(h==1){
			if(!p->next[h]){
				return LLONG_MAX;
			}else{
				return p->next[h]->key;
			}
		}else{
			return next(p,h-1,k);
		}
	}

	ll next(ll x){
		return next(root,MAXL,x);
	}
};

void solve(){
	skip_list sl;
	ll n;
	cin>>n;
	for(ll i=1;i<=n;i++){
		ll op,x;
		cin>>op>>x;
		if(op==1){
			sl.insert(x);
		}else if(op==2){
			sl.remove(x);
		}else if(op==3){
			cout<<sl.get_rank(x)<<endl;
		}else if(op==4){
			cout<<sl.at(x)<<endl;
		}else if(op==5){
			cout<<sl.prev(x)<<endl;
		}else{
			cout<<sl.next(x)<<endl;
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
