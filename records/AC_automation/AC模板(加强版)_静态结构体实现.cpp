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

//AC automation had better not be implemented in dynamic method,otherwise unordered_map must be used in building fail tree
class AC{
public:
    static const ll MX=2e5+5; //
    struct Node{
        ll ch[26],fail,cnt;  //ch:子节点，fail:失配指针，cnt:该节点为结尾的字符串数量
        vector<ll> ed;  //把ll ed扩展成vector,记录具体是哪些字符串
        Node():ch{},fail(0),cnt(0),ed{}{}
    }tr[MX];
    ll ncnt,nstr;
    vector<ll> E[MX];

    AC(ll nstr):nstr(nstr),ncnt(0),E{}{}

    void insert(string s,ll id){
        ll p=0;
        for(auto c:s){
            ll x=c-'a';
            if(!tr[p].ch[x]){
                tr[p].ch[x]=++ncnt;
            }
            p=tr[p].ch[x];
        }
        tr[p].ed.push_back(id);
    }

    void build(){
        queue<ll> q;
        for(ll i=0;i<26;i++){
            if(tr[0].ch[i]){
                q.push(tr[0].ch[i]);
            }
        }
        while(!q.empty()){
            ll u=q.front();
            q.pop();
            for(ll i=0;i<26;i++){
                ll& v=tr[u].ch[i];
                if(v){
                    tr[v].fail=tr[tr[u].fail].ch[i];                  
                    q.push(tr[u].ch[i]);
                }else{
                    tr[u].ch[i]=tr[tr[u].fail].ch[i];
                }
            }
        }
        for(ll i=1;i<=ncnt;i++){
            E[tr[i].fail].push_back(i);
        }
    }

    vector<ll> query(string s){
        ll p=0;
        for(auto c:s){
            ll x=c-'a';
            p=tr[p].ch[x];
            tr[p].cnt++;
        }
        vector<ll> ans(nstr);
        function<ll(ll)> dfs=[&](ll x)->ll{
            ll res=tr[x].cnt;
            for(ll y:E[x]){
                res+=dfs(y);
            }
            for(ll id:tr[x].ed){
                ans[id]=res;
            }
            return res;
        };
        dfs(0);
        return ans;
    }
};

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll n;
    cin>>n;
    AC* ac=new AC(n);
    string s;
    for(ll i=0;i<n;i++){
        cin>>s;
        ac->insert(s,i);
    }
    ac->build();
    cin>>s;
    vector<ll> ans=ac->query(s);
    for(ll i=0;i<n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
