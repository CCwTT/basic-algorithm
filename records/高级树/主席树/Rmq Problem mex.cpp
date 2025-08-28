//https://www.luogu.com.cn/problem/P4137
//@@@
//persistent segment tree
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

const ll MAXN=2e5+5;
const ll MAXT=MAXN*50;
ll n,m;
ll a[MAXN];
int root[MAXN];
int lc[MAXT];
int rc[MAXT];
ll late_left[MAXT];
ll cnt=0;

ll clone(ll p){
    ll q=++cnt;
    lc[q]=lc[p];
    rc[q]=rc[p];
    late_left[q]=late_left[p];
    return q;
}

void up(ll p){
    late_left[p]=min(late_left[lc[p]],late_left[rc[p]]);
}

ll build(ll l,ll r){
    ll p=++cnt;
    if(l==r){
        late_left[p]=0;
    }else{
        ll m=l+r>>1;
        lc[p]=build(l,m);
        rc[p]=build(m+1,r);
        up(p);
    }
    return p;
}

ll update(ll p,ll l,ll r,ll x,ll v){
    p=clone(p);
    if(l==r){
        late_left[p]=v;
    }else{
        ll m=l+r>>1;
        if(x<=m) lc[p]=update(lc[p],l,m,x,v);
        if(x>m) rc[p]=update(rc[p],m+1,r,x,v);
        up(p);
    }
    return p;
}

ll query(ll p,ll l,ll r,ll line){
    if(l==r){
        return l;
    }
    ll m=l+r>>1;
    if(late_left[lc[p]]<line) return query(lc[p],l,m,line);
    else return query(rc[p],m+1,r,line);
}

void prepare(){
    root[0]=build(0,n);
    for(ll i=1;i<=n;i++){
        if(a[i]>n||a[i]<0){
            root[i]=root[i-1];
        }else{
            root[i]=update(root[i-1],0,n,a[i],i);
        }
    }
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    prepare();
    for(ll i=1;i<=m;i++){
        ll l,r;
        cin>>l>>r;
        cout<<query(root[r],0,n,l)<<endl;
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
