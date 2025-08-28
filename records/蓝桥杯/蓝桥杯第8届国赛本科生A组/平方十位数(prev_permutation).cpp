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

bool is_square(ll x){
    ll rt=(ll)sqrt(x);
    while(rt*rt<=x){
        if(rt*rt==x) return true;
        rt++;
    }
    return false;
}

void solve(){
    vector<ll> nums={9,8,7,6,5,4,3,2,1,0};
    do{
        ll x=0;
        for(ll i=0;i<nums.size();i++){
            x=x*10+nums[i];
        }
        if(is_square(x)){
            cout<<x<<endl;
            return;
        }
    }while(prev_permutation(nums.begin(),nums.end()));
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
