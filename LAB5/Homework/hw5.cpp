#include <iostream>
#include <stack>
using namespace std;

struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char v) : val(v), left(nullptr), right(nullptr) {}
};

TreeNode* buildExpressionTree(const string& postfix) {
    stack<TreeNode*> st;
    for (char ch : postfix) {
        if (isdigit(ch)) {
            st.push(new TreeNode(ch));
        } else {
            TreeNode* right = st.top(); st.pop();
            TreeNode* left = st.top(); st.pop();
            TreeNode* node = new TreeNode(ch);
            node->left = left;
            node->right = right;
            st.push(node);
        }
    }
    return st.top();
}

int evaluate(TreeNode* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return root->val - '0';

    int left = evaluate(root->left);
    int right = evaluate(root->right);

    switch (root->val) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
    }
    return 0;
}

int main() {
    string postfix = "53+62/*";
    TreeNode* root = buildExpressionTree(postfix);
    cout << "Expression Result: " << evaluate(root) << endl;
    return 0;
}
