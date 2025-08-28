//https://www.lanqiao.cn/problems/20116/learning/
//@@@
//__int128
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef __int128 ll;

ostream &operator<<(ostream &os, __int128 x){
    string s;
    ll sign=1;
    if(x<0){
      sign=-1;
      x=-x;
    }
    if(x==0) s="0";
    while(x){
        s+=x%10+'0';
        x/=10;
    }
    if(sign==-1) s+='-';
    reverse(s.begin(), s.end());
    return os<<s;
}

istream &operator>>(istream &is, __int128 &x){
    string s;
    cin>>s;
    x=0;
    ll sign=1;
    ll i=0;
    if(s[0]=='-'){
      sign=-1;
      i=1;
    }
    for(;i<s.size();i++){
      x=x*10+(s[i]-'0');
    }
    x*=sign;
    return is;
}

void Log(vector<ll>& a){
	ll n=a.size();
	for(ll i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

  ll x=20240601000;
  ll ans=0;
  for(ll a=1;a*a<=x;a++){
    if(x%a) continue;
    ll b=x/a;
    if((a&1)^(b&1)) continue;
    ll p=(a+b)>>1;
    ll q=(b-a)>>1;
    if(p*p>10120300500){
      ll n=p*p-10120300500;
      ans+=n;
    }
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
