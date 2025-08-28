//https://leetcode.cn/problems/find-all-good-strings/
//@@@
//digit dp,kmp
typedef long long ll;
class Solution {
public:
    static const ll mod=1000000007;

    vector<ll> get_next(const string& s){
      ll n=s.size();
      if(n==1){
        return {-1};
      }
      vector<ll> next(n);
      next[0]=-1;
      next[1]=0;
      ll i=2,j=0;
      while(i<n){
        if(s[i-1]==s[j]){
          next[i++]=++j;
        }else if(j){
          j=next[j];
        }else{
          next[i++]=0;
        }
      }
      return next;
    }

    ll kmp(const string& s,const string& t,const vector<ll>& next) {
        ll m=s.size(),n=t.size();
        ll i=0,j=0;
        while(i<m&&j<n){
            if(s[i]==t[j]){
                i++,j++;
            }else if(j){
                j=next[j];
            }else{
                i++;
            }
        }
        return j==n?(i-j):-1;
    }

    ll helper(const string& s,const string& t,const vector<ll>& next) {
        ll m=s.size(),n=t.size();
        vector<vector<vector<ll>>> mem(m+1,vector<vector<ll>>(2,vector<ll>(n+1,-1)));
        function<ll(ll,bool,ll)> dfs=[&](ll p,bool free,ll q)->ll {
            if(q==n) return 0;
            if(p==m) return 1;
            if(~mem[p][free][q]) return mem[p][free][q];
            char cur=s[p];
            ll res=0;
            //Every blank must have a letter in it,so there's no such thing as not begun
            for(char c='a';c<=(free?'z':cur);c++){
                ll qq=q;
                while(qq>=0&&c!=t[qq]){
                    qq=next[qq];
                }
                res=(res+dfs(p+1,free||c<cur,qq+1))%mod;
            }
            mem[p][free][q]=res;
            return res;
        };
        return dfs(0,0,0);
    }

    ll findGoodStrings(ll m,string s1,string s2,string evil) {
        auto next=get_next(evil);
        ll ans1=helper(s2,evil,next);
        ll ans2=helper(s1,evil,next);
        ll ans=(ans1-ans2+mod)%mod;
        if(kmp(s1,evil,next)==-1) {
            ans=(ans+1)%mod;
        }
        return ans;
    }
};