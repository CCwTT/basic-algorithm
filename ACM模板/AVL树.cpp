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

//https://www.luogu.com.cn/problem/P3369
//@@@
//avl
class AVL{
public:
    struct Node{
        ll key;
        ll val;
        Node* lc;
        Node* rc;
        ll height;
        ll sz; 
    };
    Node* root=nullptr;

    ll get_height(Node* p){
        if(!p) return 0;
        return p->height;
    }
    
    ll get_size(Node* p){
        if(!p) return 0;
        return p->sz;
    }

    void up(Node* p){
        p->height = max(get_height(p->lc), get_height(p->rc)) + 1;
        p->sz = get_size(p->lc) + get_size(p->rc) + p->val;
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

    Node* insert(Node* p,ll x){
        if(!p){
            p=new Node;
            p->key=x;
            p->val=1;
            p->lc=p->rc=nullptr;
            p->height=1;
            p->sz=1;
            return p;
        }
        if(x==p->key){
            p->val++;
        }else if(x<p->key){
            p->lc=insert(p->lc,x);
        }else{
            p->rc=insert(p->rc,x);
        }
        up(p);
        return maintain(p);
    }

    void insert(ll x){
        root=insert(root,x);
    }

    ll get_rank(Node* p,ll x){
        if(!p) return 1;
        if(x==p->key) return get_size(p->lc)+1;
        else if(x<p->key) return get_rank(p->lc,x);
        else return get_size(p->lc)+p->val+get_rank(p->rc,x);
    }

    ll get_rank(ll x){
        return get_rank(root,x);
    }

    pair<Node*,Node*> remove_leftmost(Node* p){
        if(!p) return {nullptr,nullptr};
        if(!p->lc) return {p->rc,p};
        auto [nlc,lm]=remove_leftmost(p->lc);
        p->lc=nlc;
        up(p);
        return {maintain(p),lm};
    }

    Node* remove(Node* p,ll x){
        if(x==p->key){
            if(p->val>1){
                p->val--;
            }else{
                if(!p->lc&&!p->rc){
                    return nullptr;
                }else if(p->lc&&!p->rc){
                    return p->lc;
                }else if(p->rc&&!p->lc){
                    return p->rc;
                }else{
                    auto [nrc,np]=remove_leftmost(p->rc);
                    np->lc=p->lc;
                    np->rc=nrc;
                    p=np;
                }
            }
        }else if(x<p->key){
            p->lc=remove(p->lc,x);
        }else{
            p->rc=remove(p->rc,x);
        }
        up(p);
        return maintain(p);
    }

    void remove(ll x){
        if(get_rank(x)!=get_rank(x+1)){
            root=remove(root,x);
        }
    }

    ll at(Node* p,ll x){ //rank->key rank is 1-indexed
        if(get_size(p->lc)>=x){
            return at(p->lc,x);
        }else if(get_size(p->lc)+p->val>=x){
            return p->key;
        }else{
            return at(p->rc,x-get_size(p->lc)-p->val);
        }
    }

    ll at(ll x){
        if(x<=0) return LLONG_MIN;
        if(x>get_size(root)) return LLONG_MAX;
        return at(root,x);
    }

    ll prev(Node* p,ll x){
        if(!p) return LLONG_MIN;
        if(x<=p->key){
            return prev(p->lc,x);
        }else{
            return max(p->key,prev(p->rc,x));
        }
    }

    ll prev(ll x){
        return prev(root,x);
    }

    ll next(Node* p,ll x){
        if(!p) return LLONG_MAX;
        if(x>=p->key){
            return next(p->rc,x);
        }else{
            return min(p->key,next(p->lc,x));
        }
    }

    ll next(ll x){
        return next(root,x);
    }
};

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    AVL avl;
    ll n;
    cin>>n;
    for(ll i=0;i<n;i++){
        ll op,x;
        cin>>op>>x;
        if(op==1){
            avl.insert(x);
        }else if(op==2){
            avl.remove(x);
        }else if(op==3){
            cout<<avl.get_rank(x)<<endl;
        }else if(op==4){
            cout<<avl.at(x)<<endl;
        }else if(op==5){
            cout<<avl.prev(x)<<endl;
        }else{
            cout<<avl.next(x)<<endl;
        }
    }
    return 0;
}
