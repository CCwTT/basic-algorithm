#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a,ll b){
	return b==0?a:gcd(b,a%b);
} 

//����d=gcd(a,b) (��) 
//https://atcoder.jp/contests/abc300/tasks/abc300_e
tuple<ll,ll,ll> exgcd(ll a,ll b){
	if(b==0) return {a,1,0};
	auto [d,x,y]=exgcd(b,a%b);
	return {d,y,x-a*y/b};
}

//https://atcoder.jp/contests/abc300/tasks/abc300_e
const ll mod=1e9+7;
ll inv(ll x){
	auto [d,inv_x,_]=exgcd(x,mod);
	inv_x=(inv_x%mod+mod)%mod;
	return d==1?inv_x:-1;
}

//��ax+by=c��һ�������� (��)
tuple<ll,ll,ll> func(ll a,ll b,ll c){
	auto [d,x,y]=exgcd(a,b);
	if(c%d==0){
		x*=c/d;
		y*=c/d;
		return {x,y,0};
	}else{
		return {-1,-1,-1};
	}	
} 

//����չŷ������㷨��˷���Ԫ(��ax+by=1) (?)
//ll inv(ll x,ll mod){
//	ll inv_x,tmp;
//	ll result=func(x,mod,1,inv_x,tmp);
//	if(!~result) return -1;
//	return 0;
//}

//(?)


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    
    return 0;
}




//traditional fashion
// ll exgcd(ll a,ll b,ll& x,ll& y){
// 	if(b==0){
// 		x=1,y=0;
// 		return a;
// 	}
// 	ll x1,y1;
// 	ll d=exgcd(b,a%b,x1,y1);
// 	x=y1,y=x1-a/b*y1;
// 	return d;
// }

// ll inv(ll x,ll m,ll& inv_x){
// 	ll tmp;
// 	ll d=exgcd(x,m,inv_x,tmp);
// 	inv_x=((inv_x%m)+m)%m;
// 	if(d!=1){
// 		return -1;
// 	}
// 	return 0;
// }

// ll func(ll a,ll b,ll c,ll& x,ll& y){
// 	ll d=exgcd(a,b,x,y);
// 	if(c%d==0){
// 		x*=c/d;
// 		y*=c/d;
// 		return 0;
// 	}else{
// 		return -1;
// 	}	
// } 