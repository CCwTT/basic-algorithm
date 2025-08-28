typedef long long ll;
#define DEGUB
#define strr(x) (#x)
#define _Logstrr(a) cout<<strr(a)<<": "
#define _Log(a) cout<<strr(a)<<":"<<a
#define _Log2(a,b) _Log(a)<<" "<<strr(b)<<":"<<b
#define _Log3(a,b,c) _Log2(a,b)<<" "<<strr(c)<<":"<<c
#define _Log4(a,b,c,d) _Log3(a,b,c)<<" "<<strr(d)<<":"<<d

#define _Log5(a,b,c,d,e) _Log4(a,b,c,d)<<" "<<strr(e)<<":"<<e
#define _Log6(a,b,c,d,e,f) _Log5(a,b,c,d,e)<<" "<<strr(f)<<":"<<f
#define _Log7(a,b,c,d,e,f,g) _Log6(a,b,c,d,e,f)<<" "<<strr(g)<<":"<<g
#define _endl <<endl;
#define Log0(func) _Logstrr(func)_endl;
#define Log1(func,a) _Logstrr(func);_Log(a)_endl;
#define Log2(func,a,b) _Logstrr(func);_Log2(a,b)_endl;
#define Log3(func,a,b,c) _Logstrr(func);_Log3(a,b,c)_endl;
#define Log4(func,a,b,c,d) _Logstrr(func);_Log4(a,b,c,d)_endl;
#define Log5(func,a,b,c,d,e) _Logstrr(func);_Log5(a,b,c,d,e)_endl;
#define Log6(func,a,b,c,d,e,f) _Logstrr(func);_Log6(a,b,c,d,e,f)_endl;
#define Log7(func,a,b,c,d,e,f,g) _Logstrr(func);_Log7(a,b,c,d,e,f,g)_endl;
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

ll tabs=0;

class CountIntervals {
public:
const ll n=1000000000;
const ll LIMIT=7000001;
vector<ll> le,ri,sum;
ll cnt=1;
    CountIntervals() {
        le.assign(LIMIT,0);
	    ri.assign(LIMIT,0);
	    sum.assign(LIMIT,0);
	    cnt=1;
    }
    


void up(ll p){
	sum[p]=sum[le[p]]+sum[ri[p]];
}
void setOne(ll p,ll l,ll r,ll x,ll y){
    HEAD5(setOne,p,l,r,x,y);
	if(sum[p]==r-l+1){
		return;
	}
	if(x<=l&&r<=y){
		sum[p]=r-l+1;
		return;
	}
	ll m=l+r>>1;
	if(x<=m){
		if(le[p]==0) le[p]=++cnt;
		setOne(le[p],l,m,x,y);
	}
	if(r>m){
		if(ri[p]==0) ri[p]=++cnt;
		setOne(ri[p],m+1,r,x,y);
	}
	up(p);
    TAIL;
}

void add(ll l,ll r){
    HEAD2(add,l,r);
	setOne(1,1,n,l,r);
    TAIL;
}
    
    int count() {
        return sum[1];
        
    }
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */