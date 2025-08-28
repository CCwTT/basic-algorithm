//https://codeforces.com/contest/1451/problem/E2
//@@@
//interactive
/*
This is an interactive problem.
Ridbit has a hidden array a of n integers which he wants Ashish to guess. Note that n is a power of two. Ashish is allowed to ask three different types of queries. They are of the form
AND i&j: ask for the bitwise AND of elements ai and aj (1≤i,j≤n, i≠j)
OR  i|j: ask for the bitwise OR of elements ai and aj (1≤i,j≤n, i≠j)
XOR i^j: ask for the bitwise XOR of elements ai and aj (1≤i,j≤n, i≠j)
Can you help Ashish guess the elements of the array?
In this version, each element takes a value in the range [0,n−1]
(inclusive) and Ashish can ask no more than n+1 queries.
*/
#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define inf (LLONG_MAX/2)
typedef long long ll;

void solve(){
    ll n;
    cin>>n;
    vector<ll> a(n+1);
    vector<ll> ans(n+1,-1);
    ll mark=-1;
    for(ll i=2;i<=n;i++){
        cout<<"XOR 1 "<<i<<endl;
        cin>>a[i];
        if(a[i]==0){
            mark=i;
        }
    }
    unordered_map<int,int> mp;
    for(ll i=2;i<=n;i++){
        mp[a[i]]++;
    }
    if(~mark){
        cout<<"AND 1 "<<mark<<endl;
        cin>>ans[1];
        for(ll i=2;i<=n;i++){
            ans[i]=ans[1]^a[i];
        }
    }else if(mp.size()<n-1){
        ll val;
        for(auto& [v,c]:mp){
            if(c>1){
                val=v;
                break;
            }
        }
        ll idx1=-1,idx2=-1;
        for(ll i=2;i<=n;i++){
            if(a[i]==val){
                if(idx1==-1){
                    idx1=i;
                }else{
                    idx2=i;
                    break;
                }
            }
        }
        cout<<"AND "<<idx1<<" "<<idx2<<endl;
        cin>>ans[idx1];
        ans[1]=ans[idx1]^a[idx1];
        for(ll i=2;i<=n;i++){
            ans[i]=ans[1]^a[i];
        }
    }else{
        for(ll i=2;i<=n;i++){
            if(a[i]==n-1){
                mark=i;
                break;
            }
        }
        ll p=mark==2?3:2;
        cout<<"AND 1 "<<p<<endl;
        ll resp;
        cin>>resp;
        ans[p]=resp;
        cout<<"AND "<<mark<<" "<<p<<endl;
        cin>>resp;
        ans[p]+=resp;
        ans[1]=ans[p]^a[p];
        for(ll i=2;i<=n;i++){
            ans[i]=ans[1]^a[i];
        }
    }
    cout<<"! ";
    for(ll i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    //cin>>T;
    while(T--){
        solve();
    }
    return 0;
}