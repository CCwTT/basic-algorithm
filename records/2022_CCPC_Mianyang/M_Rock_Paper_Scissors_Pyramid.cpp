#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

//首先，我们规定生成上一层的顺序是从左到右两两生成一个字母。
//又总是可以仍为，字符串左端是一段连续相同字母A，然后出现不同字母B，如果B beats A,则根据我们的规定，上一层一定会出现B，那么将A全部替换为B不影响结果

bool beat(char a,char b){
    if(a==b) return true;
    return (a=='R'&&b=='S')||(a=='S'&&b=='P')||(a=='P'&&b=='R');
}

void solve(){
    string s;
    cin>>s;
    stack<char> stk;
    for(auto c:s){
        while(!stk.empty()&&beat(c,stk.top())){
            stk.pop();
        }
        stk.push(c);
    }
    while(stk.size()>1){
        stk.pop();
    }
    cout<<stk.top()<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}