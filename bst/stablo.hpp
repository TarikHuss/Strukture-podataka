#pragma once

#include <iostream>
#include <queue>

template <typename T>
struct Node {
  T value;
  Node* left_ = nullptr;
  Node* right_ = nullptr;
};

template <typename T>
class Tree {
public:
  Tree() = default;
  Tree(const Tree& other) = delete;
  Tree(Tree&& other) = default;
  Tree& operator=(const Tree& other) = delete;
  Tree& operator=(Tree&& other) = default;
  ~Tree() {
    clear();
  }

  bool size() const {
    return size_;
  }

  bool empty() const {
    return root_ == nullptr;
  }

  template <typename F>
  void insert(F&& v) {
    auto new_node = new Node<T>{std::forward<F>(v)};
    if (empty()) {
      root_ = new_node;
      size_++;
    } else {
      auto temp = root_;
      while (temp) {
        if (new_node->value < temp->value) {
          // idi lijevo
          if (temp->left_ == nullptr) {
            temp->left_ = new_node;
            size_++;
            return;
          }
          temp = temp->left_;
        } else {
          // veca ili jednaka - idi desno
          if (temp->right_ == nullptr) {
            temp->right_ = new_node;
            size_++;
            return;
          }
          temp = temp->right_;
        }
      }
    }
  }

  const T* find(const T& v) const {
    auto temp = root_;
    while (temp) {
      if (temp->value == v) {
        return &temp->value;
      } else if (temp->value < v) {
        temp = temp->right_;
      } else {
        temp = temp->left_;
      }
    }
    return nullptr;
  }

  void clear() {
    clear_subtree(root_);
    size_ = 0;
    root_ = nullptr;
  }

  void print() const {
    print_subtree(root_);
    std::cout << std::endl;
  }

private:
  static void print_subtree(const Node<T>* root) {
    if (!root)
      return;
    std::cout << root->value << ' ';
    print_subtree(root->left_);
    print_subtree(root->right_);
  }

  static void clear_subtree(Node<T>* root) {
    if (!root)
      return;
    clear_subtree(root->left_);
    clear_subtree(root->right_);
    delete root;
  }

  Node<T>* root_ = nullptr;
  size_t size_ = 0;
};
