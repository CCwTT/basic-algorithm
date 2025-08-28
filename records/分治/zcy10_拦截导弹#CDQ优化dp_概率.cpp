//https://www.luogu.com.cn/problem/P2487
//@@@ 
//dp optimized by cdq
//求概率统统转化成求总量和总量!
//cdq分治:先考虑有哪些维度,然后考虑可以先给那个维度排序
//cnt用ld,因为cnt会很大!而且题干有相关说明
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

const ll N=5e4+5;
ll n;
ll h[N],v[N];

struct Node{
    ll i,h,v;
};

Node A[N];

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

struct trNode{
    ll v;
    ld cnt;
};

trNode tr[N];

ll len1[N],len2[N];
ld cnt1[N],cnt2[N];

void fw_update(ll x,ll v,ld cnt){
    while(x<N){
        if(v>tr[x].v){
            tr[x].v=v;
            tr[x].cnt=cnt;
        }else if(tr[x].v==v){
            tr[x].cnt+=cnt;
        }
        x+=x&-x;
    }
}

pair<ll,ld> fw_query(ll x){
    ll resv=0;
    ld rescnt=0;
    while(x>0){
        if(tr[x].v>resv){
            resv=tr[x].v;
            rescnt=tr[x].cnt;
        }else if(tr[x].v==resv){
            rescnt+=tr[x].cnt;
        }
        x&=x-1;
    }
    return {resv,rescnt};
}

void fw_clear(ll x){
    while(x<N){
        tr[x]={0,0};
        x+=x&-x;
    }
}

void merge1(ll l,ll m,ll r){
    for(ll i=l;i<=r;i++){
        A[i]={i,h[i],v[i]};
    }
    sort(A+l,A+m+1,[&](const auto& u,const auto& v){
        return u.h>v.h;
    });
    sort(A+m+1,A+r+1,[&](const auto& u,const auto& v){
        return u.h>v.h;
    });
    ll i,j;
    for(i=l,j=m+1;j<=r;j++){
        while(i<=m&&A[i].h>=A[j].h){
            fw_update(cnt_d-A[i].v+1,len1[A[i].i],cnt1[A[i].i]); //树状数组操作后缀
            i++;
        }
        auto [val,cnt]=fw_query(cnt_d-A[j].v+1);
        if(val+1>len1[A[j].i]){
            len1[A[j].i]=val+1;
            cnt1[A[j].i]=cnt;
        }else if(val+1==len1[A[j].i]){
            cnt1[A[j].i]+=cnt;
        }
    }
    for(ll k=l;k<i;k++){
        fw_clear(cnt_d-A[k].v+1);
    }
}

void cdq1(ll l,ll r){
    if(l==r) return;
    ll m=l+r>>1;
    cdq1(l,m);
    merge1(l,m,r);
    cdq1(m+1,r);
}

void merge2(ll l,ll m,ll r){
    for(ll i=l;i<=r;i++){
        A[i]={i,h[i],v[i]};
    }
    sort(A+l,A+m+1,[&](const auto& u,const auto& v){
        return u.h<v.h;
    });
    sort(A+m+1,A+r+1,[&](const auto& u,const auto& v){
        return u.h<v.h;
    });
    ll i,j;
    for(i=l,j=m+1;j<=r;j++){
        while(i<=m&&A[i].h<=A[j].h){
            fw_update(A[i].v,len2[A[i].i],cnt2[A[i].i]);
            i++;
        }
        auto [val,cnt]=fw_query(A[j].v);
        if(val+1>len2[A[j].i]){
            len2[A[j].i]=val+1;
            cnt2[A[j].i]=cnt;
        }else if(val+1==len2[A[j].i]){
            cnt2[A[j].i]+=cnt;
        }
    }
    for(ll k=l;k<i;k++){
        fw_clear(A[k].v);
    }
}

void cdq2(ll l,ll r){
    if(l==r) return;
    ll m=l+r>>1;
    cdq2(l,m);
    merge2(l,m,r);
    cdq2(m+1,r);
}

void prepare(){
    for(ll i=1;i<=n;i++){
        disc.insert(v[i]);
    }
    cnt_d=disc.discretize();
    for(ll i=1;i<=n;i++){
        v[i]=disc.get_rank(v[i]);
    }
    for(ll i=1;i<=n;i++){
        len1[i]=len2[i]=1;
        cnt1[i]=cnt2[i]=1.0;
    }
}

void compute(){
    cdq1(1,n);
    for(ll i=1,j=n;i<j;i++,j--){
        swap(h[i],h[j]);
        swap(v[i],v[j]);
    }
    cdq2(1,n);
    for(ll i=1,j=n;i<j;i++,j--){
        swap(len2[i],len2[j]);
        swap(cnt2[i],cnt2[j]);
    }
}

void solve(){
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>h[i]>>v[i];
    }
    prepare();
    compute();
    ll len=*max_element(len1+1,len1+n+1);
    double cnt=0.0;
    for(ll i=1;i<=n;i++){
        if(len1[i]==len){
            cnt+=cnt1[i];
        }
    }
    cout<<len<<endl;
    for(ll i=1;i<=n;i++){
        if(len1[i]+len2[i]-1<len){
            cout<<"0 ";
        }else{
            cout<<fixed<<setprecision(5)<<cnt1[i]*cnt2[i]/cnt<<" ";
        }
    }
    cout<<endl;
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