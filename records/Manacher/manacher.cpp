//https://www.luogu.com.cn/problem/P3805
//@@@
//manacher model
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

string pre_process(string s){
	string res="#";
	ll n=s.size();
	for(ll i=0;i<n;i++){
		res.push_back(s[i]);
		res.push_back('#');
	}
	return res;
}

vector<ll> get_p(string s){ //p:palindrome the length of the wing of the processed string
	ll n=s.size();
	vector<ll> p(n);
	ll boxr=0,boxm=0;   
	for(ll i=0;i<n;i++){
		p[i]=i<boxr?min(boxr-i,p[2*boxm-i]):1;
		while(i-p[i]>=0&&i+p[i]<n&&s[i-p[i]]==s[i+p[i]]){
			p[i]++;
		}
		if(i+p[i]>boxr){
			boxr=i+p[i];
			boxm=i;
		}
	}
	return p;
}

void solve(){
    string s;
    cin>>s;
    s=pre_process(s);
    auto p=get_p(s);
    cout<<*max_element(p.begin(),p.end())-1<<endl;
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
