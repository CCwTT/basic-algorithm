#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void printmat(vector<vector<double>>& mat) {
	for(ll i=0;i<mat.size();i++){
		for(ll j=0;j<mat[0].size();j++){
			cout<<setw(5)<<mat[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
}

//https://atcoder.jp/contests/abc412/tasks/abc412_f
//@@@
//link:records\线性代数\高斯消元1.cpp
const ll mod=993244353;
ll qpow(ll x,ll n){
	if(x==0) return 0;
	ll res=1;
	while(n){
		if(n&1) res=res*x%mod;
		x=x*x%mod;
		n>>=1;
	}
	return res;
}

ll inv(ll x){
	return qpow(x,mod-2);
}
void gauss(vector<vector<ll>>& mat){
	ll n=mat.size()-1;
	for(ll i=1;i<=n;i++){
		ll row_max=i;
		for(ll j=1;j<=n;j++){
			if(j<i&&mat[j][j]){
				continue;
			}
			if(abs(mat[j][i])>abs(mat[row_max][i])){
				row_max=j;
			}
		}
		swap(mat[row_max],mat[i]);
		if(abs(mat[i][i])){
			ll tmp=mat[i][i];
			for(ll j=i;j<=n+1;j++){
				mat[i][j]=mat[i][j]*inv(tmp)%mod;
			}
			for(ll j=1;j<=n;j++) if(i!=j){
				tmp=mat[j][i]*inv(mat[i][i])%mod;
				for(ll k=i;k<=n+1;k++){
					mat[j][k]=(mat[j][k]-mat[i][k]*tmp%mod+mod)%mod;
				}
			}
		}
	}
}

//all 1-indexed
//����Ϊ��׼������������ 
//pretest passed
ll gauss(vector<vector<double>>& mat,vector<double>& res){
	const double eps=1e-8;
	ll n=mat.size()-1;
	res.resize(n+1);
	ll ret=0;
	//printmat(mat); 
	for(ll i=1;i<=n;i++){
		ll row_max=i;
		for(ll j=1;j<=n;j++){
			if(j<i&&fabs(mat[j][j])>=eps){
				continue;
			}
			if(fabs(mat[j][i])>fabs(mat[row_max][i])){
				row_max=j;
			}
		}
		swap(mat[row_max],mat[i]);
		if(fabs(mat[i][i])>=eps){
			double tmp=mat[i][i];
			for(ll j=i;j<=n+1;j++){
				mat[i][j]/=tmp;
			}
			for(ll j=1;j<=n;j++) if(i!=j){
				tmp=mat[j][i]/mat[i][i];
				for(ll k=i;k<=n+1;k++){
					mat[j][k]-=mat[i][k]*tmp;
				}
			}
		}
	}
	for(ll i=n;i>=1;i--){
		if(fabs(mat[i][i])<eps){
			if(fabs(mat[i][n+1])>=eps){
				return -1;
			}else{
				ret=1; 
				res[i]=0;
			}
		}else{
			res[i]=mat[i][n+1];
		}
	}
	return ret;
}

//0-indexed
//�������б任�� (��)
void gauss(vector<vector<double>>& mat){
	const double eps=1e-8;
	ll n=mat.size();
	//printmat(mat); 
	for(ll i=0;i<n;i++){
		ll mxid=i;
		for(ll j=0;j<n;j++){
			if(j<i&&fabs(mat[j][j])>=eps){
				continue;
			}
			if(fabs(mat[j][i])>fabs(mat[mxid][i])){
				mxid=j;
			}
		}
		swap(mat[mxid],mat[i]);
		if(fabs(mat[i][i])>=eps){
			for(ll k=i;k<=n;k++){
				mat[i][k]/=mat[i][i];
			}
			for(ll j=0;j<n;j++) if(i!=j){
				double ratio=mat[j][i]/mat[i][i];
				for(ll k=i;k<=n;k++){
					mat[j][k]-=mat[i][k]*ratio;
				}
			}
		}
		//printmat(mat);
	}
}
//ǧ��ע��,��������Ҫ��fabs(x)<1e-8 

//1-indexed
void gauss(vector<vector<double>>& mat){
	const double eps=1e-8;
	ll n=mat.size()-1;
	//printmat(mat); 
	for(ll i=1;i<=n;i++){
		ll row_max=i;
		for(ll j=1;j<=n;j++){
			if(j<i&&fabs(mat[j][j])>=eps){
				continue;
			}
			if(fabs(mat[j][i])>fabs(mat[row_max][i])){
				row_max=j;
			}
		}
		swap(mat[row_max],mat[i]);
		if(fabs(mat[i][i])>=eps){
			double tmp=mat[i][i];
			for(ll j=i;j<=n+1;j++){
				mat[i][j]/=tmp;
			}
			for(ll j=1;j<=n;j++) if(i!=j){
				tmp=mat[j][i]/mat[i][i];
				for(ll k=i;k<=n+1;k++){
					mat[j][k]-=mat[i][k]*tmp;
				}
			}
		}
	}
}
//ǧ��ע��,��������Ҫ��fabs(x)<1e-8 

//all 1-indexed
// pretest passed
void solveLinearSimultaneousEquations(vector<pair<vector<pair<double,ll>>,double>>& equations){
	ll m=equations.size()-1; 
	ll n=m; //������෽�̵����� 
	ll N=0;
	for(ll i=1;i<=m;i++){
		auto& equation=equations[i];
		for(ll j=1;j<equation.first.size();j++){
			auto& [coef,idx]=equation.first[j];
			N=max(N,idx);
		}
	}
	n=max(n,N);
	vector<vector<double>> mat(n+1,vector<double>(n+2,0));
	for(ll i=1;i<=m;i++){
		auto& equation=equations[i];
		mat[i][n+1]=equation.second;
		for(ll j=1;j<equation.first.size();j++){
			auto& [coef,idx]=equation.first[j];
			mat[i][idx]=coef;
		}
	}
	vector<double> solution;
	ll ret=gauss(mat,solution);
	if(ret==-1){
		cout<<"�޽�"<<endl; 
	}else if(ret==0){
		cout<<"��Ψһ��:";
		for(ll i=1;i<=N;i++){
			cout<<"x"<<i<<"="<<solution[i]<<" ";
		}
		cout<<endl;
	}else if(ret==1){
		cout<<"���,����һ���Ϊ:";
		for(ll i=1;i<=N;i++){
			cout<<"x"<<i<<"="<<solution[i]<<" ";
		}
		cout<<endl;
	}
}

//0-indexed
void gauss_xor(vector<vector<bool>>& mat){
	ll n=mat.size();
	for(ll i=0;i<n;i++){
		for(ll j=0;j<n;j++){
			if(j<i&&mat[j][j]){
				continue;
			}
			if(mat[j][i]==1){
				swap(mat[i],mat[j]);
				break;
			}
		}
		if(mat[i][i]==1){
			for(ll j=0;j<n;j++) if(i!=j){
				if(mat[j][i]==1){
					for(ll k=i;k<=n;k++){
						mat[j][k]=mat[j][k]^mat[i][k];
					}
				}
			}
		}
	}
}

const ll mod=7; 

const ll MX=mod-1;
ll inv[MX+1];
ll init=[]{
	inv[1]=1;
	for(ll i=2;i<=MX;i++){
		inv[i]=mod-1ll*inv[mod%i]*(mod/i)%mod;
	}
	return 0;
}();

//0-indexed (varitest passed)
void gauss_mod(vector<vector<ll>>& mat){
	//printmat();
	ll n=mat.size();
	for(ll i=0;i<n;i++){
		for(ll j=0;j<n;j++){
			if(j<i&&mat[j][j]){
				continue;
			}
			//�ҵ�ϵ����Ϊ0��������Ԫ���� 
			if(mat[j][i]){
				swap(mat[i],mat[j]);
				break; 
			}
		}
		if(mat[i][i]){
			for(ll j=0;j<n;j++) if(i!=j){
				if(mat[j][i]){
					ll g=gcd(mat[j][i],mat[i][i]);
					ll a=mat[i][i]/g;
					ll b=mat[j][i]/g;
					//
					if(j<i&&mat[j][j]!=0){
						for(ll k=j;k<i;k++){
							mat[j][k]=(mat[j][k]*a)%mod;
							
						}
					}
					for(ll k=i;k<=n;k++){
						mat[j][k]=((mat[j][k]*a-mat[i][k]*b)%mod+mod)%mod;
					}
					//
					//��ʵ��������߼�������ֱ��ģ���б任��Ч��������ȫһ����
					//����ֱ��ģ���б任�г�ʱ����(����ʱ�临�Ӷȶ���O(n^3)) 
//					for(ll k=0;k<=n;k++){
//						mat[j][k]=((mat[j][k]*a-mat[i][k]*b)%mod+mod)%mod;
//					}
				}
			}
		}
		//printmat(mat);
	}
	for(ll i=0;i<n;i++){
		if(mat[i][i]){
			//�Ƿ�������ԪӰ�� 
			bool flag=false;
			for(ll j=i+1;j<n;j++){
				if(mat[i][j]){
					flag=true;
					break;
				}
			}
			if(!flag){
				mat[i][n]=1ll*mat[i][n]*inv[mat[i][i]]%mod;
				mat[i][i]=1;
			}	
		}	
	}
}

ll main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    vector<vector<double>> mat1={
		{-1,-1,-1,-1,-1},
		{-1,1,1,1,6},
		{-1,1,2,3,14},
		{-1,-1,10,-4,7}
	}; 
	vector<double> res;
	ll ret=gauss(mat1,res);
	for(ll i=1;i<=3;i++){
		cout<<"x"<<i<<"="<<res[i]<<endl;
	}
	cout<<endl; 
	cout<<"--------------------------------------------------------------"<<endl; 
	ll T;
    cin>>T;
    while(T--){
    	ll m;
    	cin>>m;
    	vector<pair<vector<pair<double,ll>>,double>> equations(m+1);
    	for(ll i=1;i<=m;i++){
    		ll h;
    		cin>>h;
    		auto& equation=equations[i];
    		equation.first.resize(1);
    		for(ll j=1;j<=h;j++){
    			double coef;
    			ll idx;
    			cin>>coef>>idx;
    			equation.first.emplace_back(coef,idx);
			}
			double y;
			cin>>y;
			equation.second=y;
		}
		solveLinearSimultaneousEquations(equations);
	}
	cout<<"--------------------------------------------------------------"<<endl; 
	
    return 0;
}
