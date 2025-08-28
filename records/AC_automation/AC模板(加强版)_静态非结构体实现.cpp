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
    ll ch[MX][26],fail[MX],cnt[MX];
    vector<ll> ed[MX];
    ll ncnt,nstr;
    vector<ll> E[MX];

    AC(ll nstr):nstr(nstr),ch{},fail{},cnt{},ed{},ncnt(0),E{}{}

    void insert(string s,ll id){
        ll p=0;
        for(auto c:s){
            ll x=c-'a';
            if(!ch[p][x]){
                ch[p][x]=++ncnt;
            }
            p=ch[p][x];
        }
        ed[p].push_back(id);
    }

    void build(){
        queue<ll> q;
        for(ll i=0;i<26;i++){
            if(ch[0][i]){
                q.push(ch[0][i]);
            }
        }
        while(!q.empty()){
            ll u=q.front();
            q.pop();
            for(ll i=0;i<26;i++){
                ll v=ch[u][i];
                if(ch[u][i]){
                    fail[ch[u][i]]=ch[fail[u]][i];
                    q.push(ch[u][i]);
                }else{
                    ch[u][i]=ch[fail[u]][i];
                }
            }
        }
        for(ll i=1;i<=ncnt;i++){
            E[fail[i]].push_back(i);
        }
    }

    vector<ll> query(string s){
        ll p=0;
        for(auto c:s){
            ll x=c-'a';
            p=ch[p][x];
            cnt[p]++;
        }
        vector<ll> ans(nstr);
        function<ll(ll)> dfs=[&](ll x)->ll{
            ll res=cnt[x];
            for(ll y:E[x]){
                res+=dfs(y);
            }
            for(ll id:ed[x]){
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
