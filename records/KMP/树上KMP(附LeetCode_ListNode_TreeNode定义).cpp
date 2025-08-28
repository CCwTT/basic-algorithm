/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
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
//https://leetcode.cn/problems/linked-list-in-binary-tree/
//@@@
//next,dfs
typedef long long ll;
class Solution {
public:
    vector<ll> list2vector(ListNode* head){
        auto p=head;
        vector<ll> res;
        while(p){
            res.push_back(p->val);
            p=p->next;
        }
        return res;
    }

    vector<ll> get_next(vector<ll>& s){
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

    bool isSubPath(ListNode* head, TreeNode* root) {
        auto t=list2vector(head);
        auto next=get_next(t);
        function<bool(TreeNode*,ll)> dfs=[&](TreeNode* i,ll j)->bool{
            if(j==t.size()) return true;
            if(i==nullptr) return false;
            while(j>=0&&i->val!=t[j]){
                j=next[j];
            }
            return dfs(i->left,j+1)||dfs(i->right,j+1);
        };
        return dfs(root,0);
    }
};