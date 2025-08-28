//https://www.luogu.com.cn/problem/P6225
//@@@
//fenwick tree
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

const ll MAXN=2e5+5;
ll a[MAXN];
ll tr[2][MAXN];
ll n,m;

void update(ll op,ll p,ll v){
    while(p<=n){
        tr[op][p]^=v;
        p+=p&-p;
    }
}

ll query(ll op,ll p){
    ll res=0;
    while(p){
        res^=tr[op][p];
        p&=p-1;
    }
    return res;
}

ll query(ll op,ll l,ll r){
    return query(op,r)^query(op,l-1);
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        update(i&1,i,a[i]);
    }
    while(m--){
        ll op;
        cin>>op;
        if(op==1){
            ll x,v;
            cin>>x>>v;
            update(x&1,x,v^a[x]);
            a[x]=v;
        }else{
            ll l,r;
            cin>>l>>r;
            ll len=r-l+1;
            if(len&1){
                cout<<query(l&1,l,r)<<endl;
            }else{
                cout<<0<<endl;
            }
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