#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll mod=998244353;
const ll N=2e5+5;
ll n,m;

ll pw[N];

ll compute_even(vector<ll>& vec){
    ll ans=0;
    sort(vec.begin(),vec.end());
    ll nv=vec.size();
    vector<ll> diff(nv);
    diff[0]=vec[0];
    for(ll i=1;i<nv;i++){
        diff[i]=vec[i]-vec[i-1];
    }
    ll mn_diff=*min_element(diff.begin()+1,diff.end());
    vector<ll> ids;
    for(ll i=1;i<nv;i++){
        if(diff[i]==mn_diff){
            ids.push_back(i);
        }
    }
    ll idx=ids[ids.size()/2];
    ans+=(vec[idx]-vec[idx-1])*pw[nv/2-1]%mod;
    ans%=mod;
    ll i=0,j=nv-1,d=nv/2-2;
    while(i<j){
        if(i==idx-1||i==idx){
            i++;
        }else if(j==idx-1||j==idx){
            j--;
        }else{
            ans-=(vec[j]-vec[i])*pw[d--]%mod;
            ans=(ans+mod)%mod;
            i++,j--;
        }
    }
    return ans;
}

ll compute_odd1(vector<ll>& vec){
    ll ans=0;
    sort(vec.begin(),vec.end());
    ll nv=vec.size();
    ans=vec[0]*pw[nv/2]%mod;
    ll i=1,j=nv-1,d=nv/2-1;
    while(i<j){
        ans-=(vec[j]-vec[i])*pw[d--]%mod;
        ans=(ans+mod)%mod;
        i++,j--;
    }
    return ans;
}

ll compute_odd2


void solve(){
    cin>>n>>m;
    pw[0]=1;
    for(ll i=1;i<=n/2+5;i++){
        pw[i]=pw[i-1]*m%mod;
    }
    vector<ll> a(n);
    for(ll i=0;i<n;i++){
        cin>>a[i];
    }
    sort(a.begin(),a.end());
    vector<ll> b;
    for(ll i=n-1;i>=0;i--){
        b.push_back(a[i]);
        if(a[i]==0){
            break;
        }
    }
    a=b;
    n=a.size();
    if(n==1){
        cout<<a[0]<<endl;
        return;
    }
    if(~n&1){
        cout<<compute_even(a)<<endl;
    }else{
        if(n==1){
            cout<<a[0]*pw[0]%mod<<endl;
        }else{
            sort(a.begin(),a.end());
            if(a[0]!=0){
                cout<<compute_odd1(a)<<endl;
            }else{
                if(a[n-1]==0){
                    cout<<0<<endl;
                }else{
                    vector<ll> b;
                    for(ll i=n-1;;i--){
                        b.push_back(a[i]);
                        if(a[i]==0){
                            break;
                        }
                    }
                    ll nb=b.size();
                    sort(b.begin(),b.end());
                    ll ans=compute_odd2(a);
                    ans=max(ans)
                }
            }
        }
        
    }
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