//https://acm.hdu.edu.cn/contest/problem?cid=1174&pid=1008
//@@@
//greedy
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

constexpr ll N=-1;

void solve(){
    ll n;
    cin>>n;
    string s;
    cin>>s;
    ll ans=LLONG_MAX/2,cur;
    //010101...01
    string tar;
    for(ll i=0,c=0;i<n;i++,c=1-c){
        tar+=c+'0';  
    }
    cur=0;
    ll i=0;
    while(i<n){
        if(s[i]==tar[i]){
            i++;
            continue;
        }
        cur++;
        i+=2;
    }
    ans=min(ans,cur);

    cur=0,i=0;
    swap(s[0],s[n-1]);
    cur++;
    while(i<n){
        if(s[i]==tar[i]){
            i++;
            continue;
        }
        cur++;
        i+=2;
    }
    ans=min(ans,cur);
    swap(s[0],s[n-1]);

    //101010...10
    tar.clear();
    for(ll i=0,c=1;i<n;i++,c=1-c){
        tar+=c+'0';  
    }
    cur=0,i=0;
    while(i<n){
        if(s[i]==tar[i]){
            i++;
            continue;
        }
        cur++;
        i+=2;
    }
    ans=min(ans,cur);

    cur=0,i=0;
    swap(s[0],s[n-1]);
    cur++;
    while(i<n){
        if(s[i]==tar[i]){
            i++;
            continue;
        }
        cur++;
        i+=2;
    }
    ans=min(ans,cur);
    swap(s[0],s[n-1]);
    cout<<ans<<endl;
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