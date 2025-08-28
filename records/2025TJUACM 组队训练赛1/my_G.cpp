#include<bits/stdc++.h>
#define int long long
 
using namespace std;
using pii = pair<int,int>;
 
constexpr int N = 200010;
int _ = 1;
int n,ans;
 
class helper {
public:
    int fi =LLONG_MIN/2,se = LLONG_MIN/2,th = LLONG_MIN/2,fo = LLONG_MIN/2;
    int fiid = 0,seid = 0,thid = 0,foid = 0;
 
    void insert(int val,int id) {
		if(id==0||(id!=fiid&&id!=seid&&id!=thid&&id!=foid)){
			if(val>fi) {
        	    fo=se,foid=seid;
        	    th=se,thid=seid;
        	    se=fi,seid=fiid;
        	    fi=val,fiid=id;
        	}
        	else if(val>se) {
        	    fo=th,foid=thid;
        	    th=se,thid=seid;
        	    se=val,seid=id;
        	}
        	else if(val>th) {
        	    fo=th,foid=thid;
        	    th=val,thid=id;
        	}
        	else if(val>fo) {
        	    fo=val,foid=id;
        	}
		}else{
			if(id==fiid&&val>fi){
				fi=val;
				return;
			}
			if(id==seid&&val>se){
				se=val;
				return;
			}
			if(id==thid&&val>th){
				th=val;
				return;
			}
			if(id==foid&&val>fo){
				fo=val;
				return;
			}
		}
        
    }
 
    pair<int,int> get_fi() {
        return {fi,fiid};
    }
 
    pair<int,int> get_se() {
        return {se,seid};
    }
 
    pair<int,int> get_th() {
        return {th,thid};
    }
 
    pair<int,int> get_fo() {
        return {fo,foid};
    }
 
    int get_fival_except(int id) {
        if(fiid==id) {
            return se;
        } else {
            return fi;
        }
    }
 
    int get_seval_except(int id) {
        if(id==fiid||id==seid) {
            return th;
        } else {
            return se;
        }
    }
};
 
int a[N];
vector<int> g[N];
helper dl[N];
helper xdl[N];
helper sl[N];
helper xsl[N];
helper xxsl[N];
helper ljxxsl[N];
helper ljsl[N];
int dp[N];
int up[N];
 
void init_dp() {
    for(int i=0;i<=n;i++) {
        dp[i]=LLONG_MIN/2;
    }
}
 
void dfs1(int x,int fa) {
    up[x]=fa;
    dl[x].insert(a[x],-1);
    dl[x].insert(a[x],-2);
	dl[x].insert(a[x],-3);
    dl[x].insert(a[x],-4);
    xdl[x].insert(0,-1);
    xdl[x].insert(0,-2);
	xdl[x].insert(0,-3);
    xdl[x].insert(0,-4);
	sl[x].insert(a[x],0);
	sl[x].insert(a[x],0);
	sl[x].insert(a[x],0);
	sl[x].insert(a[x],0);
	xsl[x].insert(0,0);
	xsl[x].insert(0,0);
	xsl[x].insert(0,0);
	xsl[x].insert(0,0);
	xxsl[x].insert(0,-1);
	xxsl[x].insert(0,-2);
	xxsl[x].insert(0,-3);
	xxsl[x].insert(0,-4);
	ljxxsl[x].insert(0,-1);
	ljxxsl[x].insert(0,-2);
	ljxxsl[x].insert(0,-3);
	ljxxsl[x].insert(0,-4);
	ljsl[x].insert(a[x],0);
	ljsl[x].insert(a[x],0);
	ljsl[x].insert(a[x],0);
	ljsl[x].insert(a[x],0);
    for(auto y:g[x]) if(y!=fa) {
        dfs1(y,x);
        dl[x].insert(dl[y].get_fi().first+a[x],y);
        xdl[x].insert(dl[y].get_fi().first,y);
    }
    sl[x].insert(xdl[x].get_fi().first+xdl[x].get_se().first+a[x],0);
	xsl[x].insert(xdl[x].get_fi().first+xdl[x].get_se().first,0);
    ljsl[x].insert(sl[x].get_fi().first,0);
    for(auto y:g[x]) if(y!=fa) {
        ljsl[x].insert(ljsl[y].get_fi().first,0);
    }
	for(auto y:g[x]) if(y!=fa){
		if(x==8){
			cout<<"x=8,y="<<y<<endl;
		}
		xxsl[x].insert(xsl[y].get_fi().first,y);
		ljxxsl[x].insert(ljxxsl[y].get_fi().first,y);
		ljxxsl[x].insert(xsl[y].get_fi().first,y);
	}
}
 
