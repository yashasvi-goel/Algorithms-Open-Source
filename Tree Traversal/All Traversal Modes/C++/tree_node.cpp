#ifndef _TREE_NODE_CPP
#define _TREE_NODE_CPP
template <class T>
class tree_node
{
public:
    tree_node(T data, tree_node<T>* left = nullptr, tree_node<T>* right = nullptr)
        : data(data), left(left), right(right)
    {}
    tree_node(T data, tree_node<T>& left, tree_node<T>& right)
        : data(data), left(&left), right(&right)
    {}

    T data;
    tree_node *left, *right;
};

#endif // ifndef _TREE_NODE_CPP