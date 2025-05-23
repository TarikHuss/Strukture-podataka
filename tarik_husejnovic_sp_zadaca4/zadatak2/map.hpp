#pragma once 
#include <iostream>

template <typename K, typename V>
struct Node{
  std::pair<K, V> data_;
  Node* left_ = nullptr;
  Node* right_ = nullptr;
  template <typename T>
  Node(K key, T&& value) : data_(std::pair<K, V>(key, value)) {}
};

template <typename K, typename V>
class Map{
  private:
    Node<K, V>* root_ = nullptr;
    size_t size_ = 0;
    
    void insertSubtree(Node<K, V>* other) {
      if (other == nullptr)
        return;
      insert(other->data_.first, other->data_.second);
      insertSubtree(other->left_);
      insertSubtree(other->right_);
    }

    void deleteSubtree(Node<K, V>* node) {
      if(!node)
        return;
      if(node->left_)
        deleteSubtree(node->left_);
      if(node->right_)
        deleteSubtree(node->right_);
      delete node;
    }

    void printMap(Node<K, V>* node){
      if(!node)
        return;
      std::cout<<node->data_.first<<" "<<node->data_.second<<std::endl;
      if(node->left_)
        printMap(node->left_);
      if(node->right_)
        printMap(node->right_);
    }

    void eraseNode(Node<K, V>*& temp) {
      if(temp == nullptr)
        return;
      if(temp->left_ == nullptr && temp->right_ == nullptr) {
        delete temp;
        temp = nullptr;
      }
      else if(temp->right_ == nullptr) {
        auto ptr = temp;
        temp = temp->left_;
        delete ptr;
      }
      else if(temp->left_ == nullptr) {
        auto ptr = temp;
        temp = temp->right_;
        delete ptr;
      }
      else {
        Node<K, V>* previous = nullptr;
        auto current = temp->left_;
        while(current->right_!=nullptr) {
          previous = current;
          current = current->right_;
        }
        temp->data_.first = current->data_.first;
        temp->data_.second = current->data_.second;
        if(previous!=nullptr)
          previous->right_ = current->left_;
        else 
          temp->left_ = current->left_;
        delete current;
      }
      --size_;
    }

  public:
    Map();
    Map(const Map&);
    Map(Map&&);
    Map& operator=(const Map&);
    Map& operator=(Map&&);
    ~Map();

    bool empty() const;
    size_t size() const;

    V& at(const K&);
    const V& at(const K&) const;

    V* find(const K&);
    const V* find(const K&) const;

    V& operator[](const K&);

    template <typename F>
    void insert(const K&, F&&);

    bool erase(const K&);
    void clear();

    void print();
};

template <typename K, typename V>
Map<K, V>::Map() {}

template <typename K, typename V>
Map<K, V>::Map(const Map& other) : size_{other.size_} {
  insertSubtree(other.root_);
}

template <typename K, typename V>
Map<K, V>::Map(Map&& other) : size_{other.size_}, root_{other.root_} {
  other.size_ = 0;
  other.root_ = nullptr;
}

template <typename K, typename V>
Map<K, V>& Map<K, V>::operator=(const Map& other) {
  clear();
  insertSubtree(other.root_);
  size_=other.size_;
  return *this;
}

template <typename K, typename V>
Map<K, V>& Map<K, V>::operator=(Map&& other) {
 clear();
 root_=std::move(other.root_);
 size_=other.size_;
 other.root_=nullptr;
 other.size_=0;
 return *this;
}

template<typename K, typename V>
Map<K, V>::~Map() {
  clear();
}

template <typename K, typename V>
bool Map<K, V>::empty() const { return size_ == 0;}

template <typename K, typename V>
size_t Map<K, V>::size() const { return size_;}

template <typename K, typename V>
V& Map<K, V>::at(const K& key) {
 auto temp = find(key);
 if(temp == nullptr)
  throw std::out_of_range("Kljuc ne postoji!");
 else 
  return *temp;
}

template <typename K, typename V>
const V& Map<K, V>::at(const K& key) const{
 auto temp = find(key);
 if(temp == nullptr)
  throw std::out_of_range("Kljuc ne postoji!");
 else 
  return *temp;
}

template <typename K, typename V>
V* Map<K, V>::find(const K& key) {
  Node<K, V>* temp = root_;
  while(temp != nullptr) {
    if(temp->data_.first == key)
      return &(temp->data_.second);
    else if(temp->data_.first > key)
      temp = temp->left_;
    else 
      temp = temp->right_;
  }
  return nullptr;
}

template <typename K, typename V>
const V* Map<K, V>::find(const K& key) const{
  Node<K, V>* temp = root_;
  while(temp != nullptr) {
    if(temp->data_.first == key)
      return &(temp->data_.second);
    else if(temp->data_.first > key)
      temp = temp->left_;
    else 
      temp = temp->right_;
  }
  return nullptr;
}

template <typename K, typename V>
V& Map<K, V>::operator[](const K& key) {
  if(!find(key)) 
    insert(key, V());
  return at(key);
}

template <typename K, typename V>
template <typename F>
void Map<K, V>::insert(const K& key, F&& value) {
  Node<K, V>* temp = root_;
  Node<K, V>* parent = nullptr;

  while(temp!=nullptr) {
    parent = temp;
    if(temp->data_.first == key)
      throw std::out_of_range("Kljuc vec postoji!");
    else if(temp->data_.first > key)
      temp = temp->left_;
    else 
      temp = temp->right_;
  }
  
  if(parent == nullptr)
    root_ = new Node<K, V>(key, std::forward<F>(value));
  else if(parent->data_.first > key)
    parent->left_ = new Node<K, V>(key, std::forward<F>(value));
  else 
    parent->right_ = new Node<K, V>(key, std::forward<F>(value));

  size_++;
}

template <typename K, typename V>
bool Map<K, V>::erase(const K& key) {
  if (root_ == nullptr) 
    return false;

  Node<K, V>* previous = nullptr;
  Node<K, V>* current = root_;
  
  while (current != nullptr && current->data_.first != key) {
    previous = current;
    if (key < current->data_.first) {
      current = current->left_;
    } else {
      current = current->right_;
    }
  }

  if (current == nullptr)
    return false;

  if (current == root_) {
    eraseNode(root_);
  } else {
    if (previous->left_ == current) {
      eraseNode(previous->left_);
    } else {
      eraseNode(previous->right_);
    }
  }
  
  return true;
}

template <typename K, typename V>
void Map<K, V>::clear() {
  if(!root_)
    return;
  deleteSubtree(root_);
  size_=0;
  root_=nullptr;
}

template<typename K, typename V>
void Map<K, V>::print() {
  printMap(root_);
  std::cout<<std::endl;
}



