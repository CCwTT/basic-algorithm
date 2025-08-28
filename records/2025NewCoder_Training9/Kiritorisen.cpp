#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll N=2e5+5;
ll n,k;
ll a[N],cnt[N];

void solve(){
    cin>>n>>k;
    ll lim=min(4*n,k);
    ll mx=0;
    for(ll i=0;i<n;i++){
        cin>>a[i];
        mx=max(mx,a[i]);
    }
    queue<ll> q;
    ll now=0,tot=0;
    for(ll i=1;i<n;i++){
        q.push(i);
    }
    while(lim--){
        k--;
        ll x=q.front();
        q.pop();
        cnt[x]++,cnt[now]++;
        tot++;
        if(a[x]>=a[now]||tot==n){
            q.push(now);
            now=x;
            tot=1;
        } else {
            q.push(x);
        }
    }
    while(k){
        ll x=q.front();
        if(a[x]==mx){
            break;
        }
        k--;
        q.pop();
        cnt[x]++,cnt[now]++;
        tot++;
        if(a[x]>=a[now]||tot==n){
            q.push(now);
            now=x;
            tot=1;
        } else {
            q.push(x);
        }
    }
    ll round=k/(2*n-2);
    k-=(2*n-2)*round;
    for(ll i=0;i<n;i++){
        if(i!=now&&i!=q.front()){
            cnt[i]+=2*round;
        } else {
            cnt[i]+=n*round;
        }
    }
    while(k--){
        ll x=q.front();
        q.pop();
        cnt[x]++,cnt[now]++;
        tot++;
        if(a[x]>=a[now]||tot==n){
            q.push(now);
            now=x;
            tot=1;
        } else {
            q.push(x);
        }
    }
    for(ll i=1;i<=n;i++){
        cout<<cnt[i-1]<<(i==n?'\n':' ');
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}