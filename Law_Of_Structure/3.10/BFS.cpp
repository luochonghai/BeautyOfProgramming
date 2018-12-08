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
        if(!root)
            return result;
        queue<TreeNode*> temp_level;
        temp_level.push(root);
        int old_num = 1,new_num = 0,levels = 0,sig_levels = 0;
        while(old_num--)
        {
            TreeNode* temp_node = temp_level.front();
            temp_level.pop();
            if(sig_levels == 0)
            {
                sig_levels = 1;
                result.push_back(vector<int>{temp_node->val});
            }
            else
                result[levels].push_back(temp_node->val);
            if(temp_node->left != NULL)
            {
                temp_level.push(temp_node->left);            
                new_num++;
            }
            if(temp_node->right != NULL)
            {
                temp_level.push(temp_node->right);
                new_num++;
            }
            if(old_num == 0)
            {
                levels++;
                sig_levels = 0;
                old_num = new_num;
                new_num = 0;
            }
        }
        return result;
    }
};
