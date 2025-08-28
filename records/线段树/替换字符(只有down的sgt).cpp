//https://www.lanqiao.cn/problems/2180/learning/
//@@@
//seg
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

void Log(vector<ll>& a){
	ll n=a.size();
	for(ll i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

class segment_tree{
public:
	ll n;
	string& s;
	vector<vector<ll>> t;
	vector<bool> tag;
	segment_tree(ll sz,string& s):n(sz-1),s(s),tag(n<<2){
		t.assign(n<<2,vector<ll>(26,0));
		for(ll i=1;i<t.size();i++){
			iota(t[i].begin(),t[i].end(),0);
		}
	} 
	
	void apply(ll p,ll l,ll r){
		for(ll i=0;i<26;i++){
			t[p][i]=t[p>>1][t[p][i]];
		}
		tag[p]=true;
	}
	
	void down(ll p,ll l,ll r){
		ll m=l+r>>1;
		if(tag[p]){
			apply(p<<1,l,m);
			apply(p<<1|1,m+1,r);
			tag[p]=false;
		}
	}
	
	void update(ll p,ll l,ll r,ll x,ll y,char u,char v){
		if(x<=l&&r<=y){
			for(ll i=0;i<26;i++){
				if(t[p][i]==u-'a'){
					t[p][i]=v-'a';
				}
			}
			tag[p]=true;
			return;
		}
		down(p,l,r);
		ll m=l+r>>1;
		if(x<=m) update(p<<1,l,m,x,y,u,v);
		if(y>m) update(p<<1|1,m+1,r,x,y,u,v); 
	}
	
	void print(ll p,ll l,ll r){
		if(l==r){
			putchar(t[p][s[l-1]-'a']+'a');
			return;
		}
		down(p,l,r);
		ll m=l+r>>1;
		print(p<<1,l,m);
		print(p<<1|1,m+1,r);
	}
};

void solve(){
	string s;
	cin>>s;
	segment_tree seg(s.size()+1,s);
	ll m;
	cin>>m;
	while(m--){
		ll x,y;
		char u,v;
		cin>>x>>y>>u>>v;
		seg.update(1,1,seg.n,x,y,u,v);
	}
	seg.print(1,1,seg.n);
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