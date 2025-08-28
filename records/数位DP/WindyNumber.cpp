#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll helper(ll x){
    // if(x==0){
    //     return 0;  //return 1(anyway,should conform with below)
    // }
    string s=to_string(x);
    ll n=s.size();
    vector<vector<vector<ll>>> mem(n,vector<vector<ll>>(2,vector<ll>(15,-1)));
    function<ll(ll,bool,ll)> dfs=[&](ll p,bool free,ll prev)->ll{
        if(p==n){
            return prev!=12; //return 1;
        }
        if(~mem[p][free][prev]){
            return mem[p][free][prev];
        }
        ll cur=s[p]-'0';
        ll res=0;
        if(prev==12){
            res+=dfs(p+1,true,12);
        }
        if(!free){
            for(ll i=prev==12?1:0;i<=cur;i++) if(llabs(i-prev)>=2){
                if(i==cur){
                    res+=dfs(p+1,false,i);
                }else{
                    res+=dfs(p+1,true,i);
                }
            }
        }else{
            for(ll i=prev==12?1:0;i<=9;i++) if(llabs(i-prev)>=2){
                res+=dfs(p+1,true,i);
            }
        }
        
        mem[p][free][prev]=res;
        return res;
    };

    return dfs(0,false,12);
}

void solve(){
    ll a,b;
    cin>>a>>b;
    cout<<helper(b)-helper(a-1)<<endl;
}

signed main(){
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}
