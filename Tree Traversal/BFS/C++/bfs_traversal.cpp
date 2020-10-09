#include "tree_node.cpp"
#include <iostream>
#include <queue>
/* bfs traversal: each level will be printed each time */
template <class T>
void bfs_traverse(tree_node<T>* root)
{
    std::queue<tree_node<T>*> q;
    q.push(root);
    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();
        std::cout << cur->data << ' ';
        if (cur->left != nullptr)
            q.push(cur->left);
        if (cur->right != nullptr)
            q.push(cur->right);
    }
}
