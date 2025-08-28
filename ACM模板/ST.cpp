#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class ST{
	vector<vector<ll>> st;
public:
	ST(vector<ll>& a){
		ll n=a.size();
		ll high=__lg(n-1-0+1);
		st.assign(n,vector<ll>(high+1));
		for(ll i=0;i<n;i++){
			st[i][0]=a[i];
		}
		for(ll j=1;j<=high;j++){
			for(ll i=0;i<=n-(1<<j);i++){
				st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
			}
		}
	}
	
	ll query(ll x,ll y){
		ll high=__lg(y-x+1);
		return max(st[x][high],st[y-(1<<high)+1][high]);
	}
};

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
  	vector<ll> a={5,3,7,2,12,1,6,4,8,15};
  	ST st(a);
  	for(ll i=0;i<a.size();i++){
  		for(ll j=i;j<a.size();j++){
  			cout<<i<<" to "<<j<<" :"<<st.query(i,j)<<endl;
		}
	}
    return 0;
}

