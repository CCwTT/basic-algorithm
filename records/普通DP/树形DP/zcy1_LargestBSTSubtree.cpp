//https://leetcode.cn/problems/largest-bst-subtree/
//@@@
//tree dp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
struct info{
    bool is_bst;
    int mx_bst;
    int mx;
    int mn;
    int sz;
    info(bool is_bst=true,int mx_bst=0,int mx=INT_MIN/2,int mn=INT_MAX/2,int sz=0):is_bst(is_bst),mx_bst(mx_bst),mx(mx),mn(mn),sz(sz) {}
};
class Solution {
public:
    info dfs(TreeNode* root){
        if(!root){
            return info();
        }
        auto linfo=dfs(root->left);
        auto rinfo=dfs(root->right);
        info res;
        res.is_bst=linfo.is_bst&&rinfo.is_bst&&root->val>linfo.mx&&root->val<rinfo.mn;
        res.mx=max({root->val,linfo.mx,rinfo.mx});
        res.mn=min({root->val,linfo.mn,rinfo.mn});
        res.sz=linfo.sz+rinfo.sz+1;
        if(res.is_bst){
            res.mx_bst=res.sz;
        }else{
            res.mx_bst=max(linfo.mx_bst,rinfo.mx_bst);
        }
        return res;
    }

    int largestBSTSubtree(TreeNode* root) {
        return dfs(root).mx_bst;
    }
};