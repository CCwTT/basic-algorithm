//https://www.lanqiao.cn/problems/113/learning/
//@@@
//backtrace
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

void solve(){
    string s;
    cin>>s;
    map<string,ll> mem; 
    function<ll(void)> dfs=[&]()->ll{
        if(s.find("LOL")!=string::npos) return -1;
        if(s.find("*")==string::npos) return 0;
        if(mem.count(s)) return mem[s];
        ll& res=mem[s];
        res=-1;
        for(ll i=0;i<s.size();i++){
            if(s[i]=='*'){
                s[i]='L';
                ll ret=dfs();
                s[i]='*';
                if(ret==-1) return res=1;
                if(ret==0) res=0;
                s[i]='O';
                ret=dfs();
                s[i]='*';
                if(ret==-1) return res=1;
                if(ret==0) res=0;
            }
        }  
        return res;
    };
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
