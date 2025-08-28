//https://www.luogu.com.cn/problem/P4735
//@@@
//persistent trie
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf LLONG_MAX/2
typedef long long ll;

const int MAXN = 600001;
const int MAXT = MAXN * 30;
const int HIGH = 25;
int n, m, XOR;
int root[MAXN];
struct node{
    ll ch[2];
    ll pass;
};
node tr[MAXT];
int cnt = 0;

int insert(int pre,int x) {
   int rt = ++cnt;
   tr[rt]=tr[pre];
   tr[rt].pass++;
   for (int d=HIGH;d>=0;d--){
       ll path=(x>>d)&1;
       pre=tr[pre].ch[path];
       ++cnt;
       tr[cnt]=tr[pre];
       tr[cnt].pass++;
       tr[cnt-1].ch[path]=cnt;
   }
   return rt;
}

int query(int u,int v,int x){
   int res=0;
   for (int d=HIGH;d>=0;d--){
       ll path=(x>>d)&1;
       ll best=path^1;
       if(tr[tr[v].ch[best]].pass>tr[tr[u].ch[best]].pass){
           res+=1<<d;
           u=tr[u].ch[best];
           v=tr[v].ch[best];
       }else{
           u=tr[u].ch[path];
           v=tr[v].ch[path];
       }
   }
   return res;
}

void solve(){
    cin>>n>>m;
    ll XOR=0;
    root[0]=insert(0,XOR);
    for(ll i=1;i<=n;i++){
        ll x;
        cin>>x;
        XOR^=x;
        root[i]=insert(root[i-1],XOR);
    }
    for(ll i=1;i<=m;i++){
        string op;
        ll x,y,z;
        cin>>op;
        if(op=="A"){
            cin>>x;
            XOR^=x;
            n++;
            root[n]=insert(root[n-1],XOR);
        }else{
            cin>>x>>y>>z;
            if(x==1){
                cout<<query(0,root[y-1],XOR^z)<<endl;
            }else{
                cout<<query(root[x-2],root[y-1],XOR^z)<<endl;
            }
        }
    }
}

int main() {
   ios::sync_with_stdio(false);
   cin.tie(0);
   solve();
   return 0;
}