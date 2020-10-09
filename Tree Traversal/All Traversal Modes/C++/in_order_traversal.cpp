#include "tree_node.cpp"
#include <stack>
#include <iostream>
/* in order traversal: traverse left, root, traverse right */
template <class T>
void in_order(tree_node<T>* root)
{
    if (root->left != nullptr)
        in_order(root->left);
    
    std::cout << root->data << ' ';

    if (root->right != nullptr)
        in_order(root->right);
}

/* another in order algorithm, but this time iterative instead of recursive */
template <class T>
void in_order_iterative(tree_node<T>* root)
{
    std::stack<tree_node<T>*> s;
    tree_node<T>* cur = root;
    while (!s.empty() || cur != nullptr)
    {
        if (cur != nullptr)
        {
            s.push(cur);
            cur = cur->left;
        }
        else
        {
            cur = s.top();
            s.pop();
            std::cout << cur->data << ' ';
            cur = cur->right;
        } 
    }
}

template <class T>
void morris_traversal(tree_node<T>* root)
{
    tree_node<T>* cur = root;
    while (cur != nullptr)
    {
        if (cur->left == nullptr)
        {
            std::cout << cur->data << ' ';
            cur = cur->right;
        }
        else
        {
            auto prev = cur->left;
            while (prev->right != nullptr && prev->right != cur)
                prev = prev->right;

            if (prev->right == nullptr)
            {
                prev->right = cur;
                cur = cur->left;
            }
            else
            {
                prev->right = nullptr;
                std::cout << cur->data << ' ';
                cur = cur->right;
            }
        }
    }
}
