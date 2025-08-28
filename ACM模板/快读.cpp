#include<bits/stdc++.h>
using namespace std;

//_getchar_nolock (¡Ì)
inline void read(int& x){
	int s=0,w=1;char ch=getchar_unlocked();
	while(ch<'0'||ch>'9'){
		if(ch=='-') w=-1;
		ch=getchar_unlocked();
	}
	while(ch>='0'&&ch<='9'){
		s=(s*10)+ch-'0';
		ch=getchar_unlocked();
	}
	x=s*w;
}

//(?) 
void write(int x) {
  	static int sta[35];
  	int top = 0;
  	do {
    	sta[top++] = x % 10, x /= 10;
  	} while (x);
  	while (top) putchar(sta[--top] + 48);  // 48 ÊÇ '0'
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int x;
    int a=3;
    char t='\n';
    write(a);
    write(t);
    return 0;
}
