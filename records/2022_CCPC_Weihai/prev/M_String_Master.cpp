#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 2e6+10;
LL a[maxn], s[maxn];
LL aa[10][10];
vector<LL> g[10];
pair<LL,LL> b[1000];
int main(){
    LL x, q;  cin>>x>>q;
    LL y = (1<<20);
    for(LL i = 1; i <= y; i++){
        if(__gcd(i*x^x, x) == 1)a[i] = 1;
        s[i] = s[i-1]+a[i];
    }
    vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    map<string,int> mp;
    mp["abc"]=1;
    mp["qqq"]++;
    mp["qwer"]=1333;
    aa[0][0]=99;
    aa[0][1]=88;
    aa[1][0]=77;
    aa[1][1]=66;
    vector<vector<int>> vv;
    vv.push_back({0,1,2});
    vv.push_back({3,4,5});
    vv.push_back({6,7,8});
    g[0].push_back(1);
    g[2].push_back(3);
    g[2].push_back(4);
    b[2]={1,2};
    b[3]={3,4};
    while(q--){
        LL l, r;  cin>>l>>r;  l--;
        LL res1 = s[l%y]+(l/y)*s[y];
        LL res2 = s[r%y]+(r/y)*s[y];
        cout<<res2-res1<<"\n";
    }
    return 0;
}
