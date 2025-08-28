
//Cartesian tree
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

const ll mod=1e9+7;

ll qpow(ll x,ll n){
	ll res=1;
	while(n){
		if(n&1) res=res*x%mod;
		n>>=1;
		x=x*x%mod;
	}
	return res;
}

ll inv(ll x){
	return qpow(x,mod-2);
}

const ll MX=1e6+5;
ll fac[MX],inv_fac[MX];

ll init=[]{
	fac[0]=1;
	for(ll i=1;i<MX;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	inv_fac[MX-1]=inv(fac[MX-1]);
	for(ll i=MX-2;i>=0;i--){
		inv_fac[i]=inv_fac[i+1]*(i+1)%mod;
	}
	return 0;
}();

ll C(ll n,ll m){
	if(n<0||n<m) return 0;
	return fac[n]*inv_fac[m]%mod*inv_fac[n-m]%mod;
}

class Cartesian_tree{
public:
	struct node{
		ll key;
		ll val;
		node* lc;
		node* rc;
		ll id;
		ll cols;
		node(){}
		node(ll key,ll val):key(key),val(val),lc(nullptr),rc(nullptr){}
	};
	node* root=nullptr;
	stack<node*> stk;
	ll cnt=0;

	void insert(ll k,ll v){
		node* p=new node(k,v);
		p->id=++cnt;
		if(!root){
			root=p;
			stk.push(p);
			return;
		}
		node* last=nullptr;
		while(!stk.empty()&&stk.top()->val>v){ //同级最左为上则没有等号
			last=stk.top();
			stk.pop();
		}
		if(!stk.empty()){
			stk.top()->rc=p;
		}
		if(last){
			p->lc=last;
			if(last==root){
				root=p;
			}
		}
		stk.push(p);
	}
};

ll get_id(Cartesian_tree::node* p){
	return p?p->id:0;
}

ll get_cols(Cartesian_tree::node* p){
	return p?p->cols:0;
}

ll get_val(Cartesian_tree::node* p){
	return p?p->val:0;
}

void solve(){
	Cartesian_tree ct;
	ll n,K;
	cin>>n>>K;
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>x;
		ct.insert(i,x);
	}
	vector<vector<ll>> f(n+1,vector<ll>(K+1,0));
	f[0][0]=1;
	function<void(Cartesian_tree::node*,Cartesian_tree::node*)> dfs=[&](Cartesian_tree::node* p,Cartesian_tree::node* fa)->void{
		if(!p) return;
		dfs(p->lc,p);
		dfs(p->rc,p);
		
		p->cols=get_cols(p->lc)+get_cols(p->rc)+1;
		vector<ll> tmp(K+1);
		for(ll l=0;l<=min(get_cols(p->lc),K);l++){
			for(ll r=0;r<=min(get_cols(p->rc),K-l);r++){
				tmp[l+r]=(tmp[l+r]+f[get_id(p->lc)][l]*f[get_id(p->rc)][r]%mod)%mod;
			}
		}
		
		for(ll j=0;j<=min(p->cols,K);j++){
			for(ll up=0;up<=j;up++){
				f[p->id][j]=(f[p->id][j]+C(p->cols-up,j-up)*C(p->val-get_val(fa),j-up)%mod*fac[j-up]%mod*tmp[up]%mod)%mod;
			}
		}
		return;
	};
	dfs(ct.root,nullptr);
	cout<<f[ct.root->id][K]<<endl;
}



signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}

