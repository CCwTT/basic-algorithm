//https://leetcode.cn/problems/number-of-music-playlists/description/
//@@@
//inclusion-exclusion principle
const int MX=100;
const int mod=1e9+7;
int qpow(int x,int n){
    int ret=1;
    while(n){
        if(n&1) ret=1ll*ret*x%mod;
        n>>=1;
        x=1ll*x*x%mod;
    }
    return ret;
}
int fac[MX+1],inv_fac[MX+1];
auto init=[](){
    fac[0]=1;
    for(int i=1;i<=MX;i++){
        fac[i]=1ll*fac[i-1]*i%mod;
    }
    inv_fac[MX]=qpow(fac[MX],mod-2);
    for(int i=MX-1;i>=0;i--){
        inv_fac[i]=1ll*inv_fac[i+1]*(i+1)%mod;
    }
    return 0;
}();

int A(int n,int m){
    return 1ll*fac[n]*inv_fac[n-m]%mod;
}

int C(int n,int m){
    return 1ll*fac[n]*inv_fac[m]%mod*inv_fac[n-m]%mod;
}

int f(int n,int l,int k){
    if(n<=k) return 0;
    return 1ll*A(n,k+1)*qpow(n-k,l-(k+1))%mod;
}

class Solution {
public:
    int numMusicPlaylists(int n, int goal, int k) {
        int sign=1;
        int ans=0;
        for(int i=0;i<=n;i++,sign=-sign){
            ans=(ans+1ll*sign*C(n,i)*f(n-i,goal,k)%mod+mod)%mod;
        }
        return ans;
    }
};

