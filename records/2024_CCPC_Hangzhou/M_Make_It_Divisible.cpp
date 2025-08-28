#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

const ll N=2e5+10;
const ll mod=998244353;
ll n,k;
ll a[N];
ll b[N];
ll lc[N];
ll rc[N];
ll stk[N];

void build(){
	ll top=0;
	for(ll i=1;i<=n;i++){
		ll pos=top;
		while(pos>0&&a[stk[pos]]>a[i]){
			pos--;
		}
		if(pos>0){
			rc[stk[pos]]=i;
		}
		if(pos<top){
			lc[i]=stk[pos+1];
		}
		stk[++pos]=i;
		top=pos;
	}
}

bool dfs(ll x,ll l,ll r,ll fa){
    if(l>r) return 1;
    if(fa&&b[x]%b[fa]) return 0;
    return dfs(lc[x],l,x-1,x)&&dfs(rc[x],x+1,r,x);
}

bool check(ll x){
    for(ll i=1;i<=n;i++){
        b[i]=a[i]+x;
    }
    return dfs(stk[1],1,n,0);
}


void solve(){
    cin>>n>>k;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    ll mi=*min_element(a+1,a+n+1);
    ll gd=0;
    for(ll i=1;i<n;i++){
        gd=__gcd(gd,abs(a[i]-a[i+1]));
    }
    if(gd==0){
        cout<<k<<" "<<k*(k+1)/2<<endl;
        return;
    }
    vector<ll> factors;
    for(ll i=1;i*i<=gd;i++){
        if(gd%i==0){
            factors.push_back(i);
            if(i*i!=gd){
                factors.push_back(gd/i);
            }
        }
    }
    vector<ll> S_x;
    for(auto factor:factors){
        ll x=factor-mi;
        if(1<=x&&x<=k){
            S_x.push_back(x);
        }
    }

    for(int i=1;i<=n;i++){
        lc[i]=rc[i]=0;
    }
    build();

    ll cnt=0,sum=0;
    for(auto x:S_x){
        if(check(x)){
            cnt++;
            sum+=x;
        }
    }
    cout<<cnt<<" "<<sum<<endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
