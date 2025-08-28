#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//groups function see functional tree 
class Dsu{
private:
	vector<int> f;
	vector<int> rank;
	
public:
	Dsu(int n):f(n),rank(n,0){
		iota(f.begin(),f.end(),0);
	}
	
	int find(int x){
		return f[x]==x?x:f[x]=find(f[x]);
	}
	
	void join(int x,int y){
		int fx=find(x),fy=find(y);
		if(fx==fy) return;
		if(rank[fx]<rank[fy]){
			f[fx]=fy;
		}else if(rank[fx]>rank[fy]){
			f[fy]=fx;
		}else{
			f[fy]=fx;
			rank[fx]++;
		}
	}
	
	bool check(int x,int y){
		return find(x)==find(y);
	}
};

//@@@
class Dsu{
public:
	vector<ll> f;
	Dsu(ll n):f(n){
		iota(f.begin(),f.end(),0);
	}
	ll find(ll x){
		return f[x]==x?x:f[x]=find(f[x]);
	}
	bool check(ll x,ll y){
		return find(x)==find(y);
	}
	void join(ll x,ll y){
		if(!check(x,y)) f[find(y)]=find(x);
	}
};

class WDsu{
public:
	vector<ll> f;
	vector<ll> dist;

	WDsu(ll n):f(n),dist(n){
		iota(f.begin(),f.end(),0);
	}

	ll find(ll x){
		ll _fx=f[x];
		return f[x]==x?x:(f[x]=find(f[x]),dist[x]+=dist[_fx],f[x]);
	}

	//y is the referenced system
	void join(ll x,ll y,ll v){
		ll fx=find(x);
		ll fy=find(y);
		if(fx==fy) return;
		dist[fy]=v+dist[x]-dist[y];
		f[fy]=fx;
	}

	bool check(ll x,ll y){
		return find(x)==find(y);
	}

	ll query(ll x,ll y){
		return check(x,y)?dist[y]-dist[x]:LLONG_MAX;
	}
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    
    return 0;
}
