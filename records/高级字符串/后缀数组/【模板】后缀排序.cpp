//https://www.luogu.com.cn/problem/P3809
//@@@
//SA(radix sort,bucket sort,doubling method)
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const ll MAXN=2e6+5;
string s;
ll n,nbuc=122;
ll bel[MAXN],tmp[MAXN],buc[MAXN],sa[MAXN],rk[MAXN],h[MAXN];

void get_sa(){
    for(ll i=1;i<=n;i++) buc[bel[i]=s[i]]++;
    for(ll i=1;i<=nbuc;i++) buc[i]+=buc[i-1];
    for(ll i=n;i>=1;i--) sa[buc[bel[i]]--]=i;
    for(ll k=1;k<=n;k<<=1){
        //sort by the second key
        memset(buc,0,sizeof(buc));
        for(ll i=1;i<=n;i++) tmp[i]=sa[i];
        for(ll i=1;i<=n;i++) buc[bel[tmp[i]+k]]++;
        for(ll i=1;i<=nbuc;i++) buc[i]+=buc[i-1];
        for(ll i=n;i>=1;i--) sa[buc[bel[tmp[i]+k]]--]=tmp[i];
        //sort by the first key
        memset(buc,0,sizeof(buc));
        for(ll i=1;i<=n;i++) tmp[i]=sa[i];
        for(ll i=1;i<=n;i++) buc[bel[tmp[i]]]++;
        for(ll i=1;i<=nbuc;i++) buc[i]+=buc[i-1];
        for(ll i=n;i>=1;i--) sa[buc[bel[tmp[i]]]--]=tmp[i];
        //put suffix array into buc array
        for(ll i=1;i<=n;i++) tmp[i]=bel[i];
        nbuc=0;
        for(ll i=1;i<=n;i++){
            if(tmp[sa[i]]==tmp[sa[i-1]]&&tmp[sa[i]+k]==tmp[sa[i-1]+k]){
                bel[sa[i]]=nbuc;
            }else{
                bel[sa[i]]=++nbuc;
            }
        }
        if(nbuc==n) break;
    }
}

void solve(){
    cin>>s;
    n=s.size();
    s=" "+s;
    get_sa();
    for(ll i=1;i<=n;i++){
        cout<<sa[i]<<" ";
    }
    cout<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}