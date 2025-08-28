//https://atcoder.jp/contests/abc412/tasks/abc412_f
//This is not the AC solution for the problem,but the case in point is that the gauss here is correct.
//gauss
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
void Log(vector<vector<ll>>& a){
	ll m=a.size(),n=a[0].size();
	cout<<"    ";
	for(ll j=0;j<n;j++){
		cout<<setw(10)<<j;
	}
	cout<<endl;
	for(ll i=0;i<m;i++){
		cout<<"i:"<<i<<" ";
		for(ll j=0;j<n;j++){
			cout<<setw(10)<<(a[i][j]<=LLONG_MIN/2||a[i][j]>=LLONG_MAX/2?-1:a[i][j]);
		}
		cout<<endl;
	}
	cout<<endl;
}
const ll mod=998244353;

ll qpow(ll x,ll n){
	if(x==0) return 0;
	ll res=1;
	while(n){
		if(n&1) res=res*x%mod;
		x=x*x%mod;
		n>>=1;
	}
	return res;
}

ll inv(ll x){
	return qpow(x,mod-2);
}

void gauss(vector<vector<ll>>& mat){
	ll n=mat.size()-1;
	for(ll i=1;i<=n;i++){
		ll row_max=i;
		for(ll j=1;j<=n;j++){
			if(j<i&&mat[j][j]){
				continue;
			}
			if(llabs(mat[j][i])>llabs(mat[row_max][i])){
				row_max=j;
			}
		}
		swap(mat[row_max],mat[i]);
		if(llabs(mat[i][i])){
			ll tmp=mat[i][i];
			for(ll j=i;j<=n+1;j++){
				mat[i][j]=mat[i][j]*inv(tmp)%mod;
			}
			for(ll j=1;j<=n;j++) if(i!=j){
				tmp=mat[j][i]*inv(mat[i][i])%mod;
				for(ll k=i;k<=n+1;k++){
					mat[j][k]=(mat[j][k]-mat[i][k]*tmp%mod+mod)%mod;
				}
			}
		}
		//printmat(mat);
	}
}


void solve(){
	ll n;
	cin>>n;
	vector<ll> a(n+1);
	ll C;
	cin>>C;
	ll tot=1;
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		tot+=a[i];
	}
	a[C]++;
	vector<vector<ll>> mat(n+1,vector<ll>(n+2));
	for(ll i=1;i<=n;i++){
		mat[i][i]=mod-1;
		mat[i][n+1]=mod-(a[i]-1)*inv(tot-1)%mod;
		for(ll j=1;j<=n;j++) if(i!=j){
			mat[i][n+1]=(mat[i][n+1]-a[j]*inv(tot-1)%mod+mod)%mod;
			if(a[i]>a[j]){
				mat[i][i]=(mat[i][i]+a[j]*inv(tot-1)%mod)%mod;
			}else{
				mat[i][j]=(mat[i][j]+a[j]*inv(tot-1)%mod)%mod;
			}
		}
	}
	// vector<vector<ll>> mat0={
	// 	{0,0,0,0,0},
	// 	{0,(-1*inv(3)%mod+mod)%mod,0,0,mod-1},
	// 	{0,inv(2),mod-1,inv(3),mod-(inv(6)+inv(2)+inv(3))%mod},
	// 	{0,inv(2),inv(3),mod-1,mod-(inv(6)+inv(2)+inv(3))%mod}
	// };
	// Log(mat0);
	// Log(mat);
	gauss(mat);
	cout<<mat[C][n+1]<<endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
	// vector<vector<ll>> mat={
	// 	{0,0,0,0,0},
	// 	{0,(-1*inv(3)%mod+mod)%mod,0,0,mod-1},
	// 	{0,inv(2),mod-1,inv(3),mod-(inv(6)+inv(2)+inv(3))%mod},
	// 	{0,inv(2),inv(3),mod-1,mod-(inv(6)+inv(2)+inv(3))%mod}
	// };
	// gauss(mat);
	// for(ll i=1;i<=3;i++){
	// 	cout<<mat[i][3+1]<<endl;
	// }
    while(T--){
        solve();
    }
    return 0;
}
