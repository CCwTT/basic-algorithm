#include<bits/stdc++.h>
using namespace std;

template <class T> class BIT{
	int n;
	vector<T> c;
	
public:
	BIT(int n){
		this->n=n;
		c=vector<T>(n+1);
	}
	
	assign(int n){
		this->n=n;
		c=vector<T>(n+1);
	}
	
	clear(){
		c=vector<T>(n+1);
	}

	void add(int i,T delta){
		for(;i<=n;i+=i&(-i))
			c[i]+=delta;
	}
	
	void set(int i,T val){
		add(i,val-c[i]);
	}

	T sum(int i){
		T ret=0;
		for(;i;i&=(i-1))
			ret+=c[i];
		return ret;
	}
	
	T sum(int i,int j){
		return sum(j)-sum(i-1);
	}

	//weighted fenwick tree query kth smallest value(1-indexed)
	//@?
	T query_kth(int k){
		ll x=0,acc=0;
		for(ll i=1<<__lg(n);i;i>>=1){
			if(x+i<=n&&cur+c[x+i]<=k){
				x+=i;
				acc+=c[x];
			}
		}
		return x;
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	vector<int> a={400,800,200,500,-1000000,600,900,100,100};
	auto disc=a;
	sort(disc.begin(),disc.end());
	disc.erase(unique(disc.begin(),disc.end()),disc.end()); 
	unordered_map<int,int> pos;
	for(int i=0;i<a.size();i++){
		pos[a[i]]=lower_bound(disc.begin(),disc.end(),a[i])-disc.begin()+1;
	}
	
	vector<int> leftSmallerCnt(a.size());
	vector<int> leftBiggerCnt(a.size());
	vector<int> rightSmallerCnt(a.size());
	vector<int> rightBiggerCnt(a.size());
	BIT<int> fenwick(a.size()+1);
	for(int i=0;i<a.size();i++){
		leftSmallerCnt[i]=fenwick.sum(pos[a[i]]-1);
		leftBiggerCnt[i]=i-fenwick.sum(pos[a[i]]);
		fenwick.add(pos[a[i]],1);
	}
	fenwick.clear();
	for(int i=a.size()-1;i>=0;i--){
		rightSmallerCnt[i]=fenwick.sum(pos[a[i]]-1);
		rightBiggerCnt[i]=a.size()-i-fenwick.sum(pos[a[i]]);
		fenwick.add(pos[a[i]],1);
	}
	cout<<"leftSmallerCnt: ";
	for(int i=0;i<a.size();i++) cout<<leftSmallerCnt[i]<<" "; 
	cout<<endl;
	cout<<"leftBiggerCnt: ";
	for(int i=0;i<a.size();i++) cout<<leftBiggerCnt[i]<<" "; 
	cout<<endl;
	cout<<"rightSmallerCnt: ";
	for(int i=0;i<a.size();i++) cout<<rightSmallerCnt[i]<<" "; 
	cout<<endl;
	cout<<"rightBiggerCnt: ";
	for(int i=0;i<a.size();i++) cout<<rightBiggerCnt[i]<<" "; 
	cout<<endl;
	return 0;
} 
