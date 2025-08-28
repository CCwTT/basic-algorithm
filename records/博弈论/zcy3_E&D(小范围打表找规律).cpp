//https://www.luogu.com.cn/problem/P2148
//@@@
//game theory
//The approach for this problem is as follows:since the number of stones in each pile can reach up to 1e9,we first compute the SG values for small ranges and generate a table.
//By observing the table, we can identify the pattern:sg[a][b]=__builtin_ctzll(~((a-1)|(b-1)))
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void Log(vector<ll>& a){
	cout<<"Log: ";
	for(int i=0;i<a.size();i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

void Log(vector<vector<ll>>& a){
	ll m=a.size(),n=a[0].size();
	cout<<"    ";
	for(ll j=0;j<n;j++){
		cout<<setw(4)<<j;
	}
	cout<<endl;
	for(ll i=0;i<m;i++){
		cout<<"i:"<<i<<" ";
		for(ll j=0;j<n;j++){
			cout<<setw(4)<<(a[i][j]<=LLONG_MIN/2||a[i][j]>=LLONG_MAX/2?-1:a[i][j]);
		}
		cout<<endl;
	}
	cout<<endl;
}

ll MX=20;
vector<vector<ll>> sg(MX,vector<ll>(MX,-1));

ll dfs(ll a,ll b){
    if(a==1&&b==1) return 0;
    if(~sg[a][b]) return sg[a][b];
    ll& res=sg[a][b];
	unordered_set<ll> S;
	if(a>1){
		for(ll l=1,r=a-1;l<a;l++,r--){
			S.insert(dfs(l,r));
		}
	}
	if(b>1){
		for(ll l=1,r=b-1;l<b;l++,r--){
			S.insert(dfs(l,r));
		}
	}
	for(ll i=0;;i++){
        if(!S.count(i)){
            res=i;
            break;
        }
    }
	return res;
}

int init=[]{
    for(ll i=1;i<MX;i++){
        for(ll j=1;j<MX;j++){
            sg[i][j]=dfs(i,j);
        }
    }
    // Log(sg);
    return 0;
}();


void solve(){
	ll n;
	cin>>n;
	ll XOR=0;
	for(ll i=0;i<n/2;i++){
		ll x,y;
		cin>>x>>y;
		XOR^=__builtin_ctzll(~((x-1)|(y-1)));
	}
	cout<<(XOR?"YES":"NO")<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T;
	cin>>T;
	while(T--){
		solve();
	}
    return 0;
}
