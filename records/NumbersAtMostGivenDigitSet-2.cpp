//https://leetcode.cn/problems/numbers-at-most-n-given-digit-set/
//@@@
class Solution {
    public:
        int atMostNGivenDigitSet(vector<string>& digits, int n) {
            string s=to_string(n);
            function<int(int,bool,bool)> dfs=[&](int p,bool solid,bool free)->int{
                if(p==s.size()){
                    return solid;
                }
                int res=0;
                if(!solid){
                    res+=dfs(p+1,false,true);
                }
                if(!free){
                    for(auto d:digits){
                        auto c=d[0];
                        if(c>s[p]) break;
                        if(c<s[p]){
                            res+=dfs(p+1,true,true);
                        }else{
                            res+=dfs(p+1,true,false);
                        }
                    }
                }else{
                    res+=digits.size()*dfs(p+1,true,true);
                }
                return res;
            };
            return dfs(0,false,false);
        }
    };