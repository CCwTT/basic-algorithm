//https://leetcode.cn/problems/non-negative-integers-without-consecutive-ones/
//@@@
typedef long long ll;
class Solution {
public:
    ll findIntegers(ll n) {
        ll high=__lg(n);

        vector<vector<vector<ll>>> mem(high+1,vector<vector<ll>>(2,vector<ll>(3,-1)));
        function<ll(ll,bool,ll)> dfs=[&](ll p,bool free,ll prev)->ll{
            if(p==-1){
                return prev!=2;
            }
            if(~mem[p][free][prev]){
                return mem[p][free][prev];
            }
            ll res=0;
            if(prev==2){
                res+=dfs(p-1,true,2);
            }
            for(ll i=prev==2?1:0;i<=(free?1:(n>>p&1));i++) if(i==0||i!=prev){
                res+=dfs(p-1,free||i<(n>>p&1),i);
            }
            return mem[p][free][prev]=res;
        };
        return 1+dfs(high,false,2);
    }
};