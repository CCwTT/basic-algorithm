//https://www.luogu.com.cn/problem/P4849
//@@@  
//cdq,4-dimensional partial order
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define INF (LLONG_MAX/2)
#define EPS (1e-20)
typedef long long ll;
typedef __int128 i128;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef array<ll,3> al3;
typedef vector<ll> vl;
template<class T1,class T2> bool chmin(T1& x,const T2& y){return y<x?x=y,1:0;}
template<class T1,class T2> bool chmax(T1& x,const T2& y){return y>x?x=y,1:0;}

const ll N=8e4+5;
const ll MOD=998244353;
ll n;

struct discretizer{
    vector<ll> disc;
    discretizer(){
        disc.push_back(LLONG_MIN);
    }
    void insert(ll x){
        disc.push_back(x);
    }
    ll discretize(){
        sort(disc.begin()+1,disc.end());
        disc.erase(unique(disc.begin(),disc.end()),disc.end());
        return disc.size()-1;
    }
    ll get_rank(ll x){
        return lower_bound(disc.begin(),disc.end(),x)-disc.begin();
    }
}disc; ll cnt_d;

struct Node{
    ll a,b,c,d;
    ll v;
    ll i;
    bool left;
};

Node A[N],tmp1[N],tmp2[N];
ll dp[N],cnt[N];

struct trNode{
    ll v;
    ll cnt;
};
trNode tr[N];

void fw_update(ll x,ll v,ll cnt){
    while(x<N){
        if(v>tr[x].v){
            tr[x]={v,cnt%MOD};
        }else if(v==tr[x].v){
            (tr[x].cnt+=cnt)%=MOD;
        }
        x+=x&-x;
    }
}

pll fw_query(ll x){
    ll resval=-INF;
    ll rescnt=0;
    while(x>0){
        if(tr[x].v>resval){
            tie(resval,rescnt)={tr[x].v,tr[x].cnt};
        }else if(tr[x].v==resval){
            (rescnt+=tr[x].cnt)%=MOD;
        }
        x-=x&-x;
    }
    return {resval,rescnt};
}

void fw_clear(ll x){
    while(x<N){
        tr[x]={-INF,0};
        x+=x&-x;
    }
}

void merge(ll l,ll m,ll r){
    for(ll i=l;i<=r;i++){
        tmp2[i]=tmp1[i];
    }
    sort(tmp2+l,tmp2+m+1,[](const auto& u,const auto& v){
        return u.c^v.c?u.c<v.c:u.i<v.i;
    });
    sort(tmp2+m+1,tmp2+r+1,[](const auto& u,const auto& v){
        return u.c^v.c?u.c<v.c:u.i<v.i;
    });
    ll i,j;
    for(i=l,j=m+1;j<=r;j++){
        while(i<=m&&tmp2[i].c<=tmp2[j].c){
            if(tmp2[i].left){
                fw_update(tmp2[i].d,dp[tmp2[i].i],cnt[tmp2[i].i]);
            }
            i++;
        }
        if(!tmp2[j].left){
            auto [val,count]=fw_query(tmp2[j].d);
            ll id=tmp2[j].i;
            if(val+tmp2[j].v>dp[id]){
                dp[id]=val+tmp2[j].v;
                cnt[id]=count;
            }else if(val+tmp2[j].v==dp[id]){
                (cnt[id]+=count)%=MOD;
            }
        }
    }
    for(ll k=l;k<i;k++){
        if(tmp2[k].left){
            fw_clear(tmp2[k].d);
        }
    }
}

void cdq2(ll l,ll r){
    if(l==r) return;
    ll m=l+r>>1;
    cdq2(l,m);
    merge(l,m,r);
    cdq2(m+1,r);
}

void cdq1(ll l,ll r){
    if(l==r) return;
    ll m=l+r>>1;
    cdq1(l,m);
    for(ll i=l;i<=r;i++){
        tmp1[i]=A[i];
        tmp1[i].left=i<=m;
    }
    sort(tmp1+l,tmp1+r+1,[](const auto& u,const auto& v){
        return u.b^v.b?u.b<v.b:u.i<v.i;
    });
    cdq2(l,r);
    cdq1(m+1,r);
}

void prepare(){
    for(ll i=1;i<=n;i++){
        disc.insert(A[i].d);
    }
    cnt_d=disc.discretize();
    for(ll i=1;i<=n;i++){
        A[i].d=disc.get_rank(A[i].d);
    }
    sort(A+1,A+n+1,[](const auto& u,const auto& v){
        return u.a^v.a?u.a<v.a:u.b^v.b?u.b<v.b:u.c^v.c?u.c<v.c:u.d^v.d?u.d<v.d:u.v>v.v;
    });
    ll m=1;
    for(ll i=2;i<=n;i++){
        if(A[i].a==A[m].a&&A[i].b==A[m].b&&A[i].c==A[m].c&&A[i].d==A[m].d){
            if(A[i].v>0){
                A[m].v+=A[i].v;
            }
        }else{
            A[++m]=A[i];
        }
    }
    n=m;
    for(ll i=1;i<=n;i++){
        A[i].i=i;
        dp[i]=A[i].v;
        cnt[i]=1;
    }
    for(ll i=1;i<=cnt_d;i++){
        tr[i]={-INF,0};
    }
}

void solve(){
    ll m;
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        ll a,b,c,d,v;
        cin>>a>>b>>c>>d>>v;
        A[i]={a,b,c,d,v};
    }
    prepare();
    cdq1(1,n);
    ll best=*max_element(dp+1,dp+n+1);
    ll ways=0;
    for(ll i=1;i<=n;i++){
        if(dp[i]==best){
            (ways+=cnt[i])%=MOD;
        }
    }
    cout<<best<<endl;
    cout<<ways<<endl;
}

void clear(){}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
        clear();
    }
    return 0;
}