//https://www.luogu.com.cn/problem/P3185
//@@@
//game theory
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MX=21;
ll sg[MX];

ll init=[]{
	for(ll i=1;i<MX;i++){
		unordered_set<ll> S;
        for(ll j=i-1;j>=0;j--){
            for(ll k=j;k>=0;k--){
				S.insert(sg[j]^sg[k]);
            }
        }
        for(ll j=0;;j++){
			if(!S.count(j)){
				sg[i]=j;
				break;
			}
		}
    }
	return 0;
}();

void solve(){
	ll n;
  	cin>>n;
	vector<ll> nums(n);
    for(ll i=n-1;i>=0;i--){
        cin>>nums[i];
    }
    ll XOR=0;
    for(ll i=n-1;i>=0;i--){
        if(nums[i]%2==1){
            XOR^=sg[i];
        }
    }
    if(XOR==0){
        cout<<"-1 -1 -1"<<endl<<"0"<<endl;
		return;
    }
    ll cnt=0,a=-1,b=-1,c=-1;
    for(ll i=n-1;i>=1;i--){
        if(nums[i]>0){
            for(ll j=i-1;j>=0;j--){
                for(ll k=j;k>=0;k--){
                    if((XOR^sg[i]^sg[j]^sg[k])==0){
                        cnt++;
                        if(a==-1){
                            a=i;
                            b=j;
                            c=k;
                        }
                    }
                }
            }
        }
    }
    cout<<n-1-a<<" "<<n-1-b<<" "<<n-1-c<<endl<<cnt<<endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
	cin>>T;
    while(T--){
        solve();
    }
    return 0;
}