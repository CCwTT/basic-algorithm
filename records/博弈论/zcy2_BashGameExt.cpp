//https://www.luogu.com.cn/problem/P4018
//@@@
//game theory
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;

/* 具体讲一讲这道题 巴什博奕扩展
题意:一堆石子有n个石子，October(先手)和Roy两人轮流取石子，每次可以取p^k个石子，其中p是任意质数，k是任意自然数，取走最后一个石子的人获胜，问谁会获胜
思路:1,2,3,4,5可以一次取到，6及其倍数不能一次取到。所以先手策略如下：
如果当前石子数不是6的倍数，则取1或2或3或4或5个石子使得剩下石子个数是6的倍数。接下来后手只能取非6的倍数个石子，先手再取1或2或3或4或5个石子使得剩下石子个数是6的倍数。这样先手必胜。
如果当前石子数是6的倍数，则后手必胜。
*/

void solve(){
    ll n;
    cin>>n;
    cout<<(n%6?"October wins!":"Roy wins!")<<endl;
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