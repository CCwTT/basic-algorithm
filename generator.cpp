#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void send(){
	cout<<endl;
}

void send(ll x){
	cout<<x<<endl;
}

void send(ll x,ll y){
	cout<<x<<" "<<y<<endl;
}

void send(ll x,ll y,ll z){
	cout<<x<<" "<<y<<" "<<z<<endl;
}

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());
ll ran(ll l,ll r){
	return l+RNG()%(r-l+1);
}

ll ran_(ll l,ll r){
	ll x=l+RNG()%(r-l+1);
	cout<<x<<endl;
	return x;
}
ll ran__(ll l,ll r){
	ll x=l+RNG()%(r-l+1);
	cout<<x<<" ";
	return x;
}


ll ran_(ll l,ll r,char c){
	ll x=l+RNG()%(r-l+1);
	cout<<x<<c;
	return x;
}

ll ran(ll l,ll r,function<bool(ll)> fun){
	ll x;
	do{
		x=l+RNG()%(r-l+1);
	}while(!fun(x));
	return x;
}

ll ran_(ll l,ll r,function<bool(ll)> fun){
	ll x;
	do{
		x=l+RNG()%(r-l+1);
	}while(!fun(x));
	cout<<x<<endl;
	return x;
}

pair<ll,ll> ran2(ll l1,ll r1,ll l2,ll r2){
	ll x=l1+RNG()%(r1-l1+1);
	ll y=l2+RNG()%(r2-l2+1);
	return {x,y};
}

pair<ll,ll> ran2_(ll l1,ll r1,ll l2,ll r2){
	ll x=l1+RNG()%(r1-l1+1);
	ll y=l2+RNG()%(r2-l2+1);
	cout<<x<<" "<<y<<endl;
	return {x,y};
}

tuple<ll,ll,ll> ran3(ll l1,ll r1,ll l2,ll r2,ll l3,ll r3){
	ll x=l1+RNG()%(r1-l1+1);
	ll y=l2+RNG()%(r2-l2+1);
	ll z=l3+RNG()%(r3-l3+1);
	return {x,y,z};
}

tuple<ll,ll,ll> ran3_(ll l1,ll r1,ll l2,ll r2,ll l3,ll r3){
	ll x=l1+RNG()%(r1-l1+1);
	ll y=l2+RNG()%(r2-l2+1);
	ll z=l3+RNG()%(r3-l3+1);
	cout<<x<<" "<<y<<" "<<z<<endl;
	return {x,y,z};
}

vector<ll> ranvec(ll l,ll r,ll n){
	vector<ll> vec(n);
	for(ll i=0;i<n;i++){
		vec[i]=ran(l,r);
	}
	return vec;
}

vector<ll> ranvec_(ll l,ll r,ll n){
	vector<ll> vec(n);
	for(ll i=0;i<n;i++){
		vec[i]=ran(l,r);
		cout<<vec[i]<<" ";
	}
	cout<<endl;
	return vec;
}

vector<ll> ranvec_unique(ll l,ll r,ll n){
	vector<ll> vec(n);
	vector<ll> back(r-l+1);
	iota(back.begin(),back.end(),l);
	for(ll i=0;i<n;i++){
		ll idx=ran(0,back.size());
		vec[i]=back[idx];
		back.erase(back.begin()+idx);
	}
	return vec;
}

//r-l���ܳ���1e6,n���ܳ���1e3 
vector<ll> ranvec_unique_(ll l,ll r,ll n){
	vector<ll> vec(n);
	vector<ll> back(r-l+1);
	iota(back.begin(),back.end(),l);
	for(ll i=0;i<n;i++){
		ll idx=ran(0,back.size()-1);
		vec[i]=back[idx];
		back.erase(back.begin()+idx);
		cout<<vec[i]<<" ";
	}
	cout<<endl;
	return vec;
}

void work(){
	ll n=10;
	cout<<10<<" "<<2<<endl;
	for(ll i=0;i<n;i++){
		ran__(1,10);
	}
	send();
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    freopen("in.txt","wb",stdout);
    ll T=10;
	cout<<T<<endl;
    while(T--){
    	work();
	}
    return 0;
}
