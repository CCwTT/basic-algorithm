//https://leetcode.cn/problems/shortest-path-visiting-all-nodes/description/
class Solution{
public:
    int shortestPathLength(vector<vector<int>>& graph){
        int n=graph.size();
        queue<tuple<int,int,int>> q;
        vector<vector<int>> vis(n,vector<int>(1<<n));
        for(int i=0;i<n;i++){
            q.emplace(i,1<<i,0);
            vis[i][1<<i]=true;
        }
        int ans=0;
        while(!q.empty()){
            auto [u,mask,dis]=q.front();
            q.pop();
            if(mask==(1<<n)-1){
                ans=dis;
                break;
            }
            for(int v:graph[u]){
                if(!vis[v][mask|(1<<v)]){
                    vis[v][mask|(1<<v)]=true;
                    q.emplace(v,mask|(1<<v),dis+1);
                }
            }
        }
        return ans;
    }
};
    
class Solution{
public:
    int shortestPathLength(vector<vector<int>>& graph){
        int n=graph.size();
        vector<vector<int>> dis(n,vector<int>(n,n+1));
        for(int i=0;i<n;i++){
            for(int j:graph[i]){
                dis[i][j]=1;
            }
        }
        for(int k=0;k<n;k++){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
                }
            }
        }
        vector<vector<int>> f(n,vector<int>(1<<n,INT_MAX/2));
        for(int mask=1;mask<(1<<n);mask++){
            if((mask&(mask-1))==0){
                int u=__builtin_ctz(mask);
                f[u][mask]=0;
            }
            else{
                for(int u=0;u<n;u++){
                    if(mask>>u&1){
                        for(int v=0;v<n;v++){
                            if((mask>>v&1)&&u!=v){
                                f[u][mask]=min(f[u][mask],f[v][mask^(1<<u)]+dis[u][v]);
                            }
                        }
                    }
                }
            }
        }
        int ans=INT_MAX;
        for(int u=0;u<n;u++){
            ans=min(ans,f[u][(1<<n)-1]);
        }
        return ans;
    }
};