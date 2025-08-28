//https://leetcode.cn/problems/distribute-coins-in-binary-tree/
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
class Solution {
public:
    int ans=0;

    pair<int,int> dfs(TreeNode* root){
        if(!root){
            return {0,0};
        }
        auto [lsz,lsum]=dfs(root->left);
        auto [rsz,rsum]=dfs(root->right);
        ans+=abs(lsz-lsum)+abs(rsz-rsum);
        return {lsz+rsz+1,lsum+rsum+root->val};
    }

    int distributeCoins(TreeNode* root) {
        dfs(root);
        return ans;
    }
};