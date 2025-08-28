//https://www.lanqiao.cn/problems/1025/learning/
//@@@
//proof of greedy algorithm
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node{
    ll s,a,e;
    bool operator<(const Node&x)const{
        return(s+a+e)<(x.s+x.a+x.e);
    }
};

signed main(){
    ll n,ans=0;
    cin>>n; 
    vector<Node> vec;
    for(ll i=1;i<=n;i++){
        ll s,a,e;
        cin>>s>>a>>e;
        vec.push_back(Node{s,a,e}); 
    }
    sort(vec.begin(),vec.end());
    for(ll i=0;i<n;i++){
        ll s=vec[i].s,a=vec[i].a,e=vec[i].e;
        ans+=(n-i)*(s+a)+(n-i-1)*e;
    }
    cout<<ans<<endl;
    return 0;
}