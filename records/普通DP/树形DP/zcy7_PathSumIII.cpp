//https://leetcode.cn/problems/path-sum-iii/
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
 typedef long long ll;
class Solution {
public:
    ll target;

    pair<ll,unordered_map<ll,ll>> dfs(TreeNode* p){
        if(!p){
            return {0,{}};
        }
        auto [lsum,lcnt]=dfs(p->left);
        auto [rsum,rcnt]=dfs(p->right);
        ll sum=lsum+rsum;
        unordered_map<ll,ll> cnt;
        if(p->val==target){
            sum++;
        }
        sum+=lcnt[target-p->val];
        sum+=rcnt[target-p->val];

        cnt[p->val]++;
        for(auto [x,c]:lcnt){
            cnt[x+p->val]+=c;
        }
        for(auto [x,c]:rcnt){
            cnt[x+p->val]+=c;
        }
        return {sum,cnt};
    }

    int pathSum(TreeNode* root, int targetSum) {
        target=targetSum;
        return dfs(root).first;
    }
};