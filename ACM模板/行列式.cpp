#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void printmat(vector<vector<double>>& mat) {
	for(int i=0;i<mat.size();i++){
		for(int j=0;j<mat[0].size();j++){
			cout<<setw(5)<<mat[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
}

//0-indexed
//�������б任�� (��)
void gauss(vector<vector<double>>& mat){
	const double eps=1e-8;
	int n=mat.size();
	//printmat(mat); 
	for(int i=0;i<n;i++){
		int row_max=i;
		for(int j=0;j<n;j++){
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
			for(int j=i;j<n;j++){
				mat[i][j]/=tmp;
			}
			for(int j=0;j<n;j++) if(i!=j){
				tmp=mat[j][i]/mat[i][i];
				for(int k=i;k<n;k++){
					mat[j][k]-=mat[i][k]*tmp;
				}
			}
		}
		printmat(mat);
	}
}
//ǧ��ע��,��������Ҫ��fabs(x)<1e-8 

double det(vector<vector<double>>& mat){
	double ret=1; 
	const double eps=1e-8;
	int n=mat.size();
	for(int i=0;i<n;i++){
		int row_max=i;
		for(int j=0;j<n;j++){
			if(j<i&&fabs(mat[j][j])>=eps){
				continue;
			}
			if(fabs(mat[j][i])>fabs(mat[row_max][i])){
				row_max=j;
			}
		}
		swap(mat[row_max],mat[i]);
		if(row_max!=i){
			ret*=-1;
		}
		if(fabs(mat[i][i])>=eps){
			double tmp=mat[i][i];
			ret*=tmp;
			for(int j=i;j<n;j++){
				mat[i][j]/=tmp;
			}
			for(int j=0;j<n;j++) if(i!=j){
				tmp=mat[j][i]/mat[i][i];
				for(int k=i;k<n;k++){
					mat[j][k]-=mat[i][k]*tmp;
				}
			}
		}else{
			return 0;
		}
	}
	return ret;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
	vector<vector<double>> mat={
		{1,2,3,4},{-2,1,-4,3},{3,-4,-1,2},{4,3,-2,1}
	};
	cout<<det(mat)<<endl;
	//
    return 0;
}
