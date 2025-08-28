//https://leetcode.cn/problems/longest-path-with-different-adjacent-characters/
//@@@
//tree dp
class Solution {
public:
    int ans=0;
    string s;
    vector<vector<int>> g;

    int dfs(int u,int fa){
        int res=1;
        int mx=0,sem=0;
        for(auto v:g[u]) if(v!=fa){
            int chres=dfs(v,u);
            if(s[v]!=s[u]){
                res=max(res,1+chres);
                if(chres>mx){
                    sem=mx;
                    mx=chres;
                }else if(chres>sem){
                    sem=chres;
                }
            }
        }
        ans=max(ans,mx+sem+1);
        return res;
    }

    int longestPath(vector<int>& parent, string s) {
        this->s=s;
        g.resize(parent.size());
        for(int i=1;i<parent.size();i++){
            int j=parent[i];
            g[i].push_back(j);
            g[j].push_back(i);
        }
        dfs(0,-1);
        return ans;
    }
};