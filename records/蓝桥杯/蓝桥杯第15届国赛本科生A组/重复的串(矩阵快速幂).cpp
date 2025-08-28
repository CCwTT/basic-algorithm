//https://www.lanqiao.cn/problems/20165/learning/
//@@@
//matrix quick power
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod=998244353;

struct Matrix{
    vector<vector<ll>> mat;
    ll m,n;
    Matrix(ll _m,ll _n):m(_m),n(_n),mat(_m,vector<ll>(_n)){}
    Matrix operator*(const Matrix &o){
        Matrix R(m,o.n);
        for(ll i=0;i<m;i++){
            for(ll j=0;j<o.n;j++){
                for(ll k=0;k<n;k++){
                    R.mat[i][j]=(R.mat[i][j]+mat[i][k]*o.mat[k][j])%mod;
                }
            }
        }
        return R;
    }
};

Matrix qpow(Matrix x,ll m){
    Matrix res(x.m,x.n);
    for(ll i=0;i<x.m;i++) res.mat[i][i]=1;
    while(m){
        if(m&1) res=res*x;
        x=x*x;
        m>>=1;
    }
    return res;
}

vector<ll> get_next(string s){ 
	ll n=s.size();
	vector<ll> next(n+1);
	next[0]=-1;
	next[1]=0;
	ll i=2,j=0;
	while(i<=n){
		if(s[i-1]==s[j]){
			next[i++]=++j;
		}else if(j){
			j=next[j];
		}else{
			next[i++]=0;
		}
	}
	return next;
} 

void solve(){
    string t;
    ll m;
    cin>>t>>m;
    ll n=t.size();
    auto next=get_next(t);
    Matrix I(4*n,4*n);
    for(ll j=0;j<n;j++){
        for(ll c='a';c<='z';c++){
            ll nj;
            if(c==t[j]){
                nj=j+1;
            }
            ll jj=j;
            while(jj&&c!=t[jj]){
                jj=next[jj];
            }
            if(c==t[jj]) nj=jj+1;
            else nj=0;
            if(nj==n){
                nj=next[nj]+n;
            }
            I.mat[j][nj]++;
            I.mat[j+n][nj+n]++;
            I.mat[j+2*n][nj+2*n]++;
        }
    }
    auto R=qpow(I,m);
    ll ans=0;
    for(ll i=2*n;i<3*n;i++){
        ans=(ans+R.mat[0][i])%mod;
    }
    cout<<ans;
}

signed main(){
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}

/*
状态定义与矩阵结构
我们将整个状态空间分为三个子空间，每个子空间对应匹配到t的次数k（0 次、1 次、2 次）。每个子空间包含m个状态，表示当前匹配到t的第i个字符（i ∈ [0, m)）。因此，总状态数为3m。
我们可以定义状态向量S(n)为一个长度为3m的列向量：
S(n) = [s₀(n), s₁(n), ..., sₘ₋₁(n), sₘ(n), sₘ₊₁(n), ..., s₂ₘ₋₁(n), s₂ₘ(n), s₂ₘ₊₁(n), ..., s₃ₘ₋₁(n)]ᵀ
其中：
s₀(n) ~ sₘ₋₁(n) 表示匹配 0 次t的状态
sₘ(n) ~ s₂ₘ₋₁(n) 表示匹配 1 次t的状态
s₂ₘ(n) ~ s₃ₘ₋₁(n) 表示匹配 2 次t的状态
状态转移矩阵
状态转移矩阵B是一个3m × 3m的方阵，其中每个元素B[i][j]表示从状态i转移到状态j的方案数。根据代码中的转移逻辑，矩阵B可以分块表示为：
B = [B₀₀, B₀₁, B₀₂]
    [B₁₀, B₁₁, B₁₂]
    [B₂₀, B₂₁, B₂₂]
其中：
每个子矩阵Bᵢⱼ是m × m的矩阵
B₀₀、B₁₁、B₂₂表示组内转移
B₀₁、B₁₂表示组间转移（匹配次数增加）
B₀₂、B₁₀、B₂₀、B₂₁均为零矩阵（无法从高匹配次数转移到低匹配次数或越级匹配）
矩阵递推关系
状态向量的递推关系可以表示为：
S(n+1) = B · S(n)
通过递推可以得到：
S(n) = Bⁿ · S(0)
其中，初始状态向量S(0)为：S(0) = [1, 0, 0, ..., 0]ᵀ
*/