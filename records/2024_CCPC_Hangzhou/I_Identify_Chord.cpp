#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

using pii=pair<ll,ll>;
constexpr ll N=50010,M=20;
ll n,k;
ll a[N],b[N],g[N],lnear[N],rnear[N];
ll st[N][M];

void solve(){
    cin>>n>>k;
    for(ll i=1;i<=n;i++)cin>>a[i];
    for(ll i=1;i<n;i++)
        b[i]=abs(a[i]-a[i+1]);
    b[n]=0;
    for(ll i=1;i<=n;i++)st[i][0]=b[i];
    for(ll j=1;j<M;j++)
        for(ll i=1;i+(1<<j)-1<=n;i++)
            st[i][j]=gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    vector<ll> pre;
    ll gd=0,mi=*min_element(a+1,a+n+1);
    for(ll i=1;i<=n;i++)
        gd=gcd(gd,a[i]-mi);
    if(gd==0)return void(cout<<k<<" "<<k*(k+1)/2<<endl);
    if(gd==1)return void(cout<<0<<" "<<0<<endl);
    for(ll i=1;i*i<=gd;i++)
        if(gd%i==0){
            pre.push_back(i-mi);
            pre.push_back(gd/i-mi);
        }
    pre.erase(
        remove_if(pre.begin(),pre.end(),[&](ll x){
            return x>k||x<1;
        }),
        pre.end()
    );
    sort(pre.begin(),pre.end());
    pre.erase(unique(pre.begin(),pre.end()),pre.end());
    stack<ll> stk;
    for(ll i=1;i<=n;i++){
        while(!stk.empty()&&a[stk.top()]>a[i]) stk.pop();
        lnear[i]=stk.empty()?1:stk.top()+1;
        stk.push(i);
    }
    stack<ll>().swap(stk);
    for(ll i=n;i>=1;i--){
        while(!stk.empty()&&a[stk.top()]>a[i]) stk.pop();
        rnear[i]=stk.empty()?n:stk.top()-1;
        stk.push(i);
    }
    auto f=[&](ll l,ll r){
        if(l>--r)return 0ll;
        ll t=__lg(r-l+1);
        return gcd(st[l][t],st[r-(1<<t)+1][t]);
    };
    for(ll i=1;i<=n;i++) g[i]=f(lnear[i],rnear[i]);
    ll cnt,sum;
    for(ll x:pre){
        bool flag=true;
        for(ll i=1;i<=n;i++)
            if(g[i]%(a[i]+x)){
                flag=false;
                break;
            }
        if(flag){
            cnt++;
            sum+=x;
        }
    }
    cout<<cnt<<" "<<sum<<endl;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
