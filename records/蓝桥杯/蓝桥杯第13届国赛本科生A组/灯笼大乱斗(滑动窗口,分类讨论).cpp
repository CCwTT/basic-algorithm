//https://www.lanqiao.cn/problems/20255/learning/?page=1
//@@@
//sliding window,classification discussion
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

void solve(){
    ll n;
    cin>>n;
    vector<ll> a(n),b(n);
    for(ll i=0;i<n;i++){
    	cin>>a[i];
	}
	for(ll i=0;i<n;i++){
		cin>>b[i];
	}
	ll i=0,j=0;
	ll ans=0;
	priority_queue<pair<ll,ll>> pq1,pq2;
	while(!(i==n&&j==n)){
		if(j<n&&(pq1.empty()||a[j]+b[j]>pq1.top().first)&&(pq2.empty()||a[j]-b[j]>pq2.top().first)){
			pq1.emplace(a[j]+b[j],j);
			pq2.emplace(a[j]-b[j],j);
			ans+=j-i;
			j++;
		}else{
			i++;
			while(!pq1.empty()&&pq1.top().second<i){
				pq1.pop();
			}
			while(!pq2.empty()&&pq2.top().second<i){
				pq2.pop();
			}
		}
	}
	cout<<ans<<endl;
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