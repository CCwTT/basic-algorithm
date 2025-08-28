//https://www.luogu.com.cn/problem/P5677
//@@@
//fenwick tree
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

const ll MAXN=3e5+5;
ll n,m;
pair<ll,ll> A[MAXN];
vector<tuple<ll,ll,ll>> P;
vector<tuple<ll,ll,ll>> Q;
ll tr[MAXN];
ll ans[MAXN];

void update(ll x,ll v){
    while(x<=n){
        tr[x]+=v;
        x+=x&-x;
    }
}

ll query(ll x){
    ll res=0;
    while(x){
        res+=tr[x];
        x&=x-1;
    }
    return res;
}

ll query(ll x,ll y){
    return query(y)-query(x-1);
}

void add(ll id1,ll id2){
    if(id1>id2) swap(id1,id2);
    if(!P.empty()&&get<0>(P.back())==id1&&get<1>(P.back())==id2){
        get<2>(P.back())++;
    }else{
        P.emplace_back(id1,id2,1);
    }
}

void solve(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        cin>>A[i].first;
        A[i].second=i;
    }
    A[0]={LLONG_MIN/2,0};
    A[n+1]={LLONG_MAX/2,n+1};
    sort(A+1,A+n+1);
    for(ll i=1;i<=n;i++){
        auto [val,id]=A[i];
        auto [pval,pid]=A[i-1];
        auto [nval,nid]=A[i+1];
        if(val-pval==nval-val){
            add(pid,id);
            add(id,nid);
        }else if(val-pval<nval-val){
            add(pid,id);
        }else{
            add(id,nid);
        }
    }
    sort(P.begin(),P.end(),[&](const tuple<ll,ll,ll>& u,const tuple<ll,ll,ll>& v){
        return get<1>(u)<get<1>(v);
    });
    for(ll i=1;i<=m;i++){
         ll l,r;
         cin>>l>>r;
         Q.emplace_back(l,r,i);
    }
    sort(Q.begin(),Q.end(),[&](const tuple<ll,ll,ll>& u,const tuple<ll,ll,ll>& v){
        return get<1>(u)<get<1>(v);
    });
    ll rm=0;
    ll pi=0;
    for(ll i=0;i<m;){
        rm=get<1>(Q[i]);
        ll j=i+1;
        while(j<m&&get<1>(Q[j])==rm){
            j++;
        }
        while(pi<P.size()&&get<1>(P[pi])<=rm){
            auto [id1,id2,cnt]=P[pi];
            update(id1,cnt);
            pi++;
        }
        for(ll k=i;k<j;k++){
            auto [l,r,id]=Q[k];
            ans[id]=query(r)-query(l-1);
        }
        i=j;
    }
    ll ANS=0;
    for(ll i=1;i<=m;i++){
        ANS+=ans[i]*i;
    }
    cout<<ANS<<endl;
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