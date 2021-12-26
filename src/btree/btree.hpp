#pragma once

#include <vector>

#include "errors.h"
#include "kvpair.hpp"

namespace ds {

template <class K, class V>
class BTree {
 private:
  struct Node {
    bool is_leaf;
    std::vector<KVPair<K, V>> elements;
    std::vector<Node*> children;

    Node(bool is_leaf, unsigned int order) : is_leaf(is_leaf) {
      elements.reserve(order + 1);
      children.reserve(order + 2);
    }

    Node(const Node& other)
        : is_leaf(other.is_leaf), elements(other.elements) {}
  };

  unsigned int order;
  Node* root;

 public:
  BTree();

  BTree(unsigned int order);

  BTree(const BTree& other);

  ~BTree();

  const BTree& operator=(const BTree& rhs);

  void clear();

  void insert(const K& key, const V& value);

  V find(const K& key) const;

  V operator[](const K& key) const;

 private:
  void insert(Node* subroot, const KVPair<K, V>& pair);

  V find(const Node* subroot, const K& key) const;

  void split_child(Node* parent, size_t child_idx);

  void clear(Node* subroot);

  Node* copy(const Node* subroot);
};

template <class T, class C>
size_t insertion_idx(const std::vector<T>& elements, const C& val) {
  unsigned bot = 0;
  unsigned top = elements.size();
  while (bot < top) {
    unsigned mid = (top + bot) / 2;
    if (val < elements.at(mid)) {
      top = mid;
    } else if (val > elements.at(mid)) {
      bot = mid + 1;
    } else {
      return mid;
    }
  }
  return bot;
}

template <class K, class V>
BTree<K, V>::BTree() {
  root = nullptr;
  order = 64;
}

template <class K, class V>
BTree<K, V>::BTree(unsigned int order) {
  root = nullptr;
  this->order = order < 3 ? 3 : order;
}

template <class K, class V>
BTree<K, V>::BTree(const BTree& other) {
  clear(root);
  root = copy(other.root);
}

template <class K, class V>
typename BTree<K, V>::Node* BTree<K, V>::copy(const Node* subroot) {
  if (subroot == nullptr) {
    return nullptr;
  }

  Node* new_node = new Node(subroot);
  for (auto& child : subroot->children) {
    new_node->children.push_back(copy(child));
  }
  return new_node;
}

template <class K, class V>
void BTree<K, V>::clear(Node* subroot) {
  if (!subroot->is_leaf) {
    for (auto child : subroot->children) {
      clear(child);
    }
  }
  delete subroot;
}

template <class K, class V>
BTree<K, V>::~BTree() {
  clear();
}

template <class K, class V>
const BTree<K, V>& BTree<K, V>::operator=(const BTree& rhs) {
  if (this != &rhs) {
    clear(root);
    root = copy(rhs.root);
  }
  return *this;
}

template <class K, class V>
void BTree<K, V>::clear() {
  if (root != nullptr) {
    clear(root);
    root = nullptr;
  }
}

template <class K, class V>
V BTree<K, V>::find(const K& key) const {
  if (root == NULL) {
    throw KeyNotFound();
  } else {
    return find(root, key);
  }
}

template <class K, class V>
V BTree<K, V>::operator[](const K& key) const {
  if (root == NULL) {
    throw KeyNotFound();
  } else {
    return find(root, key);
  }
}

template <class K, class V>
V BTree<K, V>::find(const Node* subroot, const K& key) const {
  size_t first_larger_idx = insertion_idx(subroot->elements, key);

  if (first_larger_idx < subroot->elements.size() && first_larger_idx >= 0) {
    if (subroot->elements[first_larger_idx].key == key) {
      return subroot->elements[first_larger_idx].val;
    }
  }
  if (subroot->is_leaf) {
    throw KeyNotFound();
  } else {
    return find(subroot->children[first_larger_idx], key);
  }

  throw KeyNotFound();
}

template <class K, class V>
void BTree<K, V>::insert(const K& key, const V& value) {
  if (root == nullptr) {
    root = new Node(true, order);
  }
  insert(root, KVPair<K, V>(key, value));

  if (root->elements.size() >= order) {
    Node* new_root = new Node(false, order);
    new_root->children.push_back(root);
    split_child(new_root, 0);
    root = new_root;
  }
}

template <class K, class V>
void BTree<K, V>::split_child(Node* parent, size_t child_idx) {
  Node* child = parent->children[child_idx];
  Node* new_left = child;
  Node* new_right = new Node(child->is_leaf, order);

  size_t mid_elem_idx = (child->elements.size() - 1) / 2;
  size_t mid_child_idx = child->children.size() / 2;

  auto child_itr = parent->children.begin() + child_idx + 1;
  auto elem_itr = parent->elements.begin() + child_idx;
  auto mid_elem_itr = child->elements.begin() + mid_elem_idx;
  auto mid_child_itr = child->children.begin() + mid_child_idx;

  parent->elements.insert(elem_itr, child->elements[mid_elem_idx]);
  parent->children.insert(child_itr, new_right);
  new_right->elements.assign(mid_elem_itr + 1, child->elements.end());
  new_right->children.assign(mid_child_itr, child->children.end());
  new_left->elements.assign(child->elements.begin(), mid_elem_itr);
  new_left->children.assign(child->children.begin(), mid_child_itr);
}

template <class K, class V>
void BTree<K, V>::insert(Node* subroot, const KVPair<K, V>& pair) {
  size_t first_larger_idx = insertion_idx(subroot->elements, pair);

  if (subroot->is_leaf) {
    subroot->elements.insert(subroot->elements.begin() + first_larger_idx,
                             pair);
    return;
  } else if (first_larger_idx < subroot->elements.size() &&
             first_larger_idx >= 0) {
    if (subroot->elements[first_larger_idx] == pair) {
      return;
    }
  }
  insert(subroot->children[first_larger_idx], pair);
  if (subroot->children[first_larger_idx]->elements.size() >= order) {
    split_child(subroot, first_larger_idx);
  }
}
};  // namespace ds