//https://www.luogu.com.cn/problem/P5410
//@@@
//z array,e array
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define endl '\n'

void Log(vector<int>& a){
	int n=a.size();
	for(int i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

vector<int> get_z(string s){ //LCP of every suffix of s and s 
	ll n=s.size();
	vector<int> z(n);
	z[0]=n;
	for(int i=1,boxl=1,boxr=1;i<n;i++){  //box:[)
		z[i]=i<boxr?min(boxr-i,z[i-boxl]):0;
		while(i+z[i]<n&&s[i+z[i]]==s[z[i]]){
			z[i]++;
		}
		if(i+z[i]>boxr){
			boxr=i+z[i];
			boxl=i;
		}
	}
	return z;
}

vector<int> get_e(string s,string t){ //LCP of every suffix of s and t
	int m=s.size(),n=t.size();
	auto z=get_z(t);
	vector<int> e(m);
	for(int i=0,boxl=0,boxr=0;i<m;i++){
		e[i]=i<boxr?min(boxr-i,z[i-boxl]):0;
		while(i+e[i]<m&&e[i]<n&&s[i+e[i]]==t[e[i]]){
			e[i]++;
		}
		if(i+e[i]>boxr){
			boxr=i+e[i];
			boxl=i;
		}
	}
	return e;
}

void solve(){
    string s,t;
    cin>>s>>t;
    auto z=get_z(t);
    auto e=get_e(s,t);
    ll ans1=0,ans2=0;
    for(int i=0;i<z.size();i++){
        ans1^=1ll*(i+1)*(z[i]+1);
    }
    for(int i=0;i<e.size();i++){
        ans2^=1ll*(i+1)*(e[i]+1);
    }
    cout<<ans1<<endl<<ans2<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
	int T=1;
    while(T--){
        solve();
    }
    return 0;
}
