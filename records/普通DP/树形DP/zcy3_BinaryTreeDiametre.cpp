//https://leetcode.cn/problems/diameter-of-binary-tree/
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
    int diameterOfBinaryTree(TreeNode* root) {
        int ans=0;
        auto dfs=[&](this auto&& dfs,TreeNode* node)->int{
            if(node==nullptr){
                return 0;
            }
            int l_len=dfs(node->left);
            int r_len=dfs(node->right);
            ans=max(ans,l_len+r_len+1);
            return max(l_len,r_len)+1;
        };
        dfs(root);
        return ans-1;
    }
};