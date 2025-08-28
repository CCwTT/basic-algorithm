//https://leetcode.cn/problems/maximum-sum-bst-in-binary-tree/
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
    int sum;
    info(bool is_bst=true,int mx_bst=0,int mx=INT_MIN/2,int mn=INT_MAX/2,int sum=0):is_bst(is_bst),mx_bst(mx_bst),mx(mx),mn(mn),sum(sum) {}
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
        res.sum=linfo.sum+rinfo.sum+root->val;
        res.mx_bst=max(linfo.mx_bst,rinfo.mx_bst);
        if(res.is_bst){
            res.mx_bst=max(res.mx_bst,res.sum);
        }
        return res;
    }
    int maxSumBST(TreeNode* root) {
        return dfs(root).mx_bst;
    }
};