#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

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

ll m,n;
big_integer ans(0);
big_integer dp[81][81];
big_integer a[81];

big_integer dfs(ll l,ll r,big_integer po){
    if(l==r) return po*a[l];
    if(dp[l][r]!=-1) return dp[l][r];
    big_integer& res=dp[l][r];
    res=max(a[l]*po+dfs(l+1,r,po*2),a[r]*po+dfs(l,r-1,po*2));
    return res;
}


void solve(){
    cin>>m>>n;
    while(m--){
        for(ll i=1;i<=n;i++){
            ll x;
            cin>>x;
            a[i]=x;
        }
        for(ll i=1;i<=n;i++){
            for(ll j=1;j<=n;j++){
                dp[i][j]=-1;
            }
        }
        ans=ans+dfs(1,n,2);
    }
    print(ans);
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