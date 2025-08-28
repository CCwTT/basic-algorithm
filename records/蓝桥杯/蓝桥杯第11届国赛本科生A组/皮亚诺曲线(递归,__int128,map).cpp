#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
void out(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) out(x/10);
    putchar(x%10+'0');
}

ll qpow(ll x,ll n){
    if(x==0) return 0;
    ll res=1;
    while(n){
        if(n&1) res*=x;
        x*=x;
        n>>=1;
    }
    return res;
}

ll dfs(ll n,ll x,ll y,map<pair<ll,ll>,ll>mp){
    if(n==1) return mp[{x,y}];
    __int128 res=0;
    ll nx=x/qpow(3,n-1),ny=y/qpow(3,n-1);
    
    res+=mp[{nx,ny}]*qpow(3,n-1)*qpow(3,n-1);
    map<pair<ll,ll>,ll> mp1;
    if((nx==0&&ny==1)||(nx==2&&ny==1)){
        for(ll i=0;i<=2;i++){
            for(ll j=0;j<=2;j++)
                mp1[{2-i,j}]=mp[{i,j}];
        }
    }else if((nx==1&&ny==2)||(nx==1&&ny==0)){
        for(ll i=0;i<=2;i++){
            for(ll j=0;j<=2;j++)
                mp1[{i,2-j}]=mp[{i,j}];
        }
    }else if(nx==1&&ny==1){
        for(ll i=0;i<=2;i++){
            for(ll j=0;j<=2;j++)
                mp1[{2-i,2-j}]=mp[{i,j}];
        }
    }else{
		mp1=mp;
	} 
    return res+=dfs(n-1,x%qpow(3,n-1),y%qpow(3,n-1),mp1);
}

map<pair<ll,ll>,ll> mp;
int init=[]{
    mp[{0,0}]=0;
    mp[{0,1}]=1;
    mp[{0,2}]=2;
    mp[{1,2}]=3;
    mp[{1,1}]=4;
    mp[{1,0}]=5;
    mp[{2,0}]=6;
    mp[{2,1}]=7;
    mp[{2,2}]=8;
    return 0;
}();


void solve(){
	ll k;
    ll x1,y1,x2,y2;
    cin>>k>>x1>>y1>>x2>>y2;
    k=min(k,38ll); //log3(10^18)=37.726
    __int128 a=dfs(k,x1,y1,mp);
    __int128 b=dfs(k,x2,y2,mp);
    if(a>b){
		out(a-b);
	}else{
		out(b-a);
	}
    puts("");
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
