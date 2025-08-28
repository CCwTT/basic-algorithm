//https://leetcode.cn/problems/longest-palindromic-substring/
//@@@
//p array  
//KNOWLEDGE: p[i]-1:the corresponding palindrome length
//           i/2   :the end of the corresponding palindrome(open)
//           the middle index of the corresponding processed string of [l,r) is l+r
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

    string longestPalindrome(string s) {
        auto ss=pre_process(s);
        auto p=get_p(ss);
        auto it=max_element(p.begin(),p.end());
        return s.substr((it-p.begin()+*it)/2-(*it-1),*it-1);
    }
};

//https://leetcode.cn/problems/palindromic-substrings/
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

    int countSubstrings(string s) {
        auto ss=pre_process(s);
        auto p=get_p(ss);
        int ans=0;
        for(int i=0;i<p.size();i++){
            ans+=p[i]/2;
        }
        return ans;
    }
};