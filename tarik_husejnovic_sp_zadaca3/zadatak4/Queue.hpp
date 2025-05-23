#pragma once
#include <algorithm>
#include <stddef.h>
#include <stdexcept>

template <typename T> class Queue {
public:
  Queue();
  Queue(const Queue &);
  Queue(Queue &&);
  Queue &operator=(const Queue &);
  Queue &operator=(Queue &&);
  ~Queue();
  // Add new element at the end of the queue
  template <typename U> Queue &push(U &&);
  // Pop an element from the begin
  T pop();
  T &front();
  size_t size() const;
  size_t capacity() const;
  bool empty() const;
  bool full() const;
  void clear();

private:
  void copyQueue(const Queue &);
  size_t capacity_{0};
  size_t size_{0};
  T *arr_{nullptr};
  // Index sa koje strane se dodaje
  size_t back_{0};
  // Index sa koje strane se uklanja
  size_t front_{0};
};


template<typename T>
Queue<T>::Queue() : capacity_{10}, arr_{new T[capacity_]} {}

template<typename T>
Queue<T>::Queue(const Queue& other) : capacity_{other.capacity_}, size_{other.size_}, arr_{new T[capacity_]}, back_{other.back_}, front_{other.front_} {
  std::copy(other.arr_, other.arr_ + other.size_, arr_);
}

template<typename T>
Queue<T>::Queue(Queue&& other) : capacity_{other.capacity_}, size_{other.size_}, arr_{other.arr_}, back_{other.back_}, front_{other.front_} {
  other.capacity_=other.size_=other.back_=other.front_=0;
  other.arr_=nullptr;
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
  if(this!=&other){
    delete [] arr_;
    capacity_=other.capacity_; 
    size_=other.size_;
    arr_=new T[capacity_]; 
    back_=other.back_; 
    front_=other.front_;
    std::copy(other.arr_, other.arr_ + size_, arr_);
  }  
  return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) {
  if(this!=&other){
    delete [] arr_;
    capacity_=other.capacity_; 
    size_=other.size_;
    arr_=other.arr_; 
    back_=other.back_; 
    front_=other.front_;
    other.capacity_=other.size_=other.back_=other.front_=0;
    other.arr_=nullptr;
  }
  return *this;
}

template<typename T>
Queue<T>::~Queue() {
  delete [] arr_;
  capacity_=size_=back_=front_=0;
}

template<typename T>
template<typename U>
Queue<T>& Queue<T>::push(U&& element) {
  if(empty()){
    back_=front_=0;
    arr_[front_] = std::forward<U>(element);
    ++size_;
  }
  else if(!full()) {
   back_=(back_+1) % capacity_;
   arr_[back_] = std::forward<U>(element);
  ++size_;
  }
  else {
    T* temp = new T[capacity_ * 2];
    for(size_t i=0;i<size_;++i)
      temp[i]=std::move(arr_[i]);
    delete [] arr_;
    arr_=temp;
    capacity_*=2;
    back_=(back_+1) % capacity_;
    arr_[back_] = std::forward<U>(element);
    ++size_;
  }
  return *this;
}

template<typename T>
T Queue<T>::pop() {
 if(empty()) 
   throw std::out_of_range("Red je prazan!");
 auto temp = std::move(arr_[front_]);
 front_ = (front_+1)%capacity_;
 size_--;
 return temp;
}

template<typename T>
T& Queue<T>::front() { 
  if(empty())
    throw std::out_of_range("Red je prazan!");
  return arr_[front_]; 
}

template<typename T>
size_t Queue<T>::size() const{ return size_; }

template<typename T>
size_t Queue<T>::capacity() const{ return capacity_; }

template<typename T>
bool Queue<T>::empty() const{ return size_ == 0; }

template<typename T>
bool Queue<T>::full() const{ return size_ == capacity_; }

template<typename T>
void Queue<T>::clear() {
  for(size_t i=0;i<size_;++i)
    auto temp = std::move(arr_[i]);
  size_=front_=back_=0;
}
