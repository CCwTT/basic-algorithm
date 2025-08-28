//https://leetcode.cn/problems/count-special-integers/description/
//@@@
class Solution {
    public:
        int countSpecialNumbers(int n) {
            string s=to_string(n);
            vector<vector<vector<int>>> mem(s.size(),vector<vector<int>>(2,vector<int>(1<<10,-1)));
            function<int(int,bool,int)> dfs=[&](int p,bool free,int mask)->int{
                if(p==s.size()) return mask!=0;
                if(~mem[p][free][mask]) return mem[p][free][mask];
                int res=0;
                if(!mask){
                    res+=dfs(p+1,true,mask);
                }
                for(int i=mask?0:1;i<=(free?9:s[p]-'0');i++) if(!(mask>>i&1)){
                    res+=dfs(p+1,free||i<s[p]-'0',mask|1<<i);
                } 
                mem[p][free][mask]=res;
                return res;
            };
            return dfs(0,false,0);
        }
    };