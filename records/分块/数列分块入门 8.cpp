//https://loj.ac/p/6284
//@@@
//block algorithm
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

const ll MAXN=100005;
const ll MAXB=400;
const ll mod=10007;
ll a[MAXN];
ll bel[MAXN];
ll rst[MAXB];
ll n,len,ans;
ll l,r,c;

ll lend(ll X){
    return (X-1)*len+1;
}

ll rend(ll X){
    return min(n,X*len);
}

ll f(ll l,ll r){
    ll res=0;
    if(rst[bel[l]]==LLONG_MIN/2){
        for(ll i=l;i<=r;i++){
            res+=a[i]==c;
            a[i]=c;
        }
    }else{
        res=rst[bel[l]]==c?r-l+1:0;
        for(ll i=lend(bel[l]);i<=rend(bel[l]);i++){
            a[i]=(l<=i&&i<=r)?c:rst[bel[l]];
        }
        rst[bel[l]]=LLONG_MIN/2;
    }
    return res;
}

void solve(){
    fill(rst,rst+MAXB,LLONG_MIN/2);
    cin>>n;
    len=(ll)sqrt(n);
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        bel[i]=(i-1)/len+1;
    }
    for(ll o=1;o<=n;o++){
        cin>>l>>r>>c;
        ll L=bel[l]!=bel[l-1]?bel[l]:bel[l]+1;
        ll R=bel[r]!=bel[r+1]?bel[r]:bel[r]-1;
        ans=0;
        if(bel[l]==bel[r]){
            ans=f(l,r);
        }else{
            ans+=f(l,lend(L)-1);
            ans+=f(rend(R)+1,r);
            for(ll b=L;b<=R;b++){
                if(rst[b]!=LLONG_MIN/2){
                    ans+=rst[b]==c?len:0;
                    rst[b]=c;
                }else{
                    ans+=f(lend(b),rend(b));
                    rst[b]=c;
                }
            }
        }
        cout<<ans<<endl;
    }
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
