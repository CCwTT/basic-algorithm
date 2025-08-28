#include<bits/stdc++.h>
#define int long long
#define endl '\n'
 
using namespace std;
using pii=pair<int,int>;
 
constexpr int N=310;
int _=1;
char g0[N][N];
char g[N][N];
int _row[N],_col[N];
int row[N],col[N],col2[N]; //row记录行中'.'的个数，col记录列中'.'的个数
int indices[N];
 
 
void solve(){
    int n,m,c,d;
    int A=0;    //A记录初始'.'的个数，用于初始化ans为一种颜色不涂
    cin>>n>>m>>c>>d;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>g[i][j];
    if(n>m){
        memcpy(g0,g,sizeof(g));    //转置前先来个副本
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                g[j][i]=g0[i][j];  //注意i,j的顺序
        swap(n,m);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(g[i][j]=='.'){
                _row[i]++;
                _col[j]++;
                A++;
            }
    
    int ans=A*d;
    for(int k=1;k<=m;k++){
        //注意初始化
        int cnt0=0;
        memcpy(row,_row,sizeof(_row));
        memcpy(col,_col,sizeof(_col));
        memset(col2,0,sizeof(col2));
        //计算col2为该列空位所在行的空位数小于k的行的总数,col2越大该列越容易在后续被置0
        for(int i=1;i<=n;i++){
            if(row[i]>k){
                for(int j=1;j<=m;j++){
                    if(g[i][j]=='.'){
                        col2[j]++;
                    }
                }
            }
        }
        //遍历行
        for(int i=1;i<=n;i++){
            //跳过空位不足k的行
            if(row[i]<=k) continue;
            //构建自定义遍历顺序:优先在空位多的列上置0，若有多列空位同时最多，优先在最不容易在后续被置0的列上置0
            for(int p=1;p<=m;p++){
                indices[p]=p;
            }
            sort(indices+1,indices+m+1,[&](int a,int b){
                return col[a]!=col[b]?col[a]>col[b]:col2[a]<col2[b];
            });
            //按自定义遍历顺序遍历列
            for(int j0=1;j0<=m;j0++){
                int j=indices[j0];
                if(g[i][j]=='.'){
                    cnt0++;
                    col[j]--;
                    row[i]--;
                    if(row[i]<=k){
                        for(int jj=1;jj<=m;jj++){
                            if(g[i][jj]!='*'){
                                col2[jj]--;
                            }
                        }
                        break;
                    }
                }
            }
        }
        //此时每行非0位都已小于等于k,最后保证每列非0位也要小于等于k
        for(int j=1;j<=m;j++){
            cnt0+=max(0ll,col[j]-k);
        }
        ans=min(ans,k*c+cnt0*d);
    }
    cout<<ans<<endl;
}
 
 
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    while(_--)solve();
    return 0;
}
