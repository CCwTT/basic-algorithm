#include<bits/stdc++.h>
using namespace std;
//#define endl '\n
#define inf LLONG_MAX/2
typedef long long ll;

void solve(){
    ll n,t;
    cin>>n>>t;
    string s;
    cin>>s;
    vector<ll> len;
    ll mx_len=0;
    ll pre=0,suf=0;
    for(ll i=0;i<n;){
        while(i<n&&s[i]!='0')i++;
        if(i==n) break;
        ll j=i+1;
        while(j<n&&s[j]=='0')j++;
        mx_len=max(mx_len,j-i);
        if(i==0) pre=j-i;
        if(j==n) suf=j-i;
        if(i!=0&&j!=n) len.push_back(j-i);
        i=j;
    }
    if(pre+suf){
        len.push_back(pre+suf);
    }
    mx_len=max(mx_len,pre+suf);
    sort(len.begin(),len.end());
    ll ans=max(0ll,mx_len-1-t);
    for(ll i=0;i<(ll)len.size()-1;i++){
        ans+=max(0ll,len[i]-2*t);
    }
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