//https://www.luogu.com.cn/problem/P3919
//@@@
//persistent segment tree(persistent array)
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

void Log(vector<ll>& a){
	ll n=a.size();
	for(ll i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

const ll MAXN=1e6+5;
const ll MAXT=MAXN*25; //(O(m)=O(n))
ll n,m;
ll a[MAXN],root[MAXN],val[MAXT],lc[MAXT],rc[MAXT],cnt=0;

ll clone(ll p){
    ll q=++cnt;
    val[q]=val[p];
    lc[q]=lc[p];
    rc[q]=rc[p];
    return q;
}

ll build(ll l,ll r){
    ll p=++cnt;
    if(l==r){
        val[p]=a[l];
    }else{
        ll m=l+r>>1;
        lc[p]=build(l,m);
        rc[p]=build(m+1,r);
    }
    return p;
}

ll update(ll p,ll l,ll r,ll x,ll v){
    ll q=clone(p);
    if(l==r){
        val[q]=v;
    }else{
        ll m=l+r>>1;
        if(x<=m) lc[q]=update(lc[q],l,m,x,v);
        else rc[q]=update(rc[q],m+1,r,x,v);
    }
    return q;
}

ll query(ll p,ll l,ll r,ll x){
    if(l==r){
        return val[p];
    }
    ll m=l+r>>1;
    if(x<=m) return query(lc[p],l,m,x);
    else return query(rc[p],m+1,r,x);
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    root[0]=build(1,n);
    for(ll i=1;i<=m;i++){
        ll vs,op,x,y;
        cin>>vs>>op;
        if(op==1){
            cin>>x>>y;
            root[i]=update(root[vs],1,n,x,y);
        }else{
            cin>>x;
            root[i]=root[vs];
            cout<<query(root[i],1,n,x)<<'\n';
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
