//https://www.luogu.com.cn/problem/P5357
//@@@
//AC automation model
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void Log(vector<ll>& a){
	cout<<"Log: ";
	for(int i=0;i<a.size();i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

//AC automation had better not be implemented in dynamic method,otherwise unordered_map must be used in build_failing fail tree
class AC{
public:
    struct Node{
        Node* ch[26];
        Node* fail;
        ll cnt;
        vector<ll> ed;
    };
    Node* root=new Node();
    unordered_map<Node*,vector<Node*>> E; 
    AC(){}

    void insert(string s,ll id){
        Node* p=root;
        for(auto c:s){
            ll x=c-'a';
            if(!p->ch[x]){
                p->ch[x]=new Node();
            }
            p=p->ch[x];
        }
        p->ed.push_back(id);
    }

    void build_fail(){
        root->fail=root;
        queue<Node*> q;
        for(int i=0;i<26;i++){
            auto& v=root->ch[i];
            if(v){
                v->fail=root;
                E[root].push_back(v);
                q.push(v);
            }else{
                v=root;
            }
        }
        while(!q.empty()){
            auto u=q.front();
            q.pop();
            for(ll i=0;i<26;i++){
                auto& v=u->ch[i];
                if(v){
                    v->fail=u->fail->ch[i];
                    E[v->fail].push_back(v);
                    q.push(u->ch[i]);
                }else{
                    v=u->fail->ch[i];
                }
            }
        }
    }

    vector<ll> query(string s,ll nstr){
        Node* p=root;
        for(auto c:s){
            ll x=c-'a';
            p=p->ch[x];
            p->cnt++;
        }
        vector<ll> ans(nstr);
        function<ll(Node*)> dfs=[&](Node* x)->ll{
            ll res=x->cnt;
            for(auto y:E[x]){
                res+=dfs(y);
            }
            for(ll id:x->ed){
                ans[id]=res;
            }
            return res;
        };
        dfs(root);
        return ans;
    }
};

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll n;
    cin>>n;
    AC ac;
    string s;
    for(ll i=0;i<n;i++){
        cin>>s;
        ac.insert(s,i);
    }
    ac.build_fail();
    cin>>s;
    vector<ll> ans=ac.query(s,n);
    for(ll i=0;i<n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
