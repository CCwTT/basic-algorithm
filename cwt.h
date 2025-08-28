#define str(x) (#x)
#define _Logstr(a) cout<<str(a)<<": "
#define _Log(a) cout<<str(a)<<":"<<a
#define _Log2(a,b) _Log(a)<<" "<<str(b)<<":"<<b
#define _Log3(a,b,c) _Log2(a,b)<<" "<<str(c)<<":"<<c
#define _Log4(a,b,c,d) _Log3(a,b,c)<<" "<<str(d)<<":"<<d

#define _Log5(a,b,c,d,e) _Log4(a,b,c,d)<<" "<<str(e)<<":"<<e
#define _Log6(a,b,c,d,e,f) _Log5(a,b,c,d,e)<<" "<<str(f)<<":"<<f
#define _Log7(a,b,c,d,e,f,g) _Log6(a,b,c,d,e,f)<<" "<<str(g)<<":"<<g
#define _endl <<endl;
#define Log0(func) _Logstr(func)_endl;
#define Log1(func,a) _Logstr(func);_Log(a)_endl;
#define Log2(func,a,b) _Logstr(func);_Log2(a,b)_endl;
#define Log3(func,a,b,c) _Logstr(func);_Log3(a,b,c)_endl;
#define Log4(func,a,b,c,d) _Logstr(func);_Log4(a,b,c,d)_endl;
#define Log5(func,a,b,c,d,e) _Logstr(func);_Log5(a,b,c,d,e)_endl;
#define Log6(func,a,b,c,d,e,f) _Logstr(func);_Log6(a,b,c,d,e,f)_endl;
#define Log7(func,a,b,c,d,e,f,g) _Logstr(func);_Log7(a,b,c,d,e,f,g)_endl;
#define Vtab tabs++;
#define Ptab tabs--;
#define TAB for(ll i=0;i<tabs;i++) cout<<'\t'; 


#ifdef DEBUG
#define HEAD0(func) TAB;Log0(func);Vtab;
#define HEAD1(func,a) TAB;Log1(func,a);Vtab;
#define HEAD2(func,a,b) TAB;Log2(func,a,b);Vtab;
#define HEAD3(func,a,b,c) TAB;Log3(func,a,b,c);Vtab;
#define HEAD4(func,a,b,c,d) TAB;Log4(func,a,b,c,d);Vtab;
#define HEAD5(func,a,b,c,d,e) TAB;Log5(func,a,b,c,d,e);Vtab;
#define HEAD6(func,a,b,c,d,e,f) TAB;Log6(func,a,b,c,d,e,f);Vtab;
#define HEAD7(func,a,b,c,d,e,f,g) TAB;Log7(func,a,b,c,d,e,f,g);Vtab;
#define TAIL tabs--;
#else 
#define HEAD1(func,a) 
#define HEAD2(func,a,b) 
#define HEAD3(func,a,b,c) 
#define HEAD4(func,a,b,c,d) 
#define HEAD5(func,a,b,c,d,e) 
#define HEAD6(func,a,b,c,d,e,f) 
#define HEAD7(func,a,b,c,d,e,f,g) 
#define TAIL tabs--;
#endif 

void Log(vector<ll>& a){
	ll n=a.size();
	cout<<"   ";
	for(ll i=0;i<n;i++){
		cout<<setw(4)<<i;
	}
	for(int i=0;i<a.size();i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

void Log(vector<vector<ll>>& a){
	ll m=a.size(),n=a[0].size();
	cout<<"   ";
	for(ll j=0;j<n;j++){
		cout<<setw(4)<<j;
	}
	cout<<endl;
	for(ll i=0;i<m;i++){
		cout<<"i:"<<i<<" ";
		for(ll j=0;j<n;j++){
			cout<<setw(4)<<(a[i][j]<LLONG_MIN/2||a[i][j]>LLONG_MAX/2?-1:a[i][j]);
		}
		cout<<endl;
	}
	cout<<endl;
}

void Log(vector<vector<vector<ll>>>& a){
	ll m=a.size(),n=a[0].size(),p=a[0][0].size();
	for(ll i=0;i<m;i++){
		cout<<"i:"<<i<<endl;
		cout<<"   ";
		for(ll k=0;k<p;k++){
			cout<<setw(4)<<k;
		}
		cout<<endl;
		for(ll j=0;j<n;j++){
			cout<<"j:"<<j<<" ";
			for(ll k=0;k<p;k++){
				cout<<setw(4)<<(a[i][j][k]<LLONG_MIN/2||a[i][j][k]>LLONG_MAX/2?-1:a[i][j][k]);
			}
			cout<<endl;
		}
		cout<<endl;
	}
	cout<<endl;
}