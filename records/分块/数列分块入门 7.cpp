//https://loj.ac/p/6283
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
ll add[MAXB];
ll mul[MAXB];
ll n,len,nb;

ll lend(ll X){
    return (X-1)*len+1;
}

ll rend(ll X){
    return min(n,X*len);
}

void put_tag(ll X){
    for(ll i=lend(X);i<=rend(X);i++){
        a[i]=(a[i]*mul[X]+add[X])%mod;
    }
    mul[X]=1;
    add[X]=0;
}

void solve(){
    fill(mul,mul+MAXB,1);
    cin>>n;
    len=(ll)sqrt(n);
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        bel[i]=(i-1)/len+1;
    }
    for(ll o=1;o<=n;o++){
        ll op,l,r,c;
        cin>>op>>l>>r>>c;
        ll L=bel[l]!=bel[l-1]?bel[l]:bel[l]+1;
        ll R=bel[r]!=bel[r+1]?bel[r]:bel[r]-1;
        if(op==0){
            if(bel[l]==bel[r]){
                put_tag(bel[l]);
                for(ll i=l;i<=r;i++){
                    a[i]=(a[i]+c)%mod;
                }
            }else{
                if(l!=lend(L)) put_tag(bel[l]);
                for(ll i=l;i<lend(L);i++){
                    a[i]=(a[i]+c)%mod;
                }
                if(r!=rend(R)) put_tag(bel[r]);
                for(ll i=r;i>rend(R);i--){
                    a[i]=(a[i]+c)%mod;
                }
                for(ll b=L;b<=R;b++){
                    add[b]=(add[b]+c)%mod;
                }
            }
        }else if(op==1){
            if(bel[l]==bel[r]){
                put_tag(bel[l]);
                for(ll i=l;i<=r;i++){
                    a[i]=(a[i]*c)%mod;
                }
            }else{
                if(l!=lend(L)) put_tag(bel[l]);
                for(ll i=l;i<lend(L);i++){
                    a[i]=(a[i]*c)%mod;
                }
                if(r!=rend(R)) put_tag(bel[r]);
                for(ll i=r;i>rend(R);i--){
                    a[i]=(a[i]*c)%mod;
                }
                for(ll b=L;b<=R;b++){
                    mul[b]=(mul[b]*c)%mod;
                    add[b]=(add[b]*c)%mod;
                }
            }
        }else{
            cout<<(a[r]*mul[bel[r]]+add[bel[r]])%mod<<endl;
        }
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
