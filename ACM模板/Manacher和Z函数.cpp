#include<bits/stdc++.h>
using namespace std;
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

//2025/6/23
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

vector<ll> get_z(string s){ //LCP of every suffix of s and s 
	ll n=s.size();
	vector<ll> z(n);
	z[0]=n;
	for(ll i=1,boxl=1,boxr=1;i<n;i++){  //box:[)
		z[i]=i<boxr?min(boxr-i,z[i-boxl]):0;
		while(i+z[i]<n&&s[i+z[i]]==s[z[i]]){
			z[i]++;
		}
		if(i+z[i]>boxr){
			boxr=i+z[i];
			boxl=i;
		}
	}
	return z;
}

vector<ll> get_e(string s,string t){ //LCP of every suffix of s and t
	ll m=s.size(),n=t.size();
	auto z=get_z(t);
	vector<ll> e(m);
	for(ll i=0,boxl=0,boxr=0;i<m;i++){
		e[i]=i<boxr?min(boxr-i,z[i-boxl]):0;
		while(i+e[i]<m&&e[i]<n&&s[i+e[i]]==t[e[i]]){
			e[i]++;
		}
		if(i+e[i]>boxr){
			boxr=i+e[i];
			boxl=i;
		}
	}
	return e;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
	string s="afsdlaabaakelq";
	auto ss=pre_process(s);
	auto p=get_p(ss); 
	cout<<*max_element(p.begin(),p.end())-1;
    return 0;
}
