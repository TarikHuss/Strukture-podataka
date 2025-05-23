#pragma once

#include <cstddef>
#include <functional>

template <typename T> struct Node {
  Node *prev{nullptr};
  Node *next{nullptr};
  T data;
  Node(const T &element) : data{element}, next{nullptr}, prev{nullptr} {}
  Node(Node *a, Node *b, const T& element) : prev{a}, next{b}, data{element} {}
};

template <typename T> class DoubleLinkedList {
public:
  class Iterator : public std::iterator<std::forward_iterator_tag, T> {
public:
  friend class DoubleLinkedList<T>;

  Iterator() : p_{nullptr} {};
  Iterator(const Iterator& other) : p_{other.p_} {};
  Iterator(Iterator&& other) : p_{other.p_} {
    other.p_=nullptr;
  }
  Iterator& operator=(const Iterator& other) {
    p_=other.p_;
    return *this;
  }
  Iterator& operator=(Iterator&& other) {
    p_ = other.p_;
    other.p_ = nullptr;
    return *this;
  }
  Iterator(Node<T>* ptr) : p_{ptr} {};
  
  Iterator& operator++() {
    if(p_)
      p_=p_->next;
    return *this;
  }

  Iterator operator++(int) {
    auto p = p_;
    if(p_)
       p_=p_->next;
    return p;
  }

  Iterator& operator--() {
    if(p_)
      p_=p_->prev;
    return *this;
  }

  Iterator operator--(int) {
    auto p = p_;
    if(p_)
      p_=p_->prev;
    return p;
  }

  T& operator*() {
    return p_->data;
  }

  T* operator->() {
    return &p_->data;
  }

  bool operator==(const Iterator& other) const{ return p_==other.p_; }

  bool operator!=(const Iterator& other) const{ return p_!=other.p_; }

  Node<T>* node() {
    return p_;
  }

private:
  Node<T>* p_;
};

  DoubleLinkedList();
  DoubleLinkedList(const DoubleLinkedList &);
  DoubleLinkedList(DoubleLinkedList &&);
  DoubleLinkedList &operator=(const DoubleLinkedList &);
  DoubleLinkedList &operator=(DoubleLinkedList &&);
  ~DoubleLinkedList();

  DoubleLinkedList &push_back(const T &);
  DoubleLinkedList &push_front(const T &);
  DoubleLinkedList &push_back(T &&);
  DoubleLinkedList &push_front(T &&);
  DoubleLinkedList &pop_front();
  DoubleLinkedList &pop_back();
  bool empty() const;
  size_t size() const;
  T &front();
  T &back();
  Iterator begin() const{ 
    if(empty())
      return Iterator(nullptr);
    return Iterator(head_); 
  }
  Iterator end() const{ 
    if(empty())
      return Iterator(nullptr);
    return Iterator(tail_->next); 
  }
  const Iterator cbegin() const { 
    if(empty())
      return Iterator(nullptr);
    return Iterator(head_);
  }
  const Iterator cend() const {
    if(empty())
      return Iterator(nullptr);
    return Iterator(tail_->next);
  }
  Iterator rbegin() const{
    if(empty())
      return Iterator(nullptr);
    return Iterator(tail_);
  }
  Iterator rend() const{
    if(empty())
      return Iterator(nullptr);
    return Iterator(head_->prev);
  }
  const Iterator rcbegin() const{
    if(empty())
      return Iterator(nullptr);
    return Iterator(tail_);
  }
  const Iterator rcend() const{
    if(empty())
      return Iterator(nullptr);
    return Iterator(head_->prev);
  }
  void clear();
  Iterator insert(Iterator pos, const T &element);
  Iterator erase(Iterator pos);
  Iterator erase(Iterator beginIt, Iterator endIt);
  void remove_if(std::function<bool(const T &)> &&p);
  void reverse();
  Iterator find(const T &element) const;

private:
  void dealoc();
  Node<T> *head_{nullptr};
  Node<T> *tail_{nullptr};
  size_t size_{0};
};


