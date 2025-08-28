//https://www.luogu.com.cn/problem/P5854
class Cartesian_tree{
public:
	struct Node{
		ll key;
		ll val;
		Node* lc;
		Node* rc;
		Node(){}
		Node(ll key,ll val):key(key),val(val),lc(nullptr),rc(nullptr){}
	};
	Node* root=nullptr;
	stack<Node*> stk;

	void insert(ll k,ll v){
		Node* p=new Node(k,v);
		if(!root){
			root=p;
			stk.push(p);
			return;
		}
		Node* last=nullptr;
		while(!stk.empty()&&stk.top()->val>v){ //min-heap
			last=stk.top();
			stk.pop();
		}
		if(!stk.empty()){
			stk.top()->rc=p;
		}
		if(last){
			p->lc=last;
			if(last==root){
				root=p;
			}
		}
		stk.push(p);
	}
};


//static method
//root is stk[1]
const ll MAXN=1e7+1;
ll a[MAXN];
ll lc[MAXN];
ll rc[MAXN];
ll stk[MAXN];
ll n; 

void build(){
	ll top=0;
	for(ll i=1;i<=n;i++){
		ll pos=top;
		while(pos>0&&a[stk[pos]]>a[i]){
			pos--;
		}
		if(pos>0){
			rc[stk[pos]]=i;
		}
		if(pos<top){
			lc[i]=stk[pos+1];
		}
		stk[++pos]=i;
		top=pos;
	}
}