#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


const ll mod=1e9+7;
string n;
ll c;
ll ans;
ll v[3005];
ll s[3005];

bool is_pow(string s){
    bool res=true;
    for(ll i=1;i<s.size();i++){
        if(s[i]=='1'){
            res=false;
            break;
        }
    }
    return res;
}

bool is_all_one(string s){
    bool res=true;
    for(ll i=0;i<s.size();i++){
        if(s[i]=='0'){
            res=false;
            break;
        }
    }
    return res;
}

vector<ll> s2v(string s){
	vector<ll> v;
	ll n=s.size();
	for(ll i=n-1;i>=0;i--){
		v.push_back(s[i]-'0');
	}
	return v;
}

string v2s(vector<ll>& v){
	string s;
	ll n=v.size();
	for(ll i=n-1;i>=0;i--){
		s+=v[i]+'0';
	}
	return s;
}

string sub(string A,string B){
	string sign;
	if(A.size()<B.size()||A.size()==B.size()&&A<B){
		swap(A,B);
		sign="-";
	}
	auto a=s2v(A),b=s2v(B);
	ll N=max(a.size(),b.size());
	if(a.size()<N) a.resize(N);
	if(b.size()<N) b.resize(N);
	vector<ll> c(N);
	for(ll i=0;i<N;i++){
		if(a[i]<b[i]){
			a[i+1]--,a[i]+=2;
		}
		c[i]=a[i]-b[i];
	}
	while(c.size()>1&&c.back()==0) c.pop_back();
	return sign+v2s(c);
}

ll get(ll col,string x){
    if(x.size()>col||x.size()==col&&!is_pow(x)){
        assert(0);
    }
    if(x.size()==col&&is_pow(x)){
        return v[col];
    }
    if(x=="0") return 0;
    string tmp="1";
    for(ll i=1;i<=col-2;i++){
        tmp+='0';
    }
    if(x.size()<tmp.size()||x==tmp){
        return get(col-1,x);
    }else{
        return (v[col-1]+get(col-1,sub(x,tmp))*c%mod)%mod;
    }
}

void solve(){
    cin>>n>>c;
    if(n=="0"){
        cout<<1<<endl;
        return;
    }
    if(c==0){
        cout<<1<<endl;
        return;
    }
    v[0]=s[0]=1;
    v[1]=c;
    s[1]=c+1;
    for(ll i=2;i<3005;i++){
        v[i]=v[i-1]*(c+1)%mod;
        s[i]=(s[i-1]+v[i])%mod;
    }
    if(is_all_one(n)){
        cout<<s[n.size()]<<endl;
        return;
    }
    ans=s[n.size()-1];
    string tmp;
    for(ll i=0;i<n.size()-1;i++){
        tmp+='1';
    }
    ans=(ans+get(n.size(),sub(n,tmp)))%mod;
    cout<<ans<<endl;
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