//https://acm.hdu.edu.cn/showproblem.php?pid=4348
//@@@
//persistent segment tree(permanent lazy tagging)
//全用ll超内存,全用int溢出,wcnm
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class persistent_segment_tree{
public:
    int n;
    int cnt=0;
    vector<int> lc,rc;
    vector<ll> sum,add_tag;
    persistent_segment_tree(int sz,int SZ):n(sz-1),sum(SZ),add_tag(SZ),lc(SZ),rc(SZ){}

    int clone(int pp){
        int p=++cnt;
        sum[p]=sum[pp];
        add_tag[p]=add_tag[pp];
        lc[p]=lc[pp];
        rc[p]=rc[pp];
        return p;
    }

    void up(int p){
        sum[p]=sum[lc[p]]+sum[rc[p]];
    }

    int build(int l,int r,vector<ll>& a){
        int p=++cnt;
        if(l==r){
            sum[p]=a[l];
            add_tag[p]=0;
        }else{
            int m=l+r>>1;
            lc[p]=build(l,m,a);
            rc[p]=build(m+1,r,a);
            up(p);
        }
        return p;
    }

    int update(int p,int l,int r,int x,int y,ll v){
        p=clone(p);
        sum[p]+=v*(min(r,y)-max(l,x)+1);
        if(x<=l&&r<=y){
            add_tag[p]+=v;
        }else{
            int m=l+r>>1;
            if(x<=m) lc[p]=update(lc[p],l,m,x,y,v);
            if(y>m) rc[p]=update(rc[p],m+1,r,x,y,v); 
        }
        return p;
    }

    ll query(int p,int l,int r,int x,int y,int acc=0){
        if(x<=l&&r<=y){
            return sum[p]+acc*(r-l+1);
        }
        int m=l+r>>1;
        ll res=0;
        if(x<=m) res+=query(lc[p],l,m,x,y,acc+add_tag[p]);
        if(y>m) res+=query(rc[p],m+1,r,x,y,acc+add_tag[p]);
        return res;
    }

};

int n,m;
void solve(){
    vector<ll> a(n+1);
    persistent_segment_tree seg(n+1,2500000);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    vector<int> root(n+1);
    root[0]=seg.build(1,n,a);
    int t=0;
    for(int i=1;i<=m;i++){
        char op;
        cin>>op;
        if(op=='C'){
            int x,y,v;
            cin>>x>>y>>v;
            root[t+1]=seg.update(root[t],1,n,x,y,v);
            t++;
        }else if(op=='Q'){
            int x,y;
            cin>>x>>y;
            cout<<seg.query(root[t],1,n,x,y)<<endl;
        }else if(op=='H'){
            int x,y,z;
            cin>>x>>y>>z;
            cout<<seg.query(root[z],1,n,x,y)<<endl;
        }else{
            int x;
            cin>>x;
            t=x;
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T=1;
    while(cin>>n>>m){
        solve();
    }
    return 0;
}

