#include <vector>
#include <iostream>
#include <sstream>

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
            return this->key < rhs.key;
        }

        inline bool operator<(const K &rhs) const
        {
            return this->key < rhs;
        }

        inline friend bool operator<(const K &lhs, const DataPair &rhs)
        {
            return lhs < rhs.key;
        }

        inline bool operator>(const DataPair &rhs) const
        {
            return this->key > rhs.key;
        }

        inline friend bool operator>(const K &lhs, const DataPair &rhs)
        {
            return lhs > rhs.key;
        }

        inline bool operator>(const K &rhs) const
        {
            return this->key > rhs;
        }

        inline bool operator==(const DataPair &rhs) const
        {
            return this->key == rhs.key;
        }

        inline bool operator==(const K &rhs) const
        {
            return this->key == rhs;
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

#include "btree.cpp"