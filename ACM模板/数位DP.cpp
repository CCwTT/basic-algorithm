//https://leetcode.cn/problems/count-special-integers/description/
//see records for more details
//framework
ll helper(ll x){
    string s=to_string(x);
    ll n=s.size();
    vector<vector<vector<int>>> mem(n,vector<vector<int>>(2,vector<int>(2,-1)));
    function<int(int,bool,bool)> dfs=[&](int p,bool free,bool begun)->int{ //prev,pprev,max_sum,min_sum,mask,above...
        if(p==n){
            return begun;  //return (begun&&...)?...:0;
        }
        if(~mem[p][free][begun]){
            return mem[p][free][begun];
        }
        int res=0;
        if(!begun){
            res+=dfs(p+1,true,false);
        }
        for(ll i=begun?0:1;i<=(free?9:s[p]-'0');i++){ //if(...){
            res+=dfs(p+1,free||i<s[p]-'0',true);
        }
        mem[p][free][begun]=res;
        return res;
    };
    return dfs(0,false,false);
}