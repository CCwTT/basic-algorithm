//https://acm.hdu.edu.cn/contest/problem?cid=1159&pid=1009
//@@@
//sieve,hash optimization,randomization,traversing right maintaining left
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

const ll mod=998244353;
const ll MX=1e6+10;
bool np[MX];
vector<ll> primes;
ll H[MX];
mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());
ll ran(){return RNG();}

int init=[]{
	for(ll i=2;i<MX;i++){
		if(!np[i]){
			H[i]=ran();
			for(ll j=i*2;j<MX;j+=i){
				np[j]=true;
				ll t=j;
				while(t%i==0){
					H[j]^=H[i];
					t/=i;
				}
			}
		}
	}
	return 0;
}();
//plz pay attention!The linear sieve in substitution of the sieve of Eratosthenes is not correct!
//Bear in mind the mechanism of the Euler sieve that each prime is only sieved by its LPF
//that is to say,a composite number cannot be visited by all its prime factors.
//To reach a conclusion,in the situation where all prime factors of a composite number are needed,the Euler sieve is not workable.
// if(!np[i]){
	// 	primes.push_back(i);
	// 	H[i]=ran();
	// }
	// for(auto& p:primes){
	// 	if(i*p>=MX) break;
	// 	np[i*p]=true;
	// 	ll t=i*p;
	// 	while(t%i==0){
	// 		H[i*p]^=H[i];
	// 		t/=i;
	// 	}
	// 	if(i%p==0) break;
// }

void solve(){
  ll n;
  cin>>n;
  vector<ll> a(n+1);
  for(ll i=1;i<=n;i++){
	cin>>a[i];
  }
  vector<ll> sum(2);
  unordered_map<ll,ll> mp={{0,0}};
  ll ansl=-1,ansr=-1;
  for(ll i=1;i<=n;i++){
    ll x=a[i];
    sum[i&1]=sum[(i-1)&1]^H[x];
    if(mp.count(sum[i&1])){
      ll l=mp[sum[i&1]];
      if(ansl==-1||i-(l+1)>ansr-ansl){
        ansr=i;
        ansl=l+1;
      }
    }else{
		mp[sum[i&1]]=i;
	}
  }
  cout<<ansl<<" "<<ansr<<endl;
}

signed main(){
  ios::sync_with_stdio(false);
  cin.tie(0);cout.tie(0);
  ll T;
  cin>>T;
  while(T--){
	solve();
  }
  return 0;
}