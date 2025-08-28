//https://www.luogu.com.cn/problem/P4008
//@@@
//balanced tree(FHQ Treap)
//FHQ-Treap实现区间移动
//getchar() 和 ios::sync_with_stdio(false);水火不相容
//getchar() 和 ios::sync_with_stdio(false);水火不相容
//getchar() 和 ios::sync_with_stdio(false);水火不相容
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

mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count());
ll ran(ll l,ll r){
	return uniform_int_distribution<ll>(l,r)(RNG);
}

const ll MAXN=2000001;
ll root=0;
ll cnt=0;
char key[MAXN];
ll lc[MAXN];
ll rc[MAXN];
ll sz[MAXN];
ll priority[MAXN];
string ans;

void up(ll p){
	sz[p]=sz[lc[p]]+sz[rc[p]]+1;
}

void split(ll p,ll t,ll& l,ll& r){
	if(!p){
		l=r=0;
	}else{
		if(sz[lc[p]]+1<=t){
			l=p;
			split(rc[p],t-sz[lc[p]]-1,rc[p],r);
		}else{
			r=p;
			split(lc[p],t,l,lc[p]);
		}
		up(p);
	}
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

void inorder(ll p){
	if(!p) return;
	inorder(lc[p]);
	ans.push_back(key[p]);
	inorder(rc[p]);
}

void solve(){
	ll pos=0,len,l,m,lm,r;//pos模拟的是一维数组上的光标位置，也等于其左边字符个数
	ll n;
	cin>>n;
	for(ll i=1;i<=n;i++){
		string op;
		cin>>op;
		if(op=="Prev"){
			pos--;
		}else if(op=="Next"){
			pos++;
		}else if(op=="Move"){
			cin>>pos;
		}else if(op=="Insert"){
			cin>>len;
			ll l=0;
			ll r=0;
			split(root,pos,l,r);
			for(ll j=1;j<=len;j++){
				char ch;
				ch=cin.get();
				while(ch<32||ch>126){
					ch=cin.get();
				}
				key[++cnt]=ch;
				sz[cnt]=1;
				priority[cnt]=ran(1,100000);
				l=merge(l,cnt);
			}
			root=merge(l,r);
		}else if(op=="Delete"){
			cin>>len;
			ll lm=0;
			ll r=0;
			split(root,pos+len,lm,r);
			ll l=0;
			ll m=0;
			split(lm,pos,l,m);
			root=merge(l,r);
		}else{
			cin>>len;
			ll lm=0;
			ll r=0;
			split(root,pos+len,lm,r);
			ll l=0;
			ll m=0;
			split(lm,pos,l,m);
			ans.clear();
			inorder(m);
			root=merge(merge(l,m),r);
			cout<<ans<<endl;
		}
	}
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