template<typename T>
DoubleLinkedList<T>::DoubleLinkedList() {}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList& other) : head_{nullptr}, tail_{nullptr}, size_{0} {
  auto temp = other.head_;
  while(temp!=nullptr){
    Node<T>* newNode = new Node<T>{temp->data};
    if(tail_==nullptr)
      head_=tail_=newNode;
    else{
      tail_->next=newNode;
      newNode->prev=tail_;
      tail_=newNode;
    }
    ++size_;
    temp=temp->next;
  }
}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList&& other) : head_{other.head_}, tail_{other.tail_}, size_{other.size_} {
  other.size_ = 0;
  other.head_ = other.tail_ = nullptr;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList& other) {
  if(this!=&other){
    clear(); 
  auto temp = other.head_;
  while(temp!=nullptr){
    Node<T>* newNode = new Node<T>{temp->data};
    if(tail_==nullptr)
      head_=tail_=newNode;
    else{
      tail_->next=newNode;
      newNode->prev=tail_;
      tail_=newNode;
    }
    ++size_;
    temp=temp->next;
  }
  }
  return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(DoubleLinkedList&& other) {
  if(this!=&other) {
    clear();
    head_=other.head_;
    tail_=other.tail_;
    size_=other.size_;
    other.head_=other.tail_=nullptr;
    other.size_=0;
  }
  return *this;
}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
  clear();
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_back(const T& element) {
  auto temp = new Node<T>{tail_, nullptr, element};
  if(empty())
   head_=tail_=temp;
  else {
   tail_=tail_->next=temp; 
  }
  size_++;
  return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_front(const T& element) {
  auto temp = new Node<T>{nullptr, head_, element};
  if(empty())
    head_ = tail_ = temp;
  else {
    head_ = head_->prev = temp;
  }
  size_++;
  return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_back(T&& element) {
  auto temp = new Node<T>{tail_, nullptr, std::move(element)};
  if(empty())
   head_=tail_=temp;
  else {
   tail_=tail_->next=temp; 
  }
  size_++;
  return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_front(T&& element) {
  auto temp = new Node<T>{nullptr, head_, std::move(element)};
  if(empty())
    head_ = tail_ = temp;
  else {
    head_ = head_->prev = temp;
  }
  size_++;
  return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_front() {
  if(empty()) 
    throw std::out_of_range("Nevalidna operacija, prazna lista!");
  else {
    auto temp = head_;
    head_ = head_->next;
    delete temp;
  }
  size_--;
  if(head_)
    head_->prev=nullptr;
  if(empty())
    tail_=nullptr;
  return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_back() {
  if(empty())
    throw std::out_of_range("Nevalidna operacija, prazna lista!");
  else{
    auto temp = tail_->prev;
    delete tail_;
    tail_=temp;
  }
  size_--;
  if(tail_)
    tail_->next=nullptr;
  if(empty())
    head_=nullptr;
  return *this;
}

template<typename T>
bool DoubleLinkedList<T>::empty() const{
  return size_ == 0;
}

template<typename T>
size_t DoubleLinkedList<T>::size() const{
  return size_;
}

template<typename T>
T& DoubleLinkedList<T>::front() {
  if(empty())
    throw std::out_of_range("Nevalidna operacija, prazna lista!");
  return head_->data;
}

template<typename T>
T& DoubleLinkedList<T>::back() {
  if(empty())
    throw std::out_of_range("Nevalidna operacija, prazna lista!");
  return tail_->data;
}

template<typename T>
void DoubleLinkedList<T>::clear() {
  while(head_!=nullptr) {
    auto temp = head_->next;
    delete head_;
    head_=temp;
  }
  tail_ = nullptr;
  size_=0;
}

/*template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::insert(Iterator pos, const T& element) {
  if(empty()) {
    push_back(element);
    return Iterator(tail_);
  }
  Node<T>* temp = new Node<T>{pos.p_, pos.p_->next, element};
  Node<T>* nxt = pos.p_->next;
  pos.p_->next = temp;
  if(nxt!=nullptr)
    nxt->prev=temp;
  else
    tail_=temp;
  std::swap(pos.p_->data, temp->data);
  ++size_;
  return pos;
}
*/

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::insert(Iterator pos, const T& element) {
  if(empty()) {
    push_back(element);
    return Iterator(tail_);
  }
  Node<T>* temp = new Node<T>{element};
  temp->next=pos.p_;
  temp->prev=pos.p_->prev;
  Node<T>* prt = pos.p_->prev;
  pos.p_->prev=temp;
  if(prt!=nullptr)
    prt->next=temp;
  else
    head_=temp;
  ++size_;
  return Iterator(temp);
}


template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(Iterator pos) {
  if(pos.p_->next==nullptr) {
    pop_back();
    return Iterator(tail_);
  }  
  Node<T>* eraseNode = pos.p_;
  Node<T>* nextNode = pos.p_->next;
  Node<T>* prevNode = pos.p_->prev;

  if(prevNode)
    prevNode->next=nextNode;
  else
    head_=nextNode;
  if(nextNode)
    nextNode->prev=prevNode;
  else
    tail_=prevNode;

  delete eraseNode;
  --size_;
  return Iterator(nextNode);
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(Iterator beginIt, Iterator endIt) {
  Node<T>* prv = beginIt.p_->prev;
  Node<T>* nxt = endIt.p_;
  if(prv)
    prv->next=nxt;
  else
    head_=nxt;
  if(nxt)
    nxt->prev=prv;
  else
    tail_=prv;
  while(beginIt.p_!=endIt.p_) {
    auto temp = beginIt.p_->next;
    delete beginIt.p_;
    beginIt.p_=temp;
    --size_; 
  }
  return nxt;
}

template<typename T>
void DoubleLinkedList<T>::remove_if(std::function<bool(const T& a)> &&p) {
  Iterator it = begin();
  while(it!=end()) {
    if(p(*it))
      it=erase(it);
    else
      ++it;
  }
}

template <typename T>
void DoubleLinkedList<T>::reverse() {
  if (empty() || size_ == 1) 
    return;
  Iterator beginIt = begin();
  Iterator endIt = tail_; 
  while (beginIt.p_->prev != endIt.p_) {
    if(beginIt == endIt)
      return;
    std::swap(*beginIt, *endIt);
    ++beginIt;
    --endIt;
  }
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::find(const T& element) const{
  if(empty())
    return Iterator(end());
  for(Iterator it = begin();it!=end();++it) {
    if(*it==element)
      return it;
  }
  return Iterator(end());
}

