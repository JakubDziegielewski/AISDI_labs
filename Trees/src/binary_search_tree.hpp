#include "tree.hpp"

template <class T, class V>
class BinarySearchTree : public Tree<T, V>
{
private:
    Node<T, V> *remove(Node<T, V> *node, T key);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree() = default;
    virtual void insert_node(T key, V value);
    std::optional<Node<T, V>> find_node(T key) const;
    virtual void delete_node(T key);
};

template <class T, class V>
BinarySearchTree<T, V>::BinarySearchTree() {}

template <class T, class V>
void BinarySearchTree<T, V>::insert_node(T key, V value)
{
    if (this->root == nullptr)
    {
        this->root = new Node<T, V>(key, value);
        return;
    }
    Node<T, V> *current_node = this->root;
    insert(current_node, key, value);
}
template <class T, class V>
void insert(Node<T, V> *current_node, T key, V value)
{
    bool inserted = false;
    while (!inserted)
    {
        if (key == current_node->get_key())
        {
            current_node->set_value(value);
            inserted = true;
        }
        if (key < current_node->get_key() && current_node->get_left() == nullptr)
        {
            current_node->set_left(new Node<T, V>(key, value));
            inserted = true;
        }
        else if (key > current_node->get_key() && current_node->get_right() == nullptr)
        {
            current_node->set_right(new Node<T, V>(key, value));
            inserted = true;
        }
        else
            current_node = key < current_node->get_key() ? current_node->get_left() : current_node->get_right();
    }
}

template <class T, class V>
std::optional<Node<T, V>> BinarySearchTree<T, V>::find_node(T key) const
{
    Node<T, V> *current_node = this->root;
    while (current_node != nullptr)
    {
        if (key == current_node->get_key())
        {
            return std::optional<Node<T, V>>(*current_node);
        }
        current_node = key < current_node->get_key() ? current_node->get_left() : current_node->get_right();
    }
    return std::nullopt;
}

template <class T, class V>
void BinarySearchTree<T, V>::delete_node(T key)
{
    if (key)
    {
        this->root = remove(this->root, key);
    }
}

template <class T, class V>
Node<T, V> *BinarySearchTree<T, V>::remove(Node<T, V> *node, T key)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (key < node->get_key())
    {
        node->set_left(remove(node->get_left(), key));
    }
    else if (key > node->get_key())
    {
        node->set_right(remove(node->get_right(), key));
    }
    else
    {
        if (node->get_right() == nullptr)
        {
            return node->get_left();
        }
        if (node->get_left() == nullptr)
        {
            return node->get_right();
        }
        Node<T, V> *temp = node;

        node = find_smallest_element(node->get_right());
        node->set_right(remove_smallest_element(temp->get_right()));
        node->set_left(temp->get_left());
        return node;
    }
    return node;
}

template <class T, class V>
Node<T, V> *find_smallest_element(Node<T, V> *node)
{
    if (node->get_left() == nullptr)
    {
        return node;
    }
    return find_smallest_element(node->get_left());
}

template <class T, class V>
Node<T, V> *remove_smallest_element(Node<T, V> *node)
{
    if (node->get_left() == nullptr)
    {
        return node->get_right();
    }
    node->set_left(remove_smallest_element(node->get_left()));
    return node;
}
