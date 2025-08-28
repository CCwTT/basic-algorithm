//https://www.lanqiao.cn/problems/20165/learning/
//@@@
//3-dim dp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod=998244353;
void Log(vector<ll>& a){
	ll n=a.size();
	for(ll i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
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
    
    vector<vector<vector<ll>>> f(3,vector<vector<ll>>(m+1,vector<ll>(n+1,0))); 
    f[0][0][0]=1;
    
    for(ll k=0;k<=2;k++){ 
        for(ll i=0;i<m;i++){
            for(ll j=0;j<n;j++){
                if(f[k][i][j]==0) continue;
                for(char c='a';c<='z';c++){
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
                        if(k+1<=2){
                            f[k+1][i+1][next[n]]=(f[k+1][i+1][next[n]]+f[k][i][j])%mod;
                        }
                    }
                    else{
                        f[k][i+1][nj]=(f[k][i+1][nj]+f[k][i][j])%mod;
                    }
                }
            }
        }
    }
    ll ans=0;
    for(ll j=0;j<n;j++) 
        ans=(ans+f[2][m][j])%mod; 
    cout<<ans<<endl;
}

signed main(){
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}