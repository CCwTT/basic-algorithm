//https://leetcode.cn/problems/binary-tree-cameras/
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
    tuple<int,int,int> dfs(TreeNode* p){
        if(!p){
            return {INT_MAX/3,0,0};
        }
        auto [lyes,lno_bych,lno_byfa]=dfs(p->left);
        auto [ryes,rno_bych,rno_byfa]=dfs(p->right);
        int yes=min({lyes,lno_bych,lno_byfa})+min({ryes,rno_bych,rno_byfa})+1;
        int no_bych=min({lyes+ryes,lno_bych+ryes,lyes+rno_bych});
        int no_byfa=min({lyes,lno_bych})+min({ryes,rno_bych});
        return {yes,no_bych,no_byfa};
    }

    int minCameraCover(TreeNode* root) {
        auto [yes,no_bych,no_byfa]=dfs(root);
        return min(yes,no_bych);
    }
};