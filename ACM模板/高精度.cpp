#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

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


//@@@
string add(string A,string B){
	auto a=s2v(A),b=s2v(B);
	ll N=max(a.size(),b.size());
	if(a.size()<N) a.resize(N);
	if(b.size()<N) b.resize(N);
	vector<ll> c(N+1,0);
	for(ll i=0;i<N;i++){
		c[i]+=a[i]+b[i];
		c[i+1]+=c[i]/10;
		c[i]%=10;
	}
	if(c.back()==0){
		c.resize(N);
	}
	return v2s(c);
}

//@@@
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
			a[i+1]--,a[i]+=10;
		}
		c[i]=a[i]-b[i];
	}
	while(c.size()>1&&c.back()==0) c.pop_back();
	return sign+v2s(c);
}

//(��) 
string mul(string A,string B){
	auto a=s2v(A),b=s2v(B);
	vector<ll> c(a.size()+b.size(),0);
	for(ll i=0;i<a.size();i++){
		for(ll j=0;j<b.size();j++){
			c[i+j]+=a[i]*b[j];
			c[i+j+1]+=c[i+j]/10;
			c[i+j]%=10;
		}
	}
	while(c.size()>1&&c.back()==0) c.pop_back();
	return v2s(c);
}

//(��) 
string qpow(string x,ll n){
	if(x=="0"&&n==0) return "1";
	if(x=="0") return "0";
	string res="1";
	while(n){
		if(n&1) res=mul(res,x);
		n>>=1;
		x=mul(x,x); 
	}
	return res;
}

//(��)
string div(string A,ll b){
	vector<ll> a;
	for(auto ch:A){
		a.push_back(ch-'0');
	}
	vector<ll> c; 
	ll r=0;
	for(ll i=0;i<a.size();i++){
		r=r*10+a[i];
		c.push_back(r/b);
		r%=b;
	}
	string ans;
	for(ll i=0;i<c.size();i++){
		if(c[i]==0&&ans.empty()) continue;
		ans.push_back(c[i]+'0');
	}
	return ans.size()?ans:"0";
}

//https://www.luogu.com.cn/problem/P1005
//this problem@@@
struct big_integer{
    string data;
    big_integer(string s):data(s){}
    big_integer(ll x=0):data(to_string(x)) {}
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

    //(��) 
    string add(string A,string B){
    	auto a=s2v(A),b=s2v(B);
    	ll N=max(a.size(),b.size());
    	if(a.size()<N) a.resize(N);
    	if(b.size()<N) b.resize(N);
    	vector<ll> c(N+1,0);
    	for(ll i=0;i<N;i++){
    		c[i]+=a[i]+b[i];
    		c[i+1]+=c[i]/10;
    		c[i]%=10;
    	}
    	if(c.back()==0){
    		c.resize(N);
    	}
    	return v2s(c);
    }

    //(��) 
    //A and B both represent positive numbers
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
    			a[i+1]--,a[i]+=10;
    		}
    		c[i]=a[i]-b[i];
    	}
    	while(c.size()>1&&c.back()==0) c.pop_back();
    	return sign+v2s(c);
    }

    //(��) 
    string mul(string A,string B){
    	auto a=s2v(A),b=s2v(B);
    	vector<ll> c(a.size()+b.size(),0);
    	for(ll i=0;i<a.size();i++){
    		for(ll j=0;j<b.size();j++){
    			c[i+j]+=a[i]*b[j];
    			c[i+j+1]+=c[i+j]/10;
    			c[i+j]%=10;
    		}
    	}
    	while(c.size()>1&&c.back()==0) c.pop_back();
    	return v2s(c);
    }

    //(��) 
    string qpow(string x,ll n){
    	if(x=="0"&&n==0) return "1";
    	if(x=="0") return "0";
    	string res="1";
    	while(n){
    		if(n&1) res=mul(res,x);
    		n>>=1;
    		x=mul(x,x); 
    	}
    	return res;
    }

    big_integer operator+(big_integer o){
        return big_integer(add(data,o.data));
    }

    big_integer operator-(big_integer o){
        return big_integer(sub(data,o.data));
    }

    big_integer operator*(big_integer o){
        return big_integer(mul(data,o.data));
    }

    big_integer operator+(ll o){
        return big_integer(add(data,to_string(o)));
    }

    big_integer operator-(ll o){
        return big_integer(sub(data,to_string(o)));
    }

    big_integer operator*(ll o){
        return big_integer(mul(data,to_string(o)));
    }

    big_integer qpow(big_integer x,ll n){
        return big_integer(qpow(x.data,n));
    }

    bool operator==(big_integer o){
        return data==o.data;
    }

    bool operator!=(big_integer o){
        return data!=o.data;
    }

    bool operator==(ll o){
        return data==to_string(o);
    }

    bool operator!=(ll o){
        return data!=to_string(o);
    }

    void operator=(ll o){
        data=to_string(o);
    }
};
void print(big_integer x){
    cout<<x.data<<endl;
}

big_integer max(big_integer A,big_integer B){
    if(A.data.size()!=B.data.size()){
        return A.data.size()>B.data.size()?A:B;
    }else{
        return A.data>B.data?A:B;
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
	string a,b;
	ll B;
	cin>>a>>B;
	cout<<qpow(a,B)<<endl; 
    return 0;
}
