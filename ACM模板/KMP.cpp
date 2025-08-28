#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/submissions/621958042/
//@@@
vector<ll> get_next(string s){ 
	ll n=s.size();
	vector<ll> next(n+1);
	next[0]=-1;
	next[1]=0;
	ll i=2,j=0;
	while(i<=n){
		if(s[i-1]==s[j]){
			next[i++]=++j;
		}else if(j){
			j=next[j];
		}else{
			next[i++]=0;
		}
	}
	return next;
}

ll kmp(string s,string t){ //vector<ll> s,vector<ll> t
	ll m=s.size(),n=t.size();
	auto next=get_next(t);
	ll i=0,j=0;
	while(i<m&&j<n){
		if(s[i]==t[j]){
			i++,j++;
		}else if(j){
			j=next[j];
		}else{
			i++;
		}
	}
	return j==n?i-j:-1;
}

//https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/submissions/621958042/
//@@@
//1-indexed
vector<ll> get_next(string s){
	ll n=s.size()-1;
	vector<ll> next(n+2);
	next[0]=0;
	next[1]=0;
    next[2]=1;
	ll i=3,j=1;
	while(i<=n+1){
		if(s[i-1]==s[j]){
			next[i++]=++j;
		}else if(j>1){
			j=next[j];
		}else{
			next[i++]=1;
		}
	}
	return next;
} 

ll kmp(string s,string t){
	ll m=s.size()-1,n=t.size()-1;
	auto next=get_next(t);
	ll i=1,j=1;
	while(i<=m&&j<=n){
		if(s[i]==t[j]){
			i++,j++;
		}else if(j>1){
			j=next[j];
		}else{
			i++;
		}
	}
	return j==n+1?i-j+1:0;
}


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    string s="abcdefgh",t="def";
	cout<<kmp(s,t); 
    return 0;
}
