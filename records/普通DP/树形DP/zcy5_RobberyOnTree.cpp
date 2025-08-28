//https://leetcode.cn/problems/house-robber-iii/
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
    pair<int,int> dfs(TreeNode* node){
        if(node==nullptr){
            return {0,0};
        }
        auto [l_rob,l_not_rob]=dfs(node->left);
        auto [r_rob,r_not_rob]=dfs(node->right);
        int rob=l_not_rob+r_not_rob+node->val;
        int not_rob=max(l_rob,l_not_rob)+max(r_rob,r_not_rob);
        return {rob,not_rob};
    }

public:
    int rob(TreeNode* root) {
        auto [root_rob,root_not_rob]=dfs(root);
        return max(root_rob,root_not_rob);        
    }
};