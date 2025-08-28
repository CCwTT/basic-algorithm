#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//check if square number
//https://www.lanqiao.cn/problems/2090/learning/?isWithAnswer=true
//@@@
inline bool squareNumber(ll x){
	ll y=sqrt(x);
	while(y*y<=x){
		if(y*y==x) return true;
		y++;
	}
	return false;
}

//check if cubic number
//https://www.lanqiao.cn/problems/2090/learning/?isWithAnswer=true
//@@@
inline bool cubicNumber(ll x){
	ll y=pow(x,1.0/3);
	while(y*y*y<=x){
		if(y*y*y==x) return true;
		y++;
	}
	return false;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	for(ll i=0;i<10;i++){
		cout<<(1-i&1*2)<<endl;
	}
	return 0;
} 
