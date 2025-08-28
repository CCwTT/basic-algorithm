//https://acm.hdu.edu.cn/contest/problem?cid=1173&pid=1012
//@@@
//half method
//极限卡内存时不要用vector,循环里面套lamda表达式不会影响时间和内存
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

const int N=51;
ll a[N];
int n;

// vector<ll> vec1;
// vector<ll> vec2;
ll vec[(ll)2e5],vi=0;
void bf(int l,int r){
    vi=0;
    if(r<l) return;
    function<void(int,bool,ll)> dfs=[&](int p,bool choose,ll XOR)->void{
        if(p==r+1){
            vec[vi++]=XOR;
            return;
        }
        dfs(p+1,false,XOR);
        if(choose==false) dfs(p+1,true,XOR^a[p]);
    };
    dfs(l,false,0);
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int mid=(1+n)/2;
    bf(1,mid-1);
    sort(vec,vec+vi);
    ll ans=0;

    auto find_ans=[&](ll x)->ll{
        int l=0,r=vi-1;
        int d=62;
        while(l<r){

            auto find_mid=[&](int d,int x,int y)->int{
                int l=x,r=y;
                int res=x-1;
                while(l<=r){
                    int m=l+r>>1;
                    if(vec[m]>>d&1){
                        r=m-1;
                    }else{
                        res=m;
                        l=m+1;
                    }
                }
                return res;
            };

            if((vec[l]>>d&1)!=(vec[r]>>d&1)){
                int mid1=find_mid(d,l,r);
                int mid2=mid1+1;
                if(x>>d&1){
                    r=mid1;
                }else{
                    l=mid2;
                }
            }
            d--;
        }
        return vec[l]^x;
    };

    auto f=[&](ll l,ll r,ll s)->void{
        if(l>r) return;
        function<void(int,bool,ll)> dfs=[&](int p,bool choose,ll XOR)->void{
            if(p==r+1){
                ans=max(ans,find_ans(XOR^s));
                return;
            }
            dfs(p+1,false,XOR);
            if(choose==false) dfs(p+1,true,XOR^a[p]);
        };
        dfs(l,false,0);
    };
    f(mid+1,n,0);

    bf(1,mid-2);
    sort(vec,vec+vi);
    f(mid+2,n,a[mid]);
    cout<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
       solve(); 
    } 
    return 0;
}

