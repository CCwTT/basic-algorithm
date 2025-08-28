#include<bits/stdc++.h>
using namespace std;

const int mod=1e9+7;

//第二类斯特林数 
int s[1001][1001];
auto init=[]{
	s[0][0]=1; 
	for(int i=0;i<1001;i++){
		for(int j=1;j<=i;j++){
			s[i][j]=(s[i-1][j-1]+1LL*j*s[i-1][j])%mod;
		}
	}
	return 0;
}(); 

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	string s="3421567";
	sort(s.begin(),s.end());
	cout<<s;
	return 0;
} 
