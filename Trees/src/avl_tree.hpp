#include "binary_search_tree.hpp"
#include <algorithm>

template <class T, class V>
class AVLTree : public BinarySearchTree<T, V>
{
private:
    Node<T, V> *insert(Node<T, V> *node, T key, V value);

public:
    AVLTree();
    ~AVLTree() = default;
    void insert_node(T key, V value);
    int get_node_height(Node<T, V> *node) const;
    int get_balance(Node<T, V> *node) const;
    Node<T, V> *right_rotate(Node<T, V> *node);
    Node<T, V> *left_rotate(Node<T, V> *node);
};

template <class T, class V>
AVLTree<T, V>::AVLTree() {}

template <class T, class V>
void AVLTree<T, V>::insert_node(T key, V value)
{
    this->root = insert(this->root, key, value);
}

template <class T, class V>
Node<T, V> *AVLTree<T, V>::insert(Node<T, V> *node, T key, V value)
{
    if (node == nullptr)
    {
        node = new Node<T, V>(key, value);
        ;
        return node;
    }

    if (key < node->get_key())
    {
        node->set_left(insert(node->get_left(), key, value));
    }
    else if (key > node->get_key())
    {
        node->set_right(insert(node->get_right(), key, value));
    }
    else
    {
        node->set_value(value);
    }

    node->set_height(std::max(get_node_height(node->get_left()), get_node_height(node->get_right())) + 1);
    int balance = get_balance(node);

    if (balance < -1 && key < node->get_left()->get_key())
    {
        node = right_rotate(node);
        return node;
    }
    if (balance > 1 && key > node->get_right()->get_key())
    {
        node = left_rotate(node);
        return node;
    }

    if (balance < -1 && key > node->get_left()->get_key())
    {
        node->set_left(left_rotate(node->get_left()));
        if (node == this->root)
        {
            this->root = right_rotate(node);
            return this->root;
        }
        return right_rotate(node);
    }
    if (balance > 1 && key < node->get_right()->get_key())
    {
        node->set_right(right_rotate(node->get_right()));
        if (node == this->root)
        {
            this->root = left_rotate(node);
            return this->root;
        }
        return left_rotate(node);
    }

    return node;
}

template <class T, class V>
Node<T, V> *AVLTree<T, V>::right_rotate(Node<T, V> *node)
{
    Node<T, V> *left = node->get_left();
    Node<T, V> *left_right = left->get_right();

    left->set_right(node);
    node->set_left(left_right);

    node->set_height(std::max(get_node_height(node->get_left()), get_node_height(node->get_right())) + 1);
    left->set_height(std::max(get_node_height(left->get_left()), get_node_height(left->get_right())) + 1);
    return left;
}
template <class T, class V>
Node<T, V> *AVLTree<T, V>::left_rotate(Node<T, V> *node)
{
    Node<T, V> *right = node->get_right();
    Node<T, V> *right_left = right->get_left();

    right->set_left(node);
    node->set_right(right_left);

    node->set_height(std::max(get_node_height(node->get_left()), get_node_height(node->get_right())) + 1);
    right->set_height(std::max(get_node_height(right->get_left()), get_node_height(right->get_right())) + 1);
    return right;
}

template <class T, class V>
int AVLTree<T, V>::get_node_height(Node<T, V> *node) const
{
    if (node == nullptr)
    {
        return -1;
    }
    return node->get_height();
}

template <class T, class V>
int AVLTree<T, V>::get_balance(Node<T, V> *node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    return get_node_height(node->get_right()) - get_node_height(node->get_left());
}
