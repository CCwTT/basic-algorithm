//https://www.luogu.com.cn/problem/P1659
//@@@
///p array,difference,quick power
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

void Log(vector<ll>& a){
	ll n=a.size();
	for(ll i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

string pre_process(string s){
	string res="#";
	ll n=s.size();
	for(ll i=0;i<n;i++){
		res.push_back(s[i]);
		res.push_back('#');
	}
	return res;
}
vector<ll> get_p(string s){
	ll n=s.size();
	vector<ll> p(n);
	for(ll i=0,c=0,r=0,len;i<n;i++){
		len=i<r?min(r-i,p[2*c-i]):1;
		while(i+len<n&&i-len>=0&&s[i+len]==s[i-len]){
			len++;
		}
		if(i+len>r){
			r=i+len;
			c=i;
		}
		p[i]=len;
	}
	return p;
}

const ll mod=19930726;

ll qpow(ll x,ll n){
    ll res=1;
    while(n){
        if(n&1){
            res=res*x%mod;
        }
        x=x*x%mod;
        n>>=1;
    }
    return res;
}

void solve(){
    ll n,m;
    string s;
    cin>>n>>m>>s;
    string ss=pre_process(s);
    vector<ll> p=get_p(ss);
    vector<ll> diff(1000000+5);
    for(auto len:p){
        if((len-1)&1){
            diff[1]++;
            diff[len]--;
        }
    }
    partial_sum(diff.begin(),diff.end(),diff.begin());
    ll tot=0;
    for(ll i=1;i<diff.size();i+=2){
        tot+=diff[i];
    }
    if(tot<m){
        cout<<-1<<endl;
        return;
    }
    ll ans=1;
    ll rest=m;
    for(ll i=99999;i>=1;i-=2){
        ans=ans*qpow(i,min(rest,diff[i]))%mod;
        rest-=min(rest,diff[i]);
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