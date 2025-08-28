//https://loj.ac/p/6285
//@@@
//block algorithm
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class discretizer{
public:
    vector<ll> disc;
    discretizer(){
        disc.push_back(LLONG_MIN);
    }

    void insert(ll x){
        disc.push_back(x);
    }

    void discretize(){
        sort(disc.begin(),disc.end());
        disc.erase(unique(disc.begin(),disc.end()),disc.end());
    }

    ll query(ll x){
        return lower_bound(disc.begin(),disc.end(),x)-disc.begin();
    }
};
discretizer disc;

const ll MAXN=1e5+5;
const ll MAXB=2005;
ll bel[MAXN],n,a[MAXN],tot,len,mode[MAXB][MAXB],cnt[MAXN],l,r;
vector<ll> pos[MAXN];

ll lend(ll X){
    return (X-1)*len+1;
}

ll rend(ll X){
    return min(n,X*len);
}

inline ll get(ll l,ll r,ll x) {
	return upper_bound(pos[x].begin(),pos[x].end(),r)-lower_bound(pos[x].begin(),pos[x].end(),l);
} 

void init(){
    for(ll i=1;i<=n;i++){
        disc.insert(a[i]);
    }
    disc.discretize();
    for(ll i=1;i<=n;i++){
        a[i]=disc.query(a[i]);
        pos[a[i]].push_back(i);
    }
    for(ll b=1;b<=bel[n];b++){
        ll res=LLONG_MAX/2;
        ll mode_cnt=0;
        memset(cnt,0,sizeof(ll)*(n+1));
        for(ll i=lend(b);i<=n;i++){
            ll x=a[i];
            cnt[x]++;
            if(cnt[x]>mode_cnt||cnt[x]==mode_cnt&&x<res){
                mode_cnt=cnt[x];
                res=x;
            }
            mode[b][bel[i]]=res;
        }
    }
}

void solve(){
    cin>>n;
    len=max(1ll,(ll)sqrt(n)/2);
	for(ll i=1;i<=n;i++) {
		cin>>a[i];
        bel[i]=(i-1)/len+1;
	}
    init();
	for(ll i=1;i<=n;i++) {
		cin>>l>>r;
        ll L=bel[l]!=bel[l-1]?bel[l]:bel[l]+1;
        ll R=bel[r]!=bel[r+1]?bel[r]:bel[r]-1;
        if(bel[l]==bel[r]){
            ll ans=LLONG_MAX/2;
            ll mode_cnt=0;
            for(ll i=l;i<=r;i++){
                ll cur_cnt=get(l,r,a[i]);
	    	    if(cur_cnt>mode_cnt||mode_cnt==cur_cnt&&a[i]<ans){
                    mode_cnt=cur_cnt;
                    ans=a[i];
                }
            }
            cout<<disc.disc[ans]<<endl;
        }else{
            ll ans=mode[L][R];
            ll mode_cnt=get(l,r,ans);
            for(ll i=l;i<lend(L);i++){
                ll cur_cnt=get(l,r,a[i]);
	    	    if(cur_cnt>mode_cnt||mode_cnt==cur_cnt&&a[i]<ans){
                    mode_cnt=cur_cnt;
                    ans=a[i];
                }
            }
            for(ll i=r;i>rend(R);i--){
                ll cur_cnt=get(l,r,a[i]);
	    	    if(cur_cnt>mode_cnt||mode_cnt==cur_cnt&&a[i]<ans){
                    mode_cnt=cur_cnt;
                    ans=a[i];
                }
            }
            cout<<disc.disc[ans]<<endl;
        }
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