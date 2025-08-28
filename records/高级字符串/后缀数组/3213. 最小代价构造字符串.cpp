//https://leetcode.cn/problems/construct-string-with-minimum-cost/description/
//MLE
//SA
typedef long long ll;
class Solution {
public:
    int minimumCost(string target, vector<string>& words, vector<int>& costs) {
        const ll N=1e5+5;
        ll n=target.size();
        target=" "+target;
        vector<int> bel(2*n+1),buc(max(2*n+1,123ll)),tmp(2*n+1),sa(n+1),rk(n+1);
        ll nbuc=122;
        auto get_sa=[&](){
            for(ll i=1;i<=n;i++) buc[bel[i]=target[i]]++;
            for(ll i=1;i<=nbuc;i++) buc[i]+=buc[i-1];
            for(ll i=n;i>=1;i--) sa[buc[bel[i]]--]=i;
            for(ll k=1;k<=n;k<<=1){
                //sort by the second key
                fill(buc.begin(),buc.end(),0);
                for(ll i=1;i<=n;i++) tmp[i]=sa[i];
                for(ll i=1;i<=n;i++) buc[bel[tmp[i]+k]]++;
                for(ll i=1;i<=nbuc;i++) buc[i]+=buc[i-1];
                for(ll i=n;i>=1;i--) sa[buc[bel[tmp[i]+k]]--]=tmp[i];
                //sort by the first key
                fill(buc.begin(),buc.end(),0);
                for(ll i=1;i<=n;i++) tmp[i]=sa[i];
                for(ll i=1;i<=n;i++) buc[bel[tmp[i]]]++;
                for(ll i=1;i<=nbuc;i++) buc[i]+=buc[i-1];
                for(ll i=n;i>=1;i--) sa[buc[bel[tmp[i]]]--]=tmp[i];
                //put suffix array into buc array
                for(ll i=1;i<=n;i++) tmp[i]=bel[i];
                nbuc=0;
                for(ll i=1;i<=n;i++){
                    if(tmp[sa[i]]==tmp[sa[i-1]]&&tmp[sa[i]+k]==tmp[sa[i-1]+k]){
                        bel[sa[i]]=nbuc;
                    }else{
                        bel[sa[i]]=++nbuc;
                    }
                }
                if(nbuc==n) break;
            }
        };
        get_sa();
        for(ll i=1;i<=n;i++){
            rk[sa[i]]=i;
        }
        vector<vector<pair<int,int>>> from(n+1);

        auto check=[&](string& s,ll x)->ll{
            for(ll i=0;i<s.size();i++){
                if(x+i>n) return 1;
                if(s[i]>target[x+i]){
                    return 1;
                }else if(s[i]<target[x+i]){
                    return -1;
                }
            }
            return 0;
        };

        auto lbound=[&](string& s){
            ll l=1,r=n;
            ll res=-1;
            while(l<=r){
                ll m=l+r>>1;
                ll ret=check(s,sa[m]);
                if(ret==0){
                    res=m;
                    r=m-1;
                }else if(ret==1){
                    l=m+1;
                }else{
                    r=m-1;
                }
            }
            return res;
        };

        auto rbound=[&](string& s){
            ll l=1,r=n;
            ll res=-1;
            while(l<=r){
                ll m=l+r>>1;
                ll ret=check(s,sa[m]);
                if(ret==0){
                    res=m;
                    l=m+1;
                }else if(ret==1){
                    l=m+1;
                }else{
                    r=m-1;
                }
            }
            return res;
        };

        ll wi=0;
        for(auto& word:words){
            ll lb=lbound(word);
            ll rb=rbound(word);
            if(lb==-1){
                wi++;
                continue;
            }
            for(ll i=lb;i<=rb;i++){
                ll pos=sa[i];
                from[pos+word.size()-1].push_back({pos-1,costs[wi]});
            }
            wi++;
        }

        vector<int> dp(n+1,INT_MAX/2);
        dp[0]=0;
        for(ll i=1;i<=n;i++){
            for(const auto& [prev,c]:from[i]){
                dp[i]=min(dp[i],dp[prev]+c);
            }
        }
        return dp[n]==INT_MAX/2?-1:dp[n];
    }
};