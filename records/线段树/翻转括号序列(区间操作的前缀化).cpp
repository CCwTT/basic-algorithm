//https://www.lanqiao.cn/problems/1589/learning/
//@@@
//seg(flip,binary),prefixization of range operation
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF=LLONG_MAX/2;

class segment_tree{
public:
    ll n;
    vector<ll>& a;
    vector<ll> s;
    vector<ll> mn,mx,sum;  //sum is in respect to a,mn/mx are in respect to s
    vector<ll> add;
	vector<bool> flip;

    segment_tree(vector<ll>& a):a(a){
        n=a.size()-1;
        s.resize(n+1,0);
        mn.resize(n<<2);
        mx.resize(n<<2);
        sum.resize(n<<2);
        flip.resize(n<<2,false);
        add.resize(n<<2,0);

        for(ll i=1;i<=n;i++){
            s[i]=s[i-1]+a[i];
        }
        build(1,1,n);
    }

    void apply1(ll p,ll l,ll r){
        swap(mx[p],mn[p]);
		sum[p]*=-1;
        add[p]*=-1,flip[p]=!flip[p];
		mx[p]*=-1,mn[p]*=-1;
    }

	void apply2(ll p,ll l,ll r,ll v){
        add[p]+=v;
		mx[p]+=v,mn[p]+=v;
    }

    void up(ll p){
        mx[p]=max(mx[p<<1],mx[p<<1|1]);
        mn[p]=min(mn[p<<1],mn[p<<1|1]);
        sum[p]=sum[p<<1]+sum[p<<1|1];
    }

    void down(ll p,ll l,ll r){
        ll m=l+r>>1;
        if(flip[p]){
            apply1(p<<1,l,m);
            apply1(p<<1|1,m+1,r);
            flip[p]=false;
        }
        if(add[p]){
            apply2(p<<1,l,m,add[p]);
            apply2(p<<1|1,m+1,r,add[p]);
            add[p]=0;
        }
    }

    void build(ll p,ll l,ll r){
        flip[p]=false;
        add[p]=0;
        if(l==r){
            sum[p]=a[l];
            mn[p]=mx[p]=s[l];
            return;
        }
        ll m=l+r>>1;
        build(p<<1,l,m);
        build(p<<1|1,m+1,r);
        up(p);
    }

    void update1(ll p,ll l,ll r,ll x,ll y){
        if(x<=l&&r<=y){
            apply1(p,l,r);
            return;
        }
        down(p,l,r);
        ll m=l+r>>1;
        if(x<=m) update1(p<<1,l,m,x,y);
        if(y>m) update1(p<<1|1,m+1,r,x,y);
        up(p);
    }

    void update2(ll p,ll l,ll r,ll x,ll y,ll v){
        if(x<=l&&r<=y){
            apply2(p,l,r,v);
            return;
        }
        down(p,l,r);
        ll m=l+r>>1;
        if(x<=m) update2(p<<1,l,m,x,y,v);
        if(y>m) update2(p<<1|1,m+1,r,x,y,v);
        up(p);
    }

    ll query_sum(ll p,ll l,ll r,ll x,ll y){
        if(x<=l&&r<=y){
            return sum[p];
        }
        down(p,l,r);
        ll m=l+r>>1;
        ll res=0;
        if(x<=m) res+=query_sum(p<<1,l,m,x,y);
        if(y>m) res+=query_sum(p<<1|1,m+1,r,x,y);
        return res;
    }

    ll query_min(ll p,ll l,ll r,ll x,ll y){
        if(x<=l&&r<=y){
            return mn[p];
        }
        down(p,l,r);
        ll m=l+r>>1;
        ll res=INF;
        if(x<=m) res=min(res,query_min(p<<1,l,m,x,y));
        if(y>m) res=min(res,query_min(p<<1|1,m+1,r,x,y));
        return res;
    }

    ll query_binary(ll p,ll l,ll r,ll x,ll y,ll v){
        if(l==r) return l;
        down(p,l,r);
        ll m=l+r>>1;
        if(y>m&&mn[p<<1|1]<=v) return query_binary(p<<1|1,m+1,r,x,y,v);
        if(x<=m&&mn[p<<1]<=v) return query_binary(p<<1,l,m,x,y,v);
        return 0;
    }

    void user_flip(ll x,ll y){
        ll add1=2*query_sum(1,1,n,1,y)*-1;
        update1(1,1,n,1,y);
        if(y+1<=n) update2(1,1,n,y+1,n,add1);
        if(x-1>=1){
            ll add2=2*query_sum(1,1,n,1,x-1)*-1;
            update1(1,1,n,1,x-1);
            update2(1,1,n,x,n,add2);
        }
	}
};

void solve(){
    ll n,m;
    string s;
    cin>>n>>m>>s;
    s=" "+s;

    vector<ll> a(n+1);
    for(ll i=1;i<=n;i++){
        if(s[i]=='('){
            a[i]=1;
        }else{
            a[i]=-1;
        }
    }

    segment_tree seg(a);

    while(m--){
        ll op,x,y;
        cin>>op;
        if(op==1){
            cin>>x>>y;
            seg.user_flip(x,y);
        }else{
            cin>>x;
            if(seg.query_sum(1,1,n,x,x)==-1){
                cout<<0<<'\n';
                continue;
            }
            ll left=x,right=n,res=0;
            ll pre=(x==1)?0:seg.query_min(1,1,n,x-1,x-1);
            while(left<=right){
                ll mid=(left+right)>>1;
                if(seg.query_min(1,1,n,x,mid)>=pre){
                    res=mid;
                    left=mid+1;
                }else{
                    right=mid-1;
                }
            }
            if(res<n){
                cout<<res<<'\n';
            }else{
                ll ans=seg.query_binary(1,1,n,x,n,pre);
                cout<<(ans!=x?ans:0)<<'\n';
            }
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}

