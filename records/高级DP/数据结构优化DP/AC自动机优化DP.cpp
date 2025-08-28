//https://leetcode.cn/problems/minimum-number-of-valid-strings-to-form-target-ii/
//@@@
//AC,dp
class AC{
public:
    struct Node{
        Node* ch[26]{};
        Node* fail;
        int len;
        Node(int len):len(len){}
    };
    Node* root=new Node(0);

    void insert(string& s){
        auto p=root;
        for(char c:s){
            int x=c-'a';
            if(p->ch[x]==nullptr){
                p->ch[x]=new Node(p->len+1);
            }
            p=p->ch[x];
        }
    }

    void build_fail(){
        root->fail=root;
        queue<Node*> q;
        for(auto& ch:root->ch){
            if(ch){
                ch->fail=root;
                q.push(ch);
            }else{
                ch=root;
            }
        }
        while(!q.empty()){
            auto u=q.front();
            q.pop();
            for(int i=0;i<26;i++){
                auto& v=u->ch[i];
                if(v){
                    v->fail=u->fail->ch[i];
                    q.push(v);
                }else{
                    v=u->fail->ch[i];
                }
            }
        }
    }
};

class Solution{
public:
    int minValidStrings(vector<string>& words,string target){
        AC ac;
        for(auto& w:words){
            ac.insert(w);
        }
        ac.build_fail();

        int n=target.size();
        vector<int> f(n+1);
        auto p=ac.root;
        for(int i=1;i<=n;i++){
            int x=target[i-1]-'a';
            p=p->ch[x];
            if(p==ac.root){
                return -1;
            }
            f[i]=f[i-p->len]+1;
        }
        return f[n];
    }
};