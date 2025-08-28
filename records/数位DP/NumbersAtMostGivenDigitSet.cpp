//https://leetcode.cn/problems/numbers-at-most-n-given-digit-set/
//@@@
class Solution {
    public:
        int atMostNGivenDigitSet(vector<string>& digits, int n) {
            string s=to_string(n);
            vector<vector<vector<int>>> mem(s.size(),vector<vector<int>>(2,vector<int>(2,-1)));
            function<int(int,bool,bool)> dfs=[&](int p,bool free,bool begun)->int{
                if(p==s.size()){
                    return begun;
                }
                if(~mem[p][free][begun]){
                    return mem[p][free][begun];
                }
                int res=0;
                if(!begun){
                    res+=dfs(p+1,true,false);
                }
                for(auto d:digits){
                    int i=d[0]-'0';
                    if(i>(free?9:s[p]-'0')) break;
                    res+=dfs(p+1,free||i<s[p]-'0',true);
                }
                
                mem[p][free][begun]=res;
                return res;
            };
            return dfs(0,false,false);
        }
    };