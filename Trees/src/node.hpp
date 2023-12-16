template <class T, class V>
class Node
{
private:
    T key;
    V value;
    Node<T, V> *left;
    Node<T, V> *right;
    int height;

public:
    Node(T key, V value);
    Node(Node &node);
    T get_key();
    V get_value();
    Node<T, V> *get_left();
    Node<T, V> *get_right();
    int get_height();
    void set_key(T key);
    void set_value(V value);
    void set_left(Node *child);
    void set_right(Node *child);
    void set_height(int height);
};

template <class T, class V>
Node<T, V>::Node(T key, V value)
{
    this->key = key;
    this->value = value;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 0;
}

template <class T, class V>
Node<T, V>::Node(Node &node)
{
    this->key = node.key;
    this->value = node.value;
    this->left = node.left;
    this->right = node.right;
}

template <class T, class V>
T Node<T, V>::get_key()
{
    return key;
}
template <class T, class V>
V Node<T, V>::get_value()
{
    return value;
}

template <class T, class V>
Node<T, V> *Node<T, V>::get_left()
{
    return left;
}
template <class T, class V>
Node<T, V> *Node<T, V>::get_right()
{
    return right;
}
template <class T, class V>
int Node<T, V>::get_height()
{
    return height;
}

template <class T, class V>
void Node<T, V>::set_key(T key)
{
    this->key = key;
}
template <class T, class V>
inline void Node<T, V>::set_value(V value)
{
}
template <class T, class V>
void Node<T, V>::set_left(Node *child)
{
    this->left = child;
}
template <class T, class V>
void Node<T, V>::set_right(Node *child)
{
    this->right = child;
}

template <class T, class V>
void Node<T, V>::set_height(int height){
    this->height = height;
}
