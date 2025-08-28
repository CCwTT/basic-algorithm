#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//����d=gcd(a,b) (��) 
ll exgcd(ll a,ll b,ll& x,ll& y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	ll x1,y1;
	ll d=exgcd(b,a%b,x1,y1);
	x=y1,y=x1-a/b*y1;
	return d;
}
tuple<ll,ll,ll> exgcd(ll a,ll b){
	if(b==0) return {a,1,0};
	auto [d,x,y]=exgcd(b,a%b);
	return {d,y,x-a/b*y};
}

//�й�ʣ�ඨ����ͬ�෽���� 
ll crt(vector<ll>& r,vector<ll>& m){
	ll lcm=1,res=0;
	ll n=m.size();
	for(ll i=0;i<n;i++) lcm*=m[i]; //��֤lcm�����
	for(ll i=0;i<n;i++){
		ll c=lcm/m[i],inv_c,tmp;
		exgcd(c,m[i],inv_c,tmp); //��֤�н�!!!
		res=(res+r[i]*c%lcm*inv_c%lcm)%lcm;
	} 
	return (res%lcm+lcm)%lcm;
}

//��չ�й�ʣ�ඨ�� (?)
//r.size()>=2
ll excrt(vector<ll>& r,vector<ll>& m){
	ll n=r.size();
	ll r1,r2,m1,m2,x0,y0,x,y;
	r1=r[0],m1=m[0];
	for(ll i=1;i<n;i++){
		ll d=exgcd(m1,m2,x0,y0);
		if((r2-r1)%d!=0){
			return -1;
		}
		x=x*(r2-r1)/d;
		x=(x%(m2/d)+m2/d)%(m2/d);
		r1=m1*p+r1;
		m1=m1*m2/d;
	}
	return (r1%m1+m1)%m1;
} 

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    
    return 0;
}
