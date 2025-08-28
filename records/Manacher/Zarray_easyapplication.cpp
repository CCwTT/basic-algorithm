//https://leetcode.cn/problems/minimum-time-to-revert-word-to-initial-state-ii/
//@@@
//Z array
class Solution {
public:
    vector<int> get_z(string s){
    	int n=s.size();
    	vector<int> z(n);
    	z[0]=n;
    	for(int i=1,c=1,r=1,len;i<n;i++){
    		len=i<r?min(r-i,z[i-c]):0;
    		while(i+len<n&&s[i+len]==s[len]){
    			len++;
    		}
    		if(i+len>r){
    			r=i+len;
    			c=i;
    		}
    		z[i]=len;
    	}
    	return z;
    }

    int minimumTimeToInitialState(string word, int k) {
        auto z=get_z(word);
        int n=word.size();
        for(int i=k;i<n;i+=k){
            if(z[i]==n-i){
                return i/k;
            }
        }
        return (n+k-1)/k;
    }
};