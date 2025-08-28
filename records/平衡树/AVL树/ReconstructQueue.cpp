//https://leetcode.cn/problems/queue-reconstruction-by-height/
//@@@
//avl
class AVL{
public:
    struct Node{
        int key;
        int val;
        Node* lc;
        Node* rc;
        int height;
        int sz; 
    };
    Node* root=nullptr;

    int get_height(Node* p){
        if(!p) return 0;
        return p->height;
    }
    
    int get_size(Node* p){
        if(!p) return 0;
        return p->sz;
    }

    void up(Node* p){
        p->height = max(get_height(p->lc), get_height(p->rc)) + 1;
        p->sz = get_size(p->lc) + get_size(p->rc) + 1;
    }

    Node* left_rotate(Node* p){
        Node* tmp = p->rc;
        p->rc = tmp->lc;
        tmp->lc = p;
        up(p);
        up(tmp);
        return tmp;
    }

    Node* right_rotate(Node* p){
        Node* tmp = p->lc;
        p->lc = tmp->rc;
        tmp->rc = p;
        up(p);
        up(tmp);
        return tmp;
    }

    Node* ll_rotate(Node* p){
        return right_rotate(p);
    }

    Node* rr_rotate(Node* p){
        return left_rotate(p);
    }

    Node* lr_rotate(Node* p){
        p->lc = left_rotate(p->lc);
        return right_rotate(p);
    }

    Node* rl_rotate(Node* p){
        p->rc = right_rotate(p->rc);
        return left_rotate(p);
    }

    Node* maintain(Node* p){
        if(get_height(p->lc) - get_height(p->rc) > 1){
            if(get_height(p->lc->lc) >= get_height(p->lc->rc)){
                return ll_rotate(p);
            } else {
                return lr_rotate(p);
            }
        } else if(get_height(p->rc) - get_height(p->lc) > 1){
            if(get_height(p->rc->rc) >= get_height(p->rc->lc)){
                return rr_rotate(p);
            } else {
                return rl_rotate(p);
            }
        }
        return p;
    }

    Node* insert(Node* p,int rest,pair<int,int> v){
        if(!p){
            p=new Node;
            p->key=v.first;
            p->val=v.second;
            p->sz=p->height=1;
            p->lc=p->rc=nullptr;
            return p;
        }
        if(get_size(p->lc)>=rest){
            p->lc=insert(p->lc,rest,v);
        }else{
            p->rc=insert(p->rc,rest-get_size(p->lc)-1,v);
        }
        up(p);
        return maintain(p);
    }

    void insert(pair<int,int> v){
        root=insert(root,v.second,v);
    }

    vector<vector<int>> inorder(){
        vector<vector<int>> res;
        function<void(Node*)> dfs=[&](Node* p)->void{
            if(!p) return;
            dfs(p->lc);
            res.push_back({p->key,p->val});
            dfs(p->rc);
        };
        dfs(root);
        return res;
    }
};

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(),people.end(),[](const vector<int>& u,const vector<int>& v){
            return u[0]>v[0]||(u[0]==v[0]&&u[1]<v[1]);
        });
        vector<vector<int>> ans;
        AVL avl;
        for(auto person:people){
            avl.insert({person[0],person[1]});
        }
        ans=avl.inorder();
        return ans;
    }
};