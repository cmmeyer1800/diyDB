#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

template <class K, class V>
class BTree
{
  private:
    /**
     * A fancy key-value pair which acts as elements in the BTree.
     * Can be compared with <, >, ==. Additionally they can be compared against
     * a K with <, > and == based on its key.
     * */
    struct DataPair
    {
        K key;
        V value;

        DataPair(K key, V value) : key(key), value(value){}

        inline bool operator<(const DataPair &rhs) const
        {
            return key < rhs.key;
        }

        inline bool operator<(const K &rhs) const
        {
            return key < rhs;
        }

        inline friend bool operator<(const K &lhs, const DataPair &rhs)
        {
            return lhs < rhs.key;
        }

        inline bool operator>(const DataPair &rhs) const
        {
            return key > rhs.key;
        }

        inline friend bool operator>(const K &lhs, const DataPair &rhs)
        {
            return lhs > rhs.key;
        }

        inline bool operator>(const K &rhs) const
        {
            return key > rhs;
        }

        inline bool operator==(const DataPair &rhs) const
        {
            return key == rhs.key;
        }

        inline bool operator==(const K &rhs) const
        {
            return key == rhs;
        }

        inline friend bool operator==(const K &lhs, const DataPair &rhs)
        {
            return lhs == rhs.key;
        }
    };

    struct BTreeNode
    {
        bool is_leaf;
        std::vector<DataPair> elements;
        std::vector<BTreeNode *> children;

        BTreeNode(bool is_leaf, unsigned int order) : is_leaf(is_leaf)
        {
            elements.reserve(order + 1);
            children.reserve(order + 2);
        }

        BTreeNode(const BTreeNode &other):is_leaf(other.is_leaf), elements(other.elements){}

        inline friend std::ostream &operator<<(std::ostream &out,
                                               const BTreeNode &n)
        {
            std::string node_str;
            node_str.reserve(2 * (4 * n.elements.size() + 1));
            for (auto &elem : n.elements)
            {
                std::stringstream temp;
                temp << elem.key;
                node_str += "| ";
                node_str += temp.str();
                node_str += " ";
            }
            if (!n.elements.empty())
            {
                node_str += "|";
            }
            node_str += "\n";
            for (auto &child : n.children)
            {
                if (child == nullptr)
                {
                    node_str += "N   ";
                }
                else
                {
                    node_str += "*   ";
                }
            }
            if (n.children.empty())
            {
                node_str += "no children";
            }

            out << node_str;
            return out;
        }
    };

    unsigned int order;

    BTreeNode *root;

  public:

    BTree();

    BTree(unsigned int order);

    BTree(const BTree &other);

    bool is_valid(unsigned int order = 64) const;

    ~BTree();

    const BTree &operator=(const BTree &rhs);

    void clear();

    void insert(const K &key, const V &value);

    V find(const K &key) const;

  private:

    void insert(BTreeNode *subroot, const DataPair &pair);

    V find(const BTreeNode *subroot, const K &key) const;

    void split_child(BTreeNode *parent, size_t child_idx);

    void clear(BTreeNode *subroot);

    BTreeNode *copy(const BTreeNode *subroot);

    bool is_valid(const BTreeNode *subroot, std::vector<DataPair> &data, unsigned int order) const;
};

template <class T, class C>
size_t insertion_idx(const std::vector<T> &elements, const C &val)
{
    int lo = 0;
    int hi = elements.size();
    while (lo < hi)
    {
        int mid = (lo + hi) / 2;
        if (elements[mid] > val)
            hi = mid;
        else if (elements[mid] < val)
            lo = mid + 1;
        else
            return mid;
    }
    return lo;
}

template <class K, class V>
V BTree<K, V>::find(const K &key) const
{
    return root == nullptr ? V() : find(root, key);
}

template <class K, class V>
V BTree<K, V>::find(const BTreeNode *subroot, const K &key) const
{
    size_t first_larger_idx = insertion_idx(subroot->elements, key);
    if (first_larger_idx < subroot->elements.size() && subroot->elements[first_larger_idx].key == key)
        return subroot->elements[first_larger_idx].value;
    if (subroot->is_leaf)
        return V();
    else
        return find(subroot->children[first_larger_idx], key);

    return V();
}

template <class K, class V>
void BTree<K, V>::insert(const K &key, const V &value)
{
    /* Make the root node if the tree is empty. */
    if (root == nullptr)
    {
        root = new BTreeNode(true, order);
    }
    insert(root, DataPair(key, value));
    /* Increase height by one by tossing up one element from the old
     * root node. */
    if (root->elements.size() >= order)
    {
        BTreeNode *new_root = new BTreeNode(false, order);
        new_root->children.push_back(root);
        split_child(new_root, 0);
        root = new_root;
    }
}

