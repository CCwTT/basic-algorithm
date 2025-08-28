//bf O(n*m)
class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(root&&subRoot){
            return same(root,subRoot)||isSubtree(root->left,subRoot)||isSubtree(root->right,subRoot);
        }
        return subRoot==nullptr;
    }

    bool same(TreeNode* a,TreeNode* b){
        if(!a&&!b) return true;
        if(a&&b){
            return a->val==b->val&&same(a->left,b->left)&&same(a->right,b->right);
        }
        return false;
    }
};

//https://leetcode.cn/problems/subtree-of-another-tree/
//@@@
//kmp dfn
typedef long long ll;
class Solution {
public:
    vector<ll> get_next(vector<ll> s){
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
    
    ll kmp(vector<ll> s,vector<ll> t){
    	ll m=s.size(),n=t.size();
    	auto next=get_next(t);
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
    	return j==n?i-n:-1;
    }

    vector<ll> serialize(TreeNode* rt){
        vector<ll> res;
        function<void(TreeNode*)> dfs=[&](TreeNode* p){
            if(!p){
                res.push_back(LLONG_MAX); //!!!
                return;
            }
            res.push_back(p->val);
            dfs(p->left);
            dfs(p->right);
        };
        dfs(rt);
        return res;
    }

    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(root&&subRoot){
            auto s=serialize(root);
            auto t=serialize(subRoot);
            return ~kmp(s,t);
        }
        return !subRoot;
    }
};

