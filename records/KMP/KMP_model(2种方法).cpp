//https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/
//@@@
//kmp model
class Solution {
    typedef long long ll;
public:
    vector<ll> get_next(string s){ 
		ll n=s.size();
		vector<ll> next(n+1);
		next[0]=-1;
		next[1]=0;
		ll i=2,j=0;
		while(i<=n){
			if(s[i-1]==s[j]){
				next[i++]=++j;
			}else if(j){
				j=next[j];
			}else{
				next[i++]=0;
			}
		}
		return next;
	}

	ll kmp(string s,string t){ //vector<ll> s,vector<ll> t
		ll m=s.size(),n=t.size();
		auto next=get_next(t);
		ll i=0,j=0;
		while(i<m&&j<n){
			if(s[i]==t[j]){
				i++,j++;
			}else if(j){
				j=next[j];
			}else{
				i++;
			}
		}
		return j==n?i-j:-1;
	}
    
    ll strStr(string s,string t){
        return kmp(s,t);
    }
};

//1-indexed
class Solution {
    typedef long long ll;
public:
    vector<ll> get_next(string s){
		ll n=s.size()-1;
		vector<ll> next(n+2);
		next[0]=0;
		next[1]=0;
	    next[2]=1;
		ll i=3,j=1;
		while(i<=n+1){
			if(s[i-1]==s[j]){
				next[i++]=++j;
			}else if(j>1){
				j=next[j];
			}else{
				next[i++]=1;
			}
		}
		return next;
	} 
	
	ll kmp(string s,string t){
		ll m=s.size()-1,n=t.size()-1;
		auto next=get_next(t);
		ll i=1,j=1;
		while(i<=m&&j<=n){
			if(s[i]==t[j]){
				i++,j++;
			}else if(j>1){
				j=next[j];
			}else{
				i++;
			}
		}
		return j==n+1?i-j+1:0;
	}
    
    ll strStr(string s,string t){
        s=" "+s,t=" "+t;
        return kmp(s,t)-1;
    }
};

//@@@
//z&e array
typedef long long ll;
class Solution {
public:
    vector<ll> get_z(string s){
        ll n=s.size();
        vector<ll> z(n);
        z[0]=n;
        for(ll i=1,boxl=1,boxr=1;i<n;i++){
            z[i]=i<boxr?min(boxr-i,z[i-boxl]):0;
            while(i+z[i]<n&&s[i+z[i]]==s[z[i]]){
                z[i]++;
            }
            if(i+z[i]>boxr){
                boxr=i+z[i];
                boxl=i;
            }
        }
        return z;
    }

    vector<ll> get_e(string s,string t){
        ll m=s.size(),n=t.size();
        auto z=get_z(t);
        vector<ll> e(m);
        for(ll i=0,boxl=0,boxr=0;i<m;i++){
            e[i]=i<boxr?min(boxr-i,z[i-boxl]):0;
            while(i+e[i]<m&&e[i]<n&&s[i+e[i]]==t[e[i]]){
                e[i]++;
            }
            if(i+e[i]>boxr){
                boxr=i+e[i];
                boxl=i;
            }
        }
        return e;
    }

    int strStr(string haystack, string needle) {
        auto e=get_e(haystack,needle);
        for(ll  i=0;i<haystack.size();i++){
            ll len=e[i];
            if(len==needle.length()){
                return i;
            }
        }
        return -1;
    }
};