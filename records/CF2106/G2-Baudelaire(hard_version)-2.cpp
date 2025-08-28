#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<ll>> g,nextcd;
vector<ll> tot,val;
vector<bool> vis;
ll n,CD=-1;

ll ask(vector<ll> a){
    cout<<"? 1 "<<a.size()<<" ";
    for(auto x:a) cout<<x<<" ";
    cout<<endl;
    ll res; 
	cin>>res;
    return res;
}

void toggle(ll x){
    cout<<"? 2 "<<x<<endl;
}

void answer(vector<ll> ans){
    cout<<"! ";
    for(ll i=1;i<=n;i++) cout<<ans[i]<<" ";
    cout<<endl;
}

void get_tot(ll x,ll fa){
    tot[x]=1;
    if(vis[x]) return;
    for(auto y:g[x]) if(y!=fa){
        get_tot(y,x);
        tot[x]+=tot[y];
    }
}

//Such way to find the centroid can only find one of all centroids
ll find_centroid(ll x,ll fa,ll sz){
    for(auto y:g[x]) if(y!=fa&&!vis[y]){
        if(tot[y]*2>=sz) return find_centroid(y,x,sz);
    }
    return x;
}

//params:centroid,prev centroid
//O(nlogn)
void build(ll x,ll prev){
    nextcd[prev].push_back(x);
    vis[x]=true;
    for(auto y:g[x]){
        if(vis[y]) continue;
        get_tot(y,x);
        ll centroid=find_centroid(y,x,tot[y]);
        build(centroid,x);
    }
}

ll root_at_branch(vector<ll> a,ll centroid){
    ll n=a.size();
    ll l=0,r=n-1;
    ll ans=-1;
    while(l<=r){
        ll m=l+r>>1;
        
        auto check=[&]()->bool{
            vector<ll> qr;
            for(ll j=l;j<=m;j++) qr.push_back(a[j]);
            ll bef=ask(qr);
            toggle(centroid);
            ll aft=ask(qr);
            if(llabs(aft-bef)==2*qr.size()) return false;
            return true;
        };

        if(check()){
            ans=m;
            r=m-1;
        }else{
            l=m+1;
        }
    }
    return ans;
}

ll find_root(ll x,ll fa){
    if(nextcd[x].empty()) return x;
    vector<ll> branches;
    for(auto y:nextcd[x]) if(y!=fa){
        branches.push_back(y);
    }
    ll branchid=root_at_branch(branches,x);
    if(branchid==-1) return x;
    return find_root(branches[branchid],x);
}

void find_vals(ll x,ll fa,ll S){
    val[x]-=S;
    for(auto y:g[x]) if(y!=fa){
        find_vals(y,x,S+val[x]);
    }
}

void solve(){
    cin>>n;
    nextcd.assign(n+1,{});
    g.assign(n+1,{});
    for(ll i=1;i<n;i++){
        ll u,v; 
		cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vis.assign(n+1,false);
    tot.assign(n+1,0);
    get_tot(1,0);
    CD=find_centroid(1,n,0);
    build(CD,0);
    ll root=find_root(CD,0);
    val.resize(n+1);
    for(ll i=1;i<=n;i++) val[i]=ask({i});
    find_vals(root,0,0);
    answer(val);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--) solve();
    return 0;
}
