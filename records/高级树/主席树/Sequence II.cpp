//https://acm.hdu.edu.cn/showproblem.php?pid=5919
//@@@
//persistent segment tree(single point modification)
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
const ll MAXT=MAXN*40;
ll n,m;
ll a[MAXN];
int root[MAXN];
int fipos[MAXN];
int lc[MAXT];
int rc[MAXT];
ll sum[MAXT];
ll cnt=0;

ll clone(ll p){
    ll q=++cnt;
    sum[q]=sum[p];
    lc[q]=lc[p];
    rc[q]=rc[p];
    return q;
}

void up(ll p){
    sum[p]=sum[lc[p]]+sum[rc[p]];
}

ll build(ll l,ll r){
    ll p=++cnt;
    if(l==r){
        sum[p]=0;
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
        sum[p]+=v;
    }else{
        ll m=l+r>>1;
        if(x<=m) lc[p]=update(lc[p],l,m,x,v);
        else rc[p]=update(rc[p],m+1,r,x,v);
        up(p);
    }
    return p;
}

ll query_sum(ll p,ll l,ll r,ll x,ll y){
    if(x<=l&&r<=y) return sum[p];
    ll m=l+r>>1;
    ll res=0;
    if(x<=m) res+=query_sum(lc[p],l,m,x,y);
    if(y>m) res+=query_sum(rc[p],m+1,r,x,y);
    return res;
}

ll query_kth(ll p,ll l,ll r,ll k){
    if(l==r) return l;
    ll m=l+r>>1;
    if(k<=sum[lc[p]]) return query_kth(lc[p],l,m,k);
    else return query_kth(rc[p],m+1,r,k-sum[lc[p]]);
}

void init0(){
    n=m=cnt=0;
    memset(a,0,sizeof(a));
    memset(root,0,sizeof(root));
    memset(fipos,0,sizeof(fipos));
    memset(lc,0,sizeof(lc));
    memset(rc,0,sizeof(rc));
}

void prepare(){
    root[n+1]=build(1,n);
    for(ll i=n;i>=1;i--){
        if(fipos[a[i]]==0){
            root[i]=update(root[i+1],1,n,i,1);
        }else{
            root[i]=update(root[i+1],1,n,fipos[a[i]],-1);
            root[i]=update(root[i],1,n,i,1);
        }
        fipos[a[i]]=i;
    }
}

void solve(ll t){
    init0();
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    prepare();
    cout<<"Case #"<<t<<":";
    ll last_ans=0;
    for(ll i=1;i<=m;i++){
        ll l,r;
        cin>>l>>r;
        ll x=(l+last_ans)%n+1;
        ll y=(r+last_ans)%n+1;
        l=min(x,y);
        r=max(x,y);
        ll k=(query_sum(root[l],1,n,l,r)+1)/2;
        last_ans=query_kth(root[l],1,n,k);
        cout<<" "<<last_ans;
    }
    cout<<endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    for(ll i=1;i<=T;i++){
        solve(i);
    }
    return 0;
}
