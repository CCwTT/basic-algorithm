//https://www.lanqiao.cn/problems/806/learning/?isWithAnswer=true
//@@@
//unique decomposition theorem,dfs exhaustive search
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll qpow(ll x,ll n){
    if(x==0) return 0;
    ll res=1;
    while(n){
        if(n&1) res=res*x;
        x=x*x;
        n>>=1;
    }
    return res;
}

const ll MX=2e6+5;
vector<ll> primes;
bool np[MX];
vector<vector<ll>> pf(61);
int init=[]{
    for(ll i=2;i<MX;i++){
        if(!np[i])primes.push_back(i);
        for(auto p:primes){
            if(p*i>=MX)break;
            np[p*i]=true;
            if(i%p==0)break;
        }
    }
    for(ll i=2;i<=60;i++){
        ll x=i;
        for(ll j=2;j*j<=x;j++){
            while(x%j==0){
                pf[i].push_back(j);
                x/=j;
            }
        }
        if(x>1){
            pf[i].push_back(x);
        }
        pf[i].push_back(1);
    }
    return 0;
}();

map<vector<ll>,ll> mp;
ll dfs(vector<ll> vec){
    if(vec.size()<=1) return LLONG_MAX/2;
    if(mp[vec]) return LLONG_MAX/2;
    ll& res=mp[vec];
    res=1;
    sort(vec.begin(),vec.end(),greater<ll>());
    for(ll i=0;i<vec.size();i++){
        res*=qpow(primes[i],vec[i]-1);
    }
    for(ll i=0;i<vec.size();i++){
        for(ll j=i+1;j<vec.size();j++){
            vector<ll> nvec=vec;
            nvec.erase(nvec.begin()+j);  //Think about why earse j first (i、、、j-1)
            nvec.erase(nvec.begin()+i);
            nvec.push_back(vec[i]*vec[j]);
            res=min(dfs(nvec),res);
        } 
    }
    return res;
}

void solve(){
    vector<ll> res(61);
    res[1]=1;
    for(ll i=2;i<=60;i++){
        res[i]=dfs(pf[i]);
    }
    ll ans=0;
    for(ll i=1;i<=60;i++){
        ans+=res[i];
    } 
    cout<<ans<<endl; 
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
