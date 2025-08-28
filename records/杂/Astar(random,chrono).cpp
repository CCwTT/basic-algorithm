//https://github.com/algorithmzuo/algorithm-journey/blob/main/src/class065/Code01_AStarAlgorithm.java
#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
typedef long long ll;

const ll dx[]={0,0,1,-1};
const ll dy[]={1,-1,0,0};

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());
ll ran(ll l,ll r){return l+RNG()%(r-l+1);}

ll dijkstra(vector<vector<ll>>& grid,ll sx,ll sy,ll tx,ll ty){
    if(grid[sx][sy]==0||grid[tx][ty]==0) return -1;
    ll m=grid.size();       
    ll n=grid[0].size();     
    vector<vector<ll>> dis(m,vector<ll>(n,LLONG_MAX)); 
    dis[sx][sy]=1;
    vector<vector<bool>> vis(m,vector<bool>(n,false));
    priority_queue<tuple<ll,ll,ll>, vector<tuple<ll,ll,ll>>, greater<tuple<ll,ll,ll>>> pq;
    pq.push({1,sx,sy}); 
    while(!pq.empty()){
        auto [dist,x,y] = pq.top(); 
        pq.pop();
        if(vis[x][y])continue;
        vis[x][y]=true;
        if(x==tx&&y==ty) return dist; 
        for(ll i=0;i<4;i++){
            ll nx=x+dx[i];
            ll ny=y+dy[i];
            if(nx>=0&&nx<m&&ny>=0&&ny<n&&grid[nx][ny]==1&&!vis[nx][ny]){
                ll ndist=dist+1;
                if(ndist<dis[nx][ny]){
                    dis[nx][ny]=ndist;
                    pq.push({ndist,nx,ny}); 
                }
            }
        }
    }
    return -1;
}

ll h(ll x,ll y,ll tx,ll ty){
    return llabs(tx-x)+llabs(ty-y);
}

ll Astar(vector<vector<ll>>& grid,ll sx,ll sy,ll tx,ll ty){ //
    if(grid[sx][sy]==0||grid[tx][ty]==0) return -1;
    ll m=grid.size();       
    ll n=grid[0].size();     
    
    vector<vector<ll>> dis(m,vector<ll>(n,LLONG_MAX)); 
    dis[sx][sy]=1;
    vector<vector<bool>> vis(m,vector<bool>(n,false));
    priority_queue<tuple<ll,ll,ll>, vector<tuple<ll,ll,ll>>, greater<tuple<ll,ll,ll>>> pq;
    pq.push({1+h(sx,sy,tx,ty),sx,sy});  //
    while(!pq.empty()){
        auto [disthyp,x,y] = pq.top(); 
        pq.pop();
        if(vis[x][y]) continue;
        vis[x][y]=true;
        if(x==tx&&y==ty) return dis[x][y]; 
        for(ll i=0;i<4;i++){
            ll nx=x+dx[i];
            ll ny=y+dy[i];
            if(nx>=0&&nx<m&&ny>=0&&ny<n&&grid[nx][ny]==1&&!vis[nx][ny]){
                ll ndist=dis[x][y]+1;
                if(ndist<dis[nx][ny]){
                    dis[nx][ny]=ndist;
                    ll ndisthyp=ndist+h(nx,ny,tx,ty); //
                    pq.push({ndisthyp,nx,ny}); //
                }
            }
        }
    }
    return -1;
}

vector<vector<ll>> random_grid(ll n){
    vector<vector<ll>> grid(n,vector<ll>(n)); 
    for(ll i=0;i<n;i++){
        for(ll j=0;j<n;j++){
            if(ran(0,99)<30) grid[i][j]=0;
            else grid[i][j]=1;
        }
    }
    return grid;
}

signed main(){
    ll max_n=100;
    ll T=100;
    
    cout<<"Functional test begins"<<endl;
    for(ll i=0;i<T;i++){
        ll n=ran(2,max_n);
        vector<vector<ll>> grid=random_grid(n);
        ll sx=ran(0,n-1); 
        ll sy=ran(0,n-1); 
        ll tx=ran(0,n-1);
        ll ty=ran(0,n-1);
        
        if(grid[sx][sy]==0)grid[sx][sy]=1;
        if(grid[tx][ty]==0)grid[tx][ty]=1;
        
        ll ans1=dijkstra(grid,sx,sy,tx,ty);
        ll ans2=Astar(grid,sx,sy,tx,ty);
        
        if(ans1!=ans2){
            cout<<"Error! Dijkstra: "<<ans1<<" A*: "<<ans2<<endl;
        }
    }
    cout<<"Functional test ends"<<endl;
    
    cout<<"Performance test begins"<<endl;
    ll n=400;
    vector<vector<ll>> grid=random_grid(n);
    ll sx=0;
    ll sy=0;
    ll tx=n-50; 
    ll ty=n-50; 
    
    grid[sx][sy]=1;
    grid[tx][ty]=1;
    
    auto start=high_resolution_clock::now();
    ll ans1=dijkstra(grid,sx,sy,tx,ty);
    auto end=high_resolution_clock::now();
    auto duration=duration_cast<milliseconds>(end-start);
    cout<<"Dijkstra result: "<<ans1<<" | Time cost: "<<duration.count()<<" ms"<<endl;
    
    start=high_resolution_clock::now();
    ll ans2=Astar(grid,sx,sy,tx,ty);
    end=high_resolution_clock::now();
    duration=duration_cast<milliseconds>(end-start);
    cout<<"A* result: "<<ans2<<" | Time cost: "<<duration.count()<<" ms"<<endl;
    
    return 0;
}