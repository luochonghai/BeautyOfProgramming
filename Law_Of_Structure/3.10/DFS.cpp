/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {//可以尝试用非递归的方式来实现。
public:
    vector<vector<int>> levelOrder(TreeNode* root) 
    {
        vector<vector<int>>result;
        local_level(result,root,0);
        return result;
    }
private:
    void local_level(vector<vector<int>> &result,TreeNode* root,int temp_level)
    {
        if(!root)
            return;
        int len = result.size();
        if(temp_level > len-1)
        {
            result.push_back(vector<int>{root->val});
        }
        else
        {
            result[temp_level].push_back(root->val);
        }
        
        local_level(result,root->left,temp_level+1);
        local_level(result,root->right,temp_level+1);
    }
};
