#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

using pii=pair<ll,ll>;
constexpr ll N=50010,HIGH=19;
ll n,k;
ll a[N],b[N],g[N],lside[N],rside[N];
ll st[N][HIGH];

void solve(){
    cin>>n>>k;
    for(ll i=1;i<=n;i++)cin>>a[i];
    for(ll i=1;i<n;i++)
        b[i]=abs(a[i]-a[i+1]);
    b[n]=0;
    for(ll i=1;i<=n;i++) st[i][0]=b[i];
    for(ll j=1;j<=HIGH;j++)
        for(ll i=1;i+(1<<j)-1<=n;i++)
            st[i][j]=__gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    ll gd=0,mn=*min_element(a+1,a+n+1);
    for(ll i=1;i<=n;i++)
        gd=__gcd(gd,a[i]-mn);
    if(gd==0)return void(cout<<k<<" "<<k*(k+1)/2<<endl);
    if(gd==1)return void(cout<<0<<" "<<0<<endl);

    vector<ll> factors;
    for(ll i=1;i*i<=gd;i++){
        if(gd%i==0){
            factors.push_back(i);
            factors.push_back(gd/i);
        }
    }
    vector<ll> S_x;
    for(auto x:S_x){
        cout<<x<<" ";
    }
    cout<<endl;
    for(auto factor:factors){
        if(1<=factor-mn&&factor-mn<=k){
            S_x.push_back(factor-mn);
        }
    }
    sort(S_x.begin(),S_x.end());
    S_x.erase(unique(S_x.begin(),S_x.end()),S_x.end());
    
    stack<ll> stk;
    for(ll i=1;i<=n;i++){
        while(!stk.empty()&&a[stk.top()]>a[i]) stk.pop();
        lside[i]=stk.empty()?1:stk.top()+1;
        stk.push(i);
    }
    stack<ll>().swap(stk);
    for(ll i=n;i>=1;i--){
        while(!stk.empty()&&a[stk.top()]>a[i]) stk.pop();
        rside[i]=stk.empty()?n:stk.top()-1;
        stk.push(i);
    }
    auto f=[&](ll l,ll r){
        if(l>--r) return 0ll;
        ll high=__lg(r-l+1);
        return __gcd(st[l][high],st[r-(1<<high)+1][high]);
    };
    for(ll i=1;i<=n;i++) g[i]=f(lside[i],rside[i]);
    ll cnt=0,sum=0;
    for(ll x:S_x){
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
