//https://www.lanqiao.cn/problems/2176/learning/
//@@@
//mindwork
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll helper(ll o_ow,ll wo_o,ll o_o,ll wo_ow,ll o_,ll _o,ll wo_,ll _ow,ll w){
    ll c1=0,c2=0,c3=0,c4=0;
    ll ans=0;
    //two cycle
    if(o_ow>0) ++c1;
    ans+=o_ow;
    o_ow=0;
    if(wo_o>0) ++c2;
    ans+=wo_o;
    wo_o=0;
    //split first
    if(o_o>0||wo_ow>0) c1=c2=0;
    //re-cycle
    if(o_o>0&&wo_ow>0){
        c3=1;
        ll z=min(o_o,wo_ow);
        ans+=z<<1;
        o_o-=z;
        wo_ow-=z;
        if(o_o>0||wo_ow>0) c3=0;
    }

    if(o_o>0){
        if(o_o<=w) c4=1;//assert w>=1
        //if(c1||c2||c3)c4=0;//unite llo,but won't exist
    }

    if(_ow>0||o_>0) c1=0;
    if(_o>0||wo_>0) c2=0;
    if(_ow>0||o_>0||_o>0||wo_>0)
        c3=c4=0;//o_o+w(w>=1) can connect to any solo string,so c4=0 here

    if(o_o>0) _o+=o_o;
    o_+=o_o;
    if(wo_ow>0) _ow+=wo_ow;
    wo_+=wo_ow;
    o_o=wo_ow=0;
    ll z=min(_o,wo_);
    _o-=z;
    wo_-=z;
    ans+=z;
    z=min(_ow,o_);
    _ow-=z;
    o_-=z;
    ans+=z;
    z=min(_o,o_);
    z=min(z,w);
    ans+=z;
    return ans-c1-c2-c3-c4;
}

void solve(){
    ll o_o=0,o_ow=0,o_=0,wo_o=0,wo_ow=0,wo_=0,_o=0,_ow=0,w=0;
    ll n;
    string s;
    cin>>n;
    ll base_ans=0;
    ll len_tot=0;
    for(ll i=1;i<=n;++i){
        cin>>s;
        ll m=s.length();
        s=" "+s;
        len_tot+=m;
        for(ll j=1;j<=m-2;++j)
            if(s[j]=='o'&&s[j+1]=='w'&&s[j+2]=='o')
                ++base_ans;
        if(m==1){
            if(s[1]=='w')++w;
            if(s[1]=='o')++o_o;
        }else{
            if(s[1]=='o'){
                if(s[m]=='o')++o_o;
                else if(s[m]=='w'&&s[m-1]=='o')++o_ow;
                else ++o_;
            }else if(s[1]=='w'&&s[2]=='o'){
                if(s[m]=='o')++wo_o;
                else if(s[m]=='w'&&s[m-1]=='o')++wo_ow;
                else ++wo_;
            }else{
                if(s[m]=='o')++_o;
                else if(s[m]=='w'&&s[m-1]=='o')++_ow;
            }
        }
        ll r=helper(o_ow,wo_o,o_o,wo_ow,o_,_o,wo_,_ow,w);
        cout<<base_ans+r<<endl;
    }
}

signed main(){
    ll T=1;
    while(T--){
        solve();
    }
    return 0;
}