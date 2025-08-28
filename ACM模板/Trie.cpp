#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//realization of class
//@@@
class Trie {
    ll pass;
    ll ed;
    Trie* ch[26];
public:
    Trie():pass(0),ed(0),ch{}{}
    
    void insert(string word) {
        Trie* p=this;
        //p->pass++;
        for(char c:word){
            ll x=c-'a';
            if(!p->ch[x]){
                p->ch[x]=new Trie();
            }
            p=p->ch[x];
            p->pass++;
        }    
        p->ed++;
    }

    ll erase(string word) {
        Trie* p=this;
        //p->pass--;
        for(char c:word){
            ll x=c-'a';
            if(!p->ch[x]){
                return -1;
            }
            p=p->ch[x];
            p->pass--;
        }
        p->ed--;
        return 0;
    }
    
    ll count(string word) {
        Trie* p=this;
        for(char c:word){
            ll x=c-'a';
            if(!p->ch[x]){
                return 0;
            }
            p=p->ch[x];
        }
        return p->ed;
    }
    
    ll count_prefix(string prefix) {
        Trie* p=this;
        for(char c:prefix){
            ll x=c-'a';
            if(!p->ch[x]){
                return 0;
            }
            p=p->ch[x];
        }
        return p->pass;
    }
};

//realization of class(unordered_map) @@@
class Trie {
    typedef long long ll;
    ll pass;
    ll ed;
    unordered_map<ll,Trie*> ch;
public:
    Trie():pass(0),ed(0) {}

    void insert(string word) {
        Trie* p=this;
        p->pass++;
        for(char c:word){
            ll x=c-'a';
            if(!p->ch.count(x)){
                p->ch[x]=new Trie();
            }
            p=p->ch[x];
            p->pass++;
        }
        p->ed++;
    }
    
    ll count(string word) {
        Trie* p=this;
        for(char c:word){
            ll x=c-'a';
            if(!p->ch.count(x)){
                return 0;
            }
            p=p->ch[x];
        }
        return p->ed;
    }
    
    ll count_prefix(string prefix) {
        Trie* p=this;
        for(char c:prefix){
            ll x=c-'a';
            if(!p->ch.count(x)){
                return 0;
            }
            p=p->ch[x];
        }
        return p->pass;
    }
    
    ll erase(string word) {
        Trie* p=this;
        p->pass--;
        for(auto c:word){
            ll x=c-'a';
            if(!p->ch[x]){
                return -1;
            }
            p=p->ch[x];
            p->pass--;
        }
        p->ed--;
        return 0;
    }
};

//static array @@@
const ll MAXN=150001;
ll ch[MAXN][26];
ll pass[MAXN],ed[MAXN];
ll cnt;

void init(){
    cnt=0;
}

void insert(string word){
    ll p=0;
    pass[p]++;
    for(auto c:word){
        ll x=c-'a';
        if(ch[p][x]==0){
            ch[p][x]=++cnt;
        }
        p=ch[p][x];
        pass[p]++;
    }
    ed[p]++;
}

ll count(string word){
    ll p=0;
    for(auto c:word){
        ll x=c-'a';
        if(ch[p][x]==0){
            return 0;
        }
        p=ch[p][x];
    }
    return ed[p];
}

ll count_prefix(string prefix){
    ll p=0;
    for(auto c:prefix){
        ll x=c-'a';
        if(ch[p][x]==0){
            return 0;
        }
        p=ch[p][x];
    }
    return pass[p];
}

ll erase(string word) {
    ll p=0;
    for(auto c:word){
        ll x=c-'a';
        if(ch[p][x])
        p=ch[p][x];
        pass[p]--;
    }
    ed[p]--;
    return 0;
}

void clear(){
    for(ll i=0;i<=cnt;i++){
        memset(ch[i],0,sizeof(ch[i]));
        pass[i]=ed[i]=0;
    }
} 

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    
    return 0;
}




