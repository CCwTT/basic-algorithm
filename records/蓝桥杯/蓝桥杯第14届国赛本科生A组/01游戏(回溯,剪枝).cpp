//https://www.lanqiao.cn/problems/17100/learning/
//@@@
//backtrack,pruning
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

void Log(vector<ll>& a){
	ll n=a.size();
	for(ll i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

void solve(){
    ll n;
    cin>>n;
    vector<string> grid(n);
    for(ll i=0;i<n;i++){
        grid[i].resize(n);
    }
    vector<vector<ll>> row(2,vector<ll>(n)),col(2,vector<ll>(n));
    for(ll i=0;i<n;i++){
        for(ll j=0;j<n;j++){
            cin>>grid[i][j];
            if(grid[i][j]=='0'){
                row[0][i]++;
                col[0][j]++;
            }else if(grid[i][j]=='1'){
                row[1][i]++;
                col[1][j]++;
            }
        }
    }
    unordered_set<string> row_set;

    auto next_ij=[&](ll i,ll j)->pair<ll,ll>{
        return j==n-1?pair<ll,ll>{i+1,0}:pair<ll,ll>{i,j+1};
    };

    auto print_grid=[&]()->void{
        for(ll i=0;i<n;i++){
            for(ll j=0;j<n;j++){
                cout<<grid[i][j];
            }
            cout<<endl;
        }
        cout<<endl;
    };

    auto check_left=[&](ll i,ll j,char v)->bool{
        if(j-1>=0&&j-2>=0&&grid[i][j-1]==v&&grid[i][j-2]==v){
            return false;
        }
        return true;
    };

    auto check_right=[&](ll i,ll j,char v)->bool{
        if(j+1<n&&j+2<n&&grid[i][j+1]==v&&grid[i][j+2]==v){
            return false;
        }
        return true;
    };

    auto check_up=[&](ll i,ll j,char v)->bool{
        if(i-1>=0&&i-2>=0&&grid[i-1][j]==v&&grid[i-2][j]==v){
            return false;
        }
        return true;
    };

    auto check_down=[&](ll i,ll j,char v)->bool{
        if(i+1<n&&i+2<n&&grid[i+1][j]==v&&grid[i+2][j]==v){
            return false;
        }
        return true;
    };

    auto check_all=[&](ll i,ll j,char v)->bool{
        return check_left(i,j,v)&&check_right(i,j,v)&&check_up(i,j,v)&&check_down(i,j,v);
    };

    auto get_col_string=[&](ll j)->string{
        string res;
        for(ll i=0;i<n;i++){
            res+=grid[i][j];
        }
        return res;
    };

    function<void(ll,ll)> dfs=[&](ll i,ll j)->void{
        if(i==n){
            unordered_set<string> col_set;
            for(ll j=0;j<n;j++){
                string col=get_col_string(j);
                if(col_set.count(col)){
                    return;
                }
                col_set.insert(col);
            }
            print_grid();
            return;
        }
        if(grid[i][j]!='_'){
            if(check_all(i,j,grid[i][j])){
                auto [ni,nj]=next_ij(i,j);
                dfs(ni,nj);
            }
            return;
        }
        grid[i][j]='0';
        row[0][i]++;
        col[0][j]++;
        if(row[0][i]<=n/2&&col[0][j]<=n/2&&check_all(i,j,'0')){
            if(j<n-1||j==n-1&&!row_set.count(grid[i])){
                if(j==n-1){
                    row_set.insert(grid[i]);
                }
                auto [ni,nj]=next_ij(i,j);
                dfs(ni,nj);
                if(j==n-1){
                    row_set.erase(grid[i]);
                }
            }
        }
        grid[i][j]='_';
        row[0][i]--;
        col[0][j]--;
        
        grid[i][j]='1';
        row[1][i]++;
        col[1][j]++;
        if(row[1][i]<=n/2&&col[1][j]<=n/2&&check_all(i,j,'1')){
            if(j<n-1||j==n-1&&!row_set.count(grid[i])){
                if(j==n-1){
                    row_set.insert(grid[i]);
                }
                auto [ni,nj]=next_ij(i,j);
                dfs(ni,nj);
                if(j==n-1){
                    row_set.erase(grid[i]);
                }
            }
        }
        grid[i][j]='_';
        row[1][i]--;
        col[1][j]--;
    };
    dfs(0,0);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}