void backtrack(int x) {
    if(x==1) return;
    int fa=up[x];
    int tmp=a[fa]+xdl[fa].get_fival_except(x)+xdl[fa].get_seval_except(x);
 
    dp[x]=max(tmp,dp[fa]);
    ans=max(ans,dp[x]+sl[x].get_fi().first);
    return;
}
 
void dfs2(int x,int fa) {
    backtrack(x);
    for(auto y:g[x]) if(y!=fa) {
        dfs2(y,x);
    }
}
 
void dfs3(int x,int fa) {
    ans=max(ans,xdl[x].get_fi().first+xdl[x].get_se().first+xdl[x].get_th().first+xdl[x].get_fo().first);
    ans=max(ans,ljxxsl[x].get_fi().first+xdl[x].get_fival_except(ljxxsl[x].get_fi().second)+xdl[x].get_seval_except(ljxxsl[x].get_fi().second));
	ans=max(ans,ljxxsl[x].get_fi().first+ljxxsl[x].get_se().first);
	for(auto y:g[x]) if(y!=fa) {
        dfs3(y,x);
    }
}
 
void Log() {
    for(int i=1;i<=n;i++) {
        cout<<dl[i].get_fi().first<<" "<<sl[i].get_fi().first<<" "<<ljsl[i].get_fi().first<<endl;
    }
    cout<<endl;
}
 
void Log_dp() {
    for(int i=1;i<=n;i++) {
        cout<<i<<" "<<dp[i]<<endl;
    }
    cout<<endl;
}

void Log1(){
	for(int i=1;i<=n;i++){
		cout<<i<<":"<<endl;
		cout<<"ssxl:"<<xxsl[i].get_fi().first<<" "<<xxsl[i].get_se().first<<" "<<xxsl[i].get_fi().second<<" "<<xxsl[i].get_se().second<<" "<<endl;
		cout<<"ljxxsl:"<<ljxxsl[i].get_fi().first<<" "<<ljxxsl[i].get_se().first<<" "<<ljxxsl[i].get_fi().second<<" "<<ljxxsl[i].get_se().second<<endl;
		cout<<"sl:"<<sl[i].get_fi().first<<" "<<sl[i].get_se().first<<" "<<sl[i].get_fi().second<<" "<<sl[i].get_se().second<<endl;
		cout<<"xsl:"<<xsl[i].get_fi().first<<" "<<xsl[i].get_se().first<<" "<<xsl[i].get_fi().second<<" "<<xsl[i].get_se().second<<endl;
		cout<<"ljsl:"<<ljsl[i].get_fi().first<<" "<<ljsl[i].get_se().first<<" "<<ljsl[i].get_fi().second<<" "<<ljsl[i].get_se().second<<endl;
		cout<<"dl:"<<dl[i].get_fi().first<<" "<<dl[i].get_se().first<<" "<<dl[i].get_fi().second<<" "<<dl[i].get_se().second<<endl;
		cout<<"xdl:"<<xdl[i].get_fi().first<<" "<<xdl[i].get_se().first<<" "<<xdl[i].get_fi().second<<" "<<xdl[i].get_se().second<<endl;
	}
}
 
void solve() {
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
		cout<<"a"<<i<<":"<<a[i]<<endl;
    }
    for(int i=1;i<n;i++) {
        int u,v;
        cin>>u>>v;
		cout<<"u:"<<u<<" v:"<<v<<endl;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1,0);
    helper help;
    for(auto y:g[1]) {
        help.insert(ljsl[y].get_fi().first,-1);
    }
    ans=help.get_fi().first+help.get_se().first;
    init_dp();
    dfs2(1,0);
 
    dfs3(1,0);
	Log1();
    cout<<ans<<endl;
}
 
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    // cin>>_;
    while(_--) solve();
    return 0;
}