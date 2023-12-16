#include <optional>
#include <iostream>
#include "node.hpp"

template <class T, class V>
class Tree
{
protected:
    Node<T, V> *root;
    void print_tree(const std::string &prefix, Node<T, V> *node, bool is_left) const;

public:
    Tree();
    virtual ~Tree() = default;
    virtual void insert_node(T key, V value) = 0;
    virtual std::optional<Node<T, V>> find_node(T key) const = 0;
    virtual void delete_node(T key) = 0;
    void print_tree() const;
    Node<T, V> *get_root() const;
};

template <class T, class V>
Tree<T, V>::Tree()
{
    this->root = nullptr;
}

template <class T, class V>
void Tree<T, V>::print_tree(const std::string &prefix, Node<T, V> *node, bool is_left) const
{
    if (node != nullptr)
    {
        std::cout << prefix;

        std::cout << (is_left ? "├──" : "└──");

        // print the value of the nodeclea
        std::cout << node->get_key() << "(" << node->get_value() << ") " << std::endl;

        // enter the next tree level - left and right branch
        print_tree(prefix + (is_left ? "│   " : "    "), node->get_left(), true);
        print_tree(prefix + (is_left ? "│   " : "    "), node->get_right(), false);
    }
}

template <class T, class V>
void Tree<T, V>::print_tree() const
{
    print_tree("", root, false);
}

template <class T, class V>
Node<T, V> *Tree<T, V>::get_root() const
{
    return this->root;
}