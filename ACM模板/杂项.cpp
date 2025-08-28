#include<bits/stdc++.h>
using namespace std;
typedef ll ll;

//Ԥ����1~1e9��Χ�ڵĻ�����
vector<int> pal;

auto init=[] {
    //pal.push_back(0); //�ڱ�,��ֹ��������е�i�±�Խ��
    //�ϸ�˳���С�����������л������������ַ���ת����
    for(int base=1;base<=10000;base*= 10) {
        //�����������Ȼ�����
        for(int i=base;i<base*10;i++){
            int x=i;
            for(int t=i/10;t;t/=10){
                x=x*10+t%10;
            }
            pal.push_back(x);
        }
        //����ż�����Ȼ�����
        if(base<=1000){
            for(int i=base;i<base*10;i++){
                int x=i;
                for(int t=i;t;t/=10){
                    x=x*10+t%10;
                }
                pal.push_back(x);
            }
        }
    }
    // pal.push_back(1'000'000'001); // �ڱ�����ֹ��������е� i �±�Խ��
    return 0;
}(); 

//a������������a������Ԫ�ر�Ϊa[i]������� 
ll distance_sum(vector<int>& a,int l,int r,int i){
	int n=a.size();
	vector<ll> s(n+1);
	partial_sum(a.begin(),a.end(),s.begin()+1);
	ll L=1ll*a[i]*(i-l)-(s[i]-s[l]);
	ll R=s[r+1]-s[i+1]-1ll*a[i]*(r-i);
	return L+R;
}

void Log(vector<ll>& a){
	ll n=a.size();
	for(int i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

void Log(vector<vector<ll>>& a){
	ll m=a.size(),n=a[0].size();
	cout<<"    ";
	for(ll j=0;j<n;j++){
		cout<<setw(4)<<j;
	}
	cout<<endl;
	for(ll i=0;i<m;i++){
		cout<<"i:"<<i<<" ";
		for(ll j=0;j<n;j++){
			cout<<setw(4)<<(a[i][j]<=LLONG_MIN/2||a[i][j]>=LLONG_MAX/2?-1:a[i][j]);
		}
		cout<<endl;
	}
	cout<<endl;
}

void Log(vector<vector<vector<ll>>>& a){
	ll m=a.size(),n=a[0].size(),p=a[0][0].size();
	for(ll i=0;i<m;i++){
		cout<<"i:"<<i<<endl;
		cout<<"    ";
		for(ll k=0;k<p;k++){
			cout<<setw(4)<<k;
		}
		cout<<endl;
		for(ll j=0;j<n;j++){
			cout<<"j:"<<j<<" ";
			for(ll k=0;k<p;k++){
				cout<<setw(4)<<(a[i][j][k]<=LLONG_MIN/2||a[i][j][k]>=LLONG_MAX/2?-1:a[i][j][k]);
			}
			cout<<endl;
		}
		cout<<endl;
	}
	cout<<endl;
}

////https://www.luogu.com.cn/problem/P3740
//@@@
class Discretizer{
public:
	vector<ll> disc={LLONG_MIN};
	Discretizer() {}

	void insert(ll x){
		disc.push_back(x);
	}

	ll discretize(){
		sort(disc.begin(),disc.end());
		disc.erase(unique(disc.begin(),disc.end()),disc.end());
		return disc.size()-1;
	}

	ll query(ll x){
		return lower_bound(disc.begin(),disc.end(),x)-disc.begin();
	}
};

//https://www.lanqiao.cn/problems/1023/learning/
template<typename T>
void out(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) out(x/10);
    putchar(x%10+'0');
}

//https://www.lanqiao.cn/problems/20116/learning/
ostream &operator<<(ostream &os, __int128 x){
    string s;
    ll sign=1;
    if(x<0){
      sign=-1;
      x=-x;
    }
    if(x==0) s="0";
    while(x){
        s+=x%10+'0';
        x/=10;
    }
    if(sign==-1) s+='-';
    reverse(s.begin(), s.end());
    return os<<s;
}

istream &operator>>(istream &is, __int128 &x){
    string s;
    cin>>s;
    x=0;
    ll sign=1;
    ll i=0;
    if(s[0]=='-'){
      sign=-1;
      i=1;
    }
    for(;i<s.size();i++){
      x=x*10+(s[i]-'0');
    }
    x*=sign;
    return is;
}

//date computation
constexpr ll d[]={31,28,31,30,31,30,31,31,30,31,30,31};

bool is_leap(ll y){
	return y%400==0||(y%4==0&&y%100!=0);
}

ll days_in_month(ll y,ll m){
	return d[m-1]+(is_leap(y)&&m==2);
}

ll get_day(ll y,ll m,ll d){
	ll res=0;
	for(ll i=1970;i<y;i++) res+=365+is_leap(i);
	for(ll i=1;i<m;i++) res+=days_in_month(y,i);
	res+=d;
	return (res+2)%7+1;
}
//date computation

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	// auto start = chrono::high_resolution_clock::now();
	// for(ll i=0;i<1000000;i++){
	// 	//ll x;
	// 	double x;
	// 	cin>>x;
	// }
	// auto end = chrono::high_resolution_clock::now();
	// chrono::duration<double, milli> elapsed = end - start;
	// cout << "Elapsed time: " << elapsed.count() << " ms" << endl;
	vector<vector<ll>> a={
		{1,2,3,4},
		{5,6,7,8}
	};
	Log(a);
	vector<vector<vector<ll>>> b={
		{{1,2},{3,4},{5,6}},{{1,2},{333,3},{5,6}}
	};
	Log(b);
	return 0;
} 


// void Log(vector<vector<ll>>& a){
// 	ll m=a.size(),n=a[0].size();
// 	cout<<"   ";
// 	for(ll i=0;i<n;i++){
// 		cout<<setw(4)<<i;
// 	}
// 	cout<<endl;
// 	for(ll i=0;i<m;i++){
// 		cout<<"i: "<<i
// 	}
// }