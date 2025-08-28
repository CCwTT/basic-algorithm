//https://leetcode.cn/problems/count-prefix-and-suffix-pairs-ii/submissions/638839327/
//@@@
//Z array,Trie
typedef long long ll;
vector<ll> get_z(string s){
    ll n=s.size();
    vector<ll> z(n);
    z[0]=n;
    for(ll i=1,boxl=1,boxr=1;i<n;i++){
        z[i]=i<boxr?min(boxr-i,z[i-boxl]):0;
        while(i+z[i]<n&&s[i+z[i]]==s[z[i]]){
            z[i]++;
        }
        if(i+z[i]>boxr){
            boxr=i+z[i];
            boxl=i;
        }
    }
    return z;
}
class Trie{
public:
    Trie* nexts[26];
    ll ed;
    Trie():ed(0),nexts{}{}

    ll insert_and_count(string word){
        Trie* p=this;
        auto z=get_z(word);
        ll res=0;
        ll n=word.size();
        for(ll i=0;i<n;i++){
            ll path=word[i]-'a';
            if(!p->nexts[path]){
                p->nexts[path]=new Trie();
            }
            p=p->nexts[path];
            if(z[n-1-i]==i+1){
                res+=p->ed;
            }
        }
        p->ed++;
        return res;
    }
};

class Solution {
public:
    long long countPrefixSuffixPairs(vector<string>& words) {
        Trie trie;
        ll ans=0;
        for(auto word:words){
            ans+=trie.insert_and_count(word);
        }
        return ans;
    }
};

//method2 Z array,map,hash
typedef long long ll;
class Solution {
public:
    vector<ll> get_z(string s){
        ll n=s.size();
        vector<ll> z(n);
        z[0]=n;
        for(ll i=1,boxl=1,boxr=1;i<n;i++){
            z[i]=i<boxr?min(boxr-i,z[i-boxl]):0;
            while(i+z[i]<n&&s[i+z[i]]==s[z[i]]){
                z[i]++;
            }
            if(i+z[i]>boxr){
                boxr=i+z[i];
                boxl=i;
            }
        }
        return z;
    }

    ll p=19937;

    ll qpow(ll x,ll n){
        if(x==0) return 0;
        ll res=1;
        while(n){
            if(n&1) res*=x;
            n>>=1;
            x*=x;
        }
        return res;
    }

    long long countPrefixSuffixPairs(vector<string>& words) {
        unordered_map<ll,ll> mp;
        ll ans=0;
        for(auto& word:words){
            auto z=get_z(word);
            ll n=word.size();
            vector<ll> h(n+1);
            h[0]=0;
            for(ll i=1;i<=n;i++){
                h[i]=(h[i-1]*p+word[i-1])%INT_MAX;
            }
            cout<<endl;
            for(ll i=1;i<n;i++){
                if(z[i]==n-i){
                    ans+=mp[h[z[i]]];
                }
            }
            ans+=mp[h[n]];
            mp[h[n]]++;
        }
        return ans;
    }
};