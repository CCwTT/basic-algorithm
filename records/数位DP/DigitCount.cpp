//https://leetcode.cn/problems/digit-count-in-range/
//@@@
typedef long long ll;
class Solution {
private:
    ll helper(ll x,ll d){
        string s=to_string(x);
        ll n=s.size();
        vector<vector<vector<vector<ll>>>> mem(n,vector<vector<vector<ll>>>(2,vector<vector<ll>>(2,vector<ll>(101,-1))));
        function<ll(ll,bool,bool,ll)> dfs=[&](ll p,bool free,bool begun,ll above)->ll{
            if(p==n) return begun?above:0;
            if(~mem[p][free][begun][above]) return mem[p][free][begun][above];
            ll res=0;
            ll cur=s[p]-'0';
            if(!begun){
                res+=dfs(p+1,true,false,above);
            }
            for(ll i=begun?0:1;i<=(free?9:cur);i++){
                res+=dfs(p+1,free||i<cur,true,above+(i==d));
            }
            mem[p][free][begun][above]=res;
            return res;
        };
        return dfs(0,false,false,0);
    }

public:
    ll digitsCount(ll d, ll low, ll high) {
        if(low==1) return helper(high,d);
        return helper(high,d)-helper(low-1,d);
    }
};