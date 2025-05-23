#pragma once

#include <iostream>
#include <algorithm>

template <typename T>
class Heap{
  private:
    T* heap_;
    size_t capacity_;
    size_t  size_;
    void realoc();
    void maxHeap(size_t);

  public:
    Heap();
    Heap(const Heap&);
    Heap(Heap&&);
    Heap& operator=(const Heap&);
    Heap& operator=(Heap&&);
    ~Heap();
    size_t parent(size_t) const;
    size_t left_child(size_t) const;
    size_t right_child(size_t) const;
    size_t size() const;
    size_t capacity() const;
    bool full() const;
    bool empty() const;
    void insert(T);
    T& max();
    const T& max() const;
    T removeMax();
    void clear();
    void print(size_t) const;
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Heap<U>& heap);
};

template<typename T>
void Heap<T>::realoc() {
  T* temp = new T[2*capacity_];
  std::copy(heap_, heap_+size_, temp);
  delete[] heap_;
  heap_=temp;
  capacity_*=2;
}

template <typename T>
size_t Heap<T>::parent(size_t index) const{
  return (index-1)/2;
}

template <typename T>
size_t Heap<T>::left_child(size_t index) const{
  return (2*index)+1;
}

template <typename T>
size_t Heap<T>::right_child(size_t index) const{
  return (2*index)+2;
}

template <typename T>
void Heap<T>::maxHeap(size_t current) {
  size_t left = left_child(current);
  size_t right = right_child(current);
  size_t largest = current;
  
  if((left<=size_) && (heap_[left] > heap_[largest]))
    largest = left;
  if((right<=size_) && (heap_[right] > heap_[largest]))
    largest = right;

  if(largest != current) {
    T temp = heap_[current];
    heap_[current] = heap_[largest];
    heap_[largest] = temp;
    maxHeap(largest);
  }
}

template<typename T>
Heap<T>::Heap() : capacity_{15}, size_{0}, heap_{new T[capacity_]} {}

template<typename T>
Heap<T>::Heap(const Heap& other) : capacity_{other.capacity_}, size_{other.size_}, heap_{new T[capacity_]} {
  std::copy(other.heap_, other.heap_+other.size_, heap_);
}

template<typename T>
Heap<T>::Heap(Heap&& other) : capacity_{other.capacity_}, size_{other.size_}, heap_{other.heap_} {
  other.capacity_=other.size_=0;
  other.heap_=nullptr;
}

template<typename T>
Heap<T>& Heap<T>::operator=(const Heap& other) {
  if(this!=&other) {
    delete [] heap_;
    capacity_=other.capacity_;
    size_=other.size_;
    heap_=new T[capacity_];
    std::copy(other.heap_, other.heap_ + size_, heap_);
  } 
  return *this;
}

template<typename T>
Heap<T>& Heap<T>::operator=(Heap&& other) {
  if(this!=&other){
    delete [] heap_;
    capacity_=other.capacity_;
    size_=other.size_;
    heap_=other.heap_;
    other.capacity_=other.size_=0;
    other.heap_=nullptr;
  }
  return *this;
}

template <typename T>
Heap<T>::~Heap() {
  clear();
}

template <typename T>
size_t Heap<T>::size() const { return size_;}

template <typename T>
size_t Heap<T>::capacity() const { return capacity_;}

template <typename T>
bool Heap<T>::full() const { return size_ == capacity_;}

template <typename T>
bool Heap<T>::empty() const { return size_ == 0;}

template <typename T>
void Heap<T>::insert(T data) {
  if(full())
    realoc();
  heap_[size_++]=data;
  size_t i = size() - 1;
  while((i!=0) && (heap_[parent(i)] < heap_[i])) {
    std::swap(heap_[parent(i)], heap_[i]);
    i = parent(i);
  }
}

template <typename T>
T& Heap<T>::max() {
  if(empty())
    throw std::out_of_range("Heap je prazan!");
  return heap_[0];
}

template <typename T>
  const T& Heap<T>::max() const{
  if(empty())
    throw std::out_of_range("Heap je prazan!");
  return heap_[0];
}

template <typename T>
T Heap<T>::removeMax() {
  if(empty())
    throw std::out_of_range("Heap je prazan!");
  T maxElem = heap_[0];
  heap_[0] = heap_[--size_];
  maxHeap(0);
  return maxElem;
}

template <typename T>
void Heap<T>::clear() {
  if(!heap_) 
    return;
  delete [] heap_;
  heap_=nullptr;
  capacity_=size_=0;
}

template <typename T>
void Heap<T>::print(size_t k) const{
  std::cout<<heap_[k]<<" ";
  if((k*2+1)<size_)
    print(k*2+1);
  if((k*2+2)<size_)
    print(k*2+2);
}

template <typename T> 
std::ostream& operator<<(std::ostream& out, const Heap<T>& heap) {
  if(!heap.empty())
    heap.print(0);
  return out;
}  