template <class K, class V>
void BTree<K, V>::split_child(BTreeNode *parent, size_t child_idx)
{
    BTreeNode *child = parent->children[child_idx];
    BTreeNode *new_left = child;
    BTreeNode *new_right = new BTreeNode(child->is_leaf, order);

    size_t mid_elem_idx = (child->elements.size() - 1) / 2;
    size_t mid_child_idx = child->children.size() / 2;

    auto child_itr = parent->children.begin() + child_idx + 1;
    auto elem_itr = parent->elements.begin() + child_idx;
    auto mid_elem_itr = child->elements.begin() + mid_elem_idx;
    auto mid_child_itr = child->children.begin() + mid_child_idx;

    parent->children.insert(child_itr, new_right);
    parent->elements.insert(elem_itr, child->elements[mid_elem_idx]);
    new_right->children.assign(mid_child_itr, child->children.end());
    new_right->elements.assign(mid_elem_itr + 1, child->elements.end());
    new_left->children.assign(child->children.begin(), mid_child_itr);
    new_left->elements.assign(child->elements.begin(), mid_elem_itr);
}

template <class K, class V>
void BTree<K, V>::insert(BTreeNode *subroot, const DataPair &pair)
{
    size_t first_larger_idx = insertion_idx(subroot->elements, pair);

    if (subroot->is_leaf)
    {
        subroot->elements.insert(subroot->elements.begin() + first_larger_idx, pair);
        return;
    }
    if (first_larger_idx < subroot->elements.size() && subroot->elements[first_larger_idx] == pair)
        return;
    else
    {
        BTreeNode *o = subroot->children[first_larger_idx];
        insert(o, pair);
        if (o->elements.size() >= order)
        {
            split_child(subroot, first_larger_idx);
        }
    }
}

template <class K, class V>
BTree<K, V>::BTree()
{
    root = nullptr;
    order = 64;
}

template <class K, class V>
BTree<K, V>::BTree(unsigned int order)
{
    root = nullptr;
    this->order = order < 3 ? 3 : order;
}

template <class K, class V>
BTree<K, V>::BTree(const BTree& other)
{
    clear(root);
    root = copy(other.root);
}

template <class K, class V>
typename BTree<K, V>::BTreeNode* BTree<K, V>::copy(const BTreeNode* subroot)
{
    if (subroot == nullptr) {
        return nullptr;
    }

    BTreeNode* new_node = new BTreeNode(subroot);
    for (auto& child : subroot->children) {
        new_node->children.push_back(copy(child));
    }
    return new_node;
}

template <class K, class V>
bool BTree<K, V>::is_valid(unsigned int order /* = 64 */) const
{
    if (root == nullptr)
        return true;
    std::vector<DataPair> data;
    return is_valid(root, data, order)
           && std::is_sorted(data.begin(), data.end());
}

template <class K, class V>
bool BTree<K, V>::is_valid(const BTreeNode* subroot, std::vector<DataPair>& data,
                           unsigned int order) const
{
    if (subroot->elements.size() >= order) {
        return false;
    }

    auto first = subroot->elements.begin();
    auto last = subroot->elements.end();
    bool ret = subroot->children.size() == subroot->elements.size() + 1;
    if (!subroot->is_leaf) {
        auto curr_child = subroot->children.begin();
        ret &= is_valid(*curr_child, data, order);
        curr_child++;
        for (auto elem = first; ret && elem != last; elem++) {
            data.push_back(*elem);
            ret &= is_valid(*curr_child, data, order);
            curr_child++;
        }
    } else {
        data.insert(data.end(), first, last);
        ret = true;
    }
    return ret;
}

template <class K, class V>
void BTree<K, V>::clear(BTreeNode* subroot)
{
    if (!subroot->is_leaf) {
        for (auto child : subroot->children) {
            clear(child);
        }
    }
    delete subroot;
}

template <class K, class V>
BTree<K, V>::~BTree()
{
    clear();
}

template <class K, class V>
const BTree<K, V>& BTree<K, V>::operator=(const BTree& rhs)
{
    if (this != &rhs) {
        clear(root);
        root = copy(rhs.root);
    }
    return *this;
}

template <class K, class V>
void BTree<K, V>::clear()
{
    if (root != nullptr) {
        clear(root);
        root = nullptr;
    }
}