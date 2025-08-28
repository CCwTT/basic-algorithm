//https://www.luogu.com.cn/problem/P4555
//@@@
///p array,monotonicity optimization
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

void solve(){
    string s;
    cin>>s;
    auto ss=pre_process(s);
    auto p=get_p(ss);
    vector<ll> l(p.size(),0);
    vector<ll> r(p.size(),0);
    for(int i=0,j=0;i<p.size();i++){
        while(i+p[i]>j){
            l[j]=j-i;
            j+=2;
        }
    }
    for(int i=p.size()-1,j=p.size()-1;i>=0;i--){
        while(i-p[i]<j){
            r[j]=i-j;
            j-=2;
        }
    }
    ll ans=0;
    for(ll i=2;i<p.size()-2;i+=2){
        ans=max(ans,l[i]+r[i]);
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