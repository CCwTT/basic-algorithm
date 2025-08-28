//https://ac.nowcoder.com/acm/contest/108300/B
//@@@
//bit operation
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

void solve(){
    ll a,b,c;
    cin>>a>>b>>c;
    vector<ll> ans;
    if(a==0&&b==0&&c!=0){
        cout<<-1<<endl;
        return;
    }
    if(__lg(a)>__lg(b)){
        ans.push_back(4);
        b=b^a;
    }else if(__lg(a)<__lg(b)){
        ans.push_back(3);
        a=a^b;
    }
    ll high=__lg(a);
    if(__lg(c)>=high){
        for(ll i=0;i<__lg(c)-high;i++){
            ll bitc=c>>(__lg(c)-i)&1;
            if((a>>high&1)==bitc){
                ans.push_back(1);
                a<<=1;
            }else{
                ans.push_back(3);
                ans.push_back(1);
                a=a^b;
                a<<=1;
            }
        }
        for(ll i=high;i>=0;i--){
            if((a>>i&1)!=(c>>i&1)){
                ans.push_back(3);
                a=a^b;
            }
            ans.push_back(2);
            b>>=1;
        }
    }else{
        for(ll i=high;i>=0;i--){
            if((a>>i&1)!=(c>>i&1)){
                ans.push_back(3);
                a=a^b;
            }
            ans.push_back(2);
            b>>=1;
        }
    }
    ans.push_back(4);
    cout<<ans.size()<<endl;
    for(ll i=0;i<ans.size();i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
}

signed main(){
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}