#include "tree_node.cpp"
#include <iostream>

/* pre order traveral: root, traverse left, traverse right */
template <class T>
void pre_order(tree_node<T>* root)
{
    std::cout << root->data << ' ';

    if (root->left != nullptr)
        pre_order(root->left);

    if (root->right != nullptr)
        pre_order(root->right);   
}
