//https://www.luogu.com.cn/problem/P3413
//@@@
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod=1e9+7;

bool check(const string& num){
    for(ll pprev=-2,prev=-1,i=0;i<num.size();pprev++,prev++,i++){
        if(pprev>=0&&num[pprev]==num[i]){
            return true;
        }
        if(prev>=0&&num[prev]==num[i]){
            return true;
        }
    }
    return false;
}

ll helper(const string& num){
    ll n=num.size();
    ll all=1;
    for(ll i=0;i<n;i++){
        all=(all*10%mod+num[i]-'0')%mod;
    }
    vector<vector<vector<vector<ll>>>> mem(n,vector<vector<vector<ll>>>(2,vector<vector<ll>>(11,vector<ll>(11,-1))));
    function<ll(ll,bool,ll,ll)> dfs=[&](ll p,bool free,ll pprev,ll prev)->ll{
        if(p==num.size()){
            return 1;
        }
        if(mem[p][free][pprev][prev]!=-1){
            return mem[p][free][pprev][prev];
        }
        ll cur=num[p]-'0';
        ll res=0;
        if(prev==10) res=(res+dfs(p+1,true,10,10))%mod;
        for(ll i=prev==10?1:0;i<=(free?9:cur);i++) if(i!=prev&&i!=pprev){
            res=(res+dfs(p+1,free||i<cur,prev,i))%mod;
        }
        mem[p][free][pprev][prev]=res;
        return res;
    };  
    return (all-dfs(0,false,10,10)+mod)%mod;
}

void solve(){
    // 定义两个字符串变量l和r，用于存储输入的两个字符串
    string l,r;
    // 从标准输入读取两个字符串
    cin>>l>>r;
    // 如果字符串l为"0"，则将其改为"1"
    if(l=="0") l="1";
    // 调用helper函数计算字符串r的结果，并减去helper函数计算字符串l的结果
    // 加上mod再取模，得到最终结果res
    ll res=(helper(r)-helper(l)+mod)%mod;
    // 检查字符串l是否满足某些条件，如果满足则将结果res加1再取模
    if(check(l)){
        res=(res+1)%mod;
    }
    // 输出最终结果res
    cout<<res<<endl;
}

signed main(){
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}