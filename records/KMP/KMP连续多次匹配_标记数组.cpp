//https://leetcode.cn/problems/find-beautiful-indices-in-the-given-array-ii/
//@@@
//consecutive multiple matches
typedef long long ll;
class Solution {
public:
    vector<ll> get_next(string t){
        ll n=t.size()-1;
        vector<ll> next(n+2);
        next[0]=next[1]=0;
        next[2]=1;
        ll i=3,j=1;
        while(i<=n+1){
            if(t[i-1]==t[j]){
                next[i++]=++j;
            }else if(j>1){
                j=next[j];
            }else{
                next[i++]=1;
            }
        }
        return next;
    }

    vector<ll> kmp(string s,string t){
        auto next=get_next(t);
        ll m=s.size()-1,n=t.size()-1;
        vector<ll> res(m+1,0);
        ll i=1,j=1;
        while(i<=m){
            if(s[i]==t[j]){
                i++,j++;
            }else if(j>1){
                j=next[j];
            }else{
                i++;
            }
            if(j==n+1){
                res[i-n]=1;
                j=next[j];
            }
        }
        return res;
    }

    vector<int> beautifulIndices(string s, string a, string b, int k) {
        s=" "+s;
        a=" "+a;
        b=" "+b;
        auto ret1=kmp(s,a);
        auto ret2=kmp(s,b);
        vector<ll> sum(ret2.size());
        partial_sum(ret2.begin()+1,ret2.end(),sum.begin()+1);
        vector<int> ans;
        for(ll i=1;i<ret1.size();i++){
            if(ret1[i]){
                ll left=max(1ll,i-k);
                ll right=min((ll)ret1.size()-1,i+k);
                if(sum[right]-sum[left-1]){
                    ans.push_back(i-1);
                }
            }
        }
        return ans;
    }
};