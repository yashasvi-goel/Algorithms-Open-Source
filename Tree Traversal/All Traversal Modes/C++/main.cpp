#include "pre_order_traversal.cpp"
#include "post_order_traversal.cpp"
#include "in_order_traversal.cpp"
#include "bfs_traversal.cpp"
#include "tree_node.cpp"
#include <iostream>

/* post order traversal: traverse left, travers right, root */
template <class T>
void post_order(tree_node<T>* root)
{
    if (root->left != nullptr)
        post_order(root->left);

    if (root->right != nullptr)
        post_order(root->right);   

    std::cout << root->data << ' ';
}



int main()
{
    /*
                            4
                        2       6
                       1  3    5  7
    */
   tree_node<int> one(1), three(3), two(2, one, three), five(5), seven(7), six(6, five, seven), four(4, two, six);
   std::cout << "In Order: ";
   in_order(&four);
   std::cout << std::endl << "In Order Iterative: ";
   in_order_iterative(&four);
   std::cout << std::endl << "Morris: ";
   morris_traversal(&four);
   std::cout << std::endl << "Post Order: ";
   post_order(&four);
   std::cout << std::endl << "Pre Order: ";
   pre_order(&four);
   std::cout << std::endl << "BFS: ";
   bfs_traverse(&four);
}