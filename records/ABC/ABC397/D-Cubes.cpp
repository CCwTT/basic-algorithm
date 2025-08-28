//https://atcoder.jp/contests/abc397/editorial/12464
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
	ll n;
	cin>>n;
	for(ll d=1;d*d*d<=n;d++){
		//(d+y)^3-y^3=d^3+3*d^2*y+3*d*y^2=n
		if(n%d!=0) continue;
		//d^2+3*d*y+3*y^2=n/d=m
		ll m=n/d;
		//3*y^2+3*d*y+d^2-m=0 monotonically increasing
		//quadratic equation formula is another option
		//whereas binary search circumvents overflow
		ll left=1,right=1e9+1;
		while(left<=right){
			ll mid=left+right>>1;
			if(3*mid*mid+3*d*mid+d*d-m<0){
				left=mid+1;
			}else{
				right=mid-1;
			}
		}
		if(3*left*left+3*d*left+d*d-m==0){
			cout<<left+d<<" "<<left<<endl;
			exit(0);
		}
	}
	cout<<-1<<endl;
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
