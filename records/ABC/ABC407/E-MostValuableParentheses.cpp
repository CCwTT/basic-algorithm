//https://atcoder.jp/contests/abc407/tasks/abc407_e
//@@@
//thought
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
    vector<ll> a(n*2);
    for(ll i=0;i<n*2;i++){
        cin>>a[i];
    }
    ll ans=0;
    priority_queue<ll> pq;
    for(ll i=0;i<n;i++){
        if(i==0){
            pq.push(a[i*2-0]);
        }else{
            pq.push(a[i*2-1]);
            pq.push(a[i*2-0]);
        }
        ll v=pq.top();
        pq.pop();
        ans+=v;
    }
    cout<<ans<<endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
