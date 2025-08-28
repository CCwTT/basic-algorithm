//https://leetcode.cn/problems/minimum-fuel-cost-to-report-to-the-capital/
//@@@
//tree dp
typedef long long ll;
constexpr ll N=1e5+5;
class Solution {
public:
    ll seats;
    vector<int> g[N];

    pair<ll,ll> dfs(ll u,ll fa){
        ll sz=1;
        ll sum=0;
        for(auto v:g[u]) if(v!=fa){
            auto [chsz,chsum]=dfs(v,u);
            sz+=chsz;
            sum+=chsum;
        }
        sum+=(sz+seats-1)/seats;
        return {sz,sum};
    }

    long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
        for(auto v:roads){
            ll f=v[0],c=v[1];
            g[f].push_back(c);
            g[c].push_back(f);
        }
        this->seats=seats;
        ll ans=0;
        for(auto v:g[0]){
            ans+=dfs(v,0).second;
        }
        return ans;
    }
};