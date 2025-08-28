//https://leetcode.cn/problems/count-of-integers/
//@@@
class Solution{
    const int mod=1e9+7;

    int helper(string &s,int min_sum,int max_sum){
        int n=s.length();
        vector<vector<vector<int>>> mem(n,vector<vector<int>>(2,vector<int>(9*n+1,-1)));
        function<int(int,bool,int)> dfs=[&](int p,bool free,int sum)->int{
            if(p==n){
                return (sum&&sum>=min_sum&&sum<=max_sum)?1:0;
            }
            if(~mem[p][free][sum]){
                return mem[p][free][sum];
            }
            int res=0;
            if(sum==0){
                res=(res+dfs(p+1,true,0))%mod;
            }
            for(int i=sum==0?1:0;i<=(free?9:s[p]-'0');i++){
                res=(res+dfs(p+1,free||i<s[p]-'0',sum+i))%mod;
            }
            
            mem[p][free][sum]=res;
            return res;
        };
        return dfs(0,false,0);
    }

public:
    int count(string num1,string num2,int min_sum,int max_sum){
        int ans=helper(num2,min_sum,max_sum)-helper(num1,min_sum,max_sum)+mod; 
        int sum=0;
        for(char c:num1){
            sum+=c-'0';
        }
        ans+=min_sum<=sum&&sum<=max_sum;
        return ans%mod;
    }
};