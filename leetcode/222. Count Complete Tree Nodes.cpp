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
    int countNodes(TreeNode* root) {
        if(!root)
            return 0;
        
        int low = 1, high = static_cast<int>(5e4) + 1;

        while(low < high) {
            auto mid = (low + high) / 2;

            if(!checkNode(root, mid))
                high = mid;
            else
                low = mid + 1;
        }

        return high - 1;
    }

private:
    bool checkNode(TreeNode* root, int p) {
        int lg = 32 - __builtin_clz(p);
        int cur = 0;

        for(int i = lg - 1; i >= 0 && root; --i) {
            if(p & (1 << i)) {
                if(cur)
                    root = root->right;
                cur = (cur << 1) | 1;
            } else {
                cur <<= 1;
                root = root->left;
            }
        }

        return root != nullptr;
    }
};