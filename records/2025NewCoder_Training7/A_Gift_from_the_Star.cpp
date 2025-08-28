//https://ac.nowcoder.com/acm/contest/108304/A
//KNOWLEDGE:逆序对定理:一次任意2位置的swap要么使逆序对个数+1,要么使逆序对个数-1
//Inverse Pair Theorem: A swap of any two positions at a time either increases the number of inverse pairs by 1 or decreases the number of inverse pairs by 1.
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll M=105,N=10,K=4;
ll id,m,k,n;
ll a[M][N][N*N];
ll fw[M];
vector<pair<ll,ll>> res;
bool ans[M];

void fw_update(ll x,ll v){
    while(x<M){
        fw[x]+=v;
        x+=x&-x;
    }
}

ll fw_query(ll x){
    ll res=0;
    while(x>0){
        res+=fw[x];
        x&=x-1;
    }
    return res;
}

void solve(){
    cin>>id>>m>>k>>n;
    for(ll i=0;i<m;i++){
        for(ll j=0;j<k;j++){
            for(ll x=0;x<n*n;x++){
                cin>>a[i][j][x];
            }
        }
    }
    for(ll i=0;i<m;i++){
        ll score=0;
        for(ll j=0;j<k;j++){
            memset(fw,0,sizeof(fw));
            ll cnt=0;
            for(ll x=0;x<n*n;x++){
                cnt+=x-fw_query(a[i][j][x]);
                fw_update(a[i][j][x],1);
            }
            score+=~cnt&1;
        }
        res.push_back({score,i});
    }
    sort(res.begin(),res.end());
    for(ll i=0;i<m/2;i++){
        ans[res[i].second]=true;
    }
    for(ll i=0;i<m;i++){
        cout<<ans[i];
    }
    cout<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
    }
    return 0;
}