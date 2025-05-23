#pragma once
#include <algorithm>
#include <stddef.h>
#include <stdexcept>

template <typename T> class Stack {
public:
  Stack();
  Stack(const Stack &);
  Stack(Stack &&);
  Stack &operator=(const Stack &);
  Stack &operator=(Stack &&);
  T pop();
  T &top() const;
  // Savrseno proslijedjivane (forward referenca)
  template <typename U> Stack<T> &push(U &&);
  size_t size() const;
  size_t capacity() const;
  bool empty() const;
  bool full() const;
  ~Stack();
  void clear();
  void resize(size_t newSize);
  bool operator==(const Stack &);
  bool operator!=(const Stack &);

private:
  void realoc();
  size_t capacity_{0};
  size_t size_{0};
  T *arr_{nullptr};
};

template<typename T>
Stack<T>::Stack() : capacity_{100}, size_{0}, arr_{new T[capacity_]} {}

template<typename T>
Stack<T>::Stack(const Stack& other) : capacity_{other.capacity_}, size_{other.size_}, arr_{new T[capacity_]} {
  std::copy(other.arr_, other.arr_+other.size_, arr_);
}

template<typename T>
Stack<T>::Stack(Stack&& other) : capacity_{other.capacity_}, size_{other.size_}, arr_{other.arr_} {
  other.capacity_=other.size_=0;
  other.arr_=nullptr;
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
  if(this!=&other) {
    delete [] arr_;
    capacity_=other.capacity_;
    size_=other.size_;
    arr_=new T[capacity_];
    std::copy(other.arr_, other.arr_ + size_, arr_);
  } 
  return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) {
  if(this!=&other){
    delete [] arr_;
    capacity_=other.capacity_;
    size_=other.size_;
    arr_=other.arr_;
    other.capacity_=other.size_=0;
    other.arr_=nullptr;
  }
  return *this;
}

template<typename T>
T Stack<T>::pop() {
  if(empty())
    throw std::out_of_range("Stack je prazan!");
  auto temp = std::move(arr_[size_-1]);
  size_--;
  return temp;
}

template<typename T>
T& Stack<T>::top() const{ return arr_[size_-1]; }

template<typename T>
template<typename U>
Stack<T>& Stack<T>::push(U&& element) {
  if(full())
    realoc();
  arr_[size_++]=std::forward<U>(element);
  return *this;
}

template<typename T>
size_t Stack<T>::size() const { return size_; }

template<typename T>
size_t Stack<T>::capacity() const { return capacity_; }

template<typename T>
bool Stack<T>::empty() const { return size_==0; }

template<typename T>
bool Stack<T>::full() const{ return size_ == capacity_; }

template<typename T>
Stack<T>::~Stack() {
  delete [] arr_;
  size_=capacity_=0;
}

template<typename T>
void Stack<T>::clear() {
  for(size_t i = 0; i<size_;++i)
    auto temp = std::move(arr_[i]);
  size_=0;
}

template<typename T>
void Stack<T>::resize(size_t newSize) {
  if(newSize<size_){
    for(size_t i=newSize;i<size_;++i)
      pop();
    size_=newSize;
  }
  else if(newSize>size_ && newSize<=capacity_) {
    for(size_t i=size_;i<newSize;++i)
      push(0);
    size_=newSize;
  }
  else if(newSize>capacity_){
    T* temp = new T[newSize];
    std::copy(arr_, arr_+size_,temp);
    delete [] arr_;
    arr_=temp;
    for(size_t i=size_;i<newSize;++i)
      arr_[i]=0;
    size_=capacity_=newSize;
  }
}

template<typename T>
bool Stack<T>::operator==(const Stack& other) {
 if(size_!=other.size_)
   return false;
  for(size_t i=0;i<size_;++i) {
    if(arr_[i]!=other.arr_[i])
      return false;
  }
  return true;
}

template<typename T>
bool Stack<T>::operator!=(const Stack& other) {
  return !(*this==other);
}

template<typename T>
void Stack<T>::realoc() {
  auto temp=new T[capacity_ * 2];
  for(auto i = 0ul; i<size_;i++)
    temp[i]=std::move(arr_[i]);
  delete [] arr_;
  arr_ = temp;
  capacity_*=2;
}
