//https://leetcode.cn/problems/maximum-number-of-non-overlapping-palindrome-substrings/
//@@@
//p array
typedef long long ll;
class Solution {
public:
    string pre_process(string s){
    	string res="#";
    	ll n=s.size();
    	for(ll i=0;i<n;i++){
    		res.push_back(s[i]);
    		res.push_back('#');
    	}
    	return res;
    }

    vector<ll> get_p(string s){
    	ll n=s.size();
    	vector<ll> p(n);
    	for(ll i=0,c=0,r=0,len;i<n;i++){
    		len=i<r?min(r-i,p[2*c-i]):1;
    		while(i+len<n&&i-len>=0&&s[i+len]==s[i-len]){
    			len++;
    		}
    		if(i+len>r){
    			r=i+len;
    			c=i;
    		}
    		p[i]=len;
    	}
    	return p;
    }

    int maxPalindromes(string s, int k) {
        auto ss=pre_process(s);
        auto p=get_p(ss);
        ll ans=0;
        ll r=0;
        for(ll i=0;i<ss.size();){
            ll j=i;
            while(j<ss.size()&&(p[j]-1<k||j-k<r)){
                j++;
            }
            if(j==ss.size()) break;
            ans++;
            r=j+k+1;
            if(r&1) r--;
            i=j+k;
            if(i&1) i--;
        }
        return ans;
    }
};