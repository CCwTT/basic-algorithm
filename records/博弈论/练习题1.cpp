//https://www.luogu.com.cn/problem/P7589
//@@@
//game theory
/*
Approach:
First, the problem can be transformed into: Given n piles of stones,where the initial number of stones in each pile is 
llabs(w−b)−1.Each operation allows taking any number of stones from a pile or adding at most d stones to a pile, with at most 
k addition operations allowed.
The key insight is that addition operations can be ignored, reducing the problem to a Nim game.The proof is as follows:
a.If a player is in a losing state in the game without considering backward operations(i.e., additions) and chooses to add 
x stones,the opponent can immediately remove x stones,nullifying the addition.The original losing player remains in a losing state.
b.If a player is in a winning state without considering additions,they can avoid using additions.If addition operations remain unused at the game's end, the scenario reduces to case (a),and the winning player stays victorious.
*/
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
    ll n,k,d;
    cin>>n>>k>>d;
    ll XOR=0;
    for(ll i=0;i<n;i++){
        ll y,b,w;
        cin>>y>>b>>w;
        ll x=llabs(b-w)-1;
        XOR^=x;
    }
    cout<<(XOR?"Yes":"No")<<endl;
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
