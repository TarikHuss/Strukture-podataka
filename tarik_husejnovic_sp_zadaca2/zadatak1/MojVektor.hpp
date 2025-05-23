#pragma once
#include <initializer_list>
#include <iterator>

template <typename T>
class MojVektor {
  public:
class Iterator {
    public:
  Iterator();
  Iterator(T*);
  Iterator(const Iterator&);
  Iterator(Iterator&&);
  Iterator& operator=(const Iterator& other) {
    ptr_=other.ptr_;
    return *this;
  }
  Iterator& operator=(Iterator&& other) {
    ptr_=other.ptr_;
    other.ptr_=nullptr;
    return *this;
  }
  
  T* operator->();
  T& operator*();
  bool operator==(const Iterator&); 
  bool operator!=(const Iterator&);
  Iterator& operator++() {
    ++ptr_;
    return *this;
  }
  Iterator& operator--() {
    --ptr_;
    return *this;
  }
  Iterator operator+(size_t n) {return Iterator(ptr_+n);}
  Iterator operator-(size_t n) {return Iterator(ptr_-n);}
  size_t operator-(const Iterator&);
  T* operator[](size_t);
  bool operator<(const Iterator&);

  private:
  T* ptr_;
  };

  MojVektor();
  MojVektor(const std::initializer_list<T>&);
  MojVektor(const MojVektor&);
  MojVektor& operator=(const MojVektor&);
  MojVektor(MojVektor&&);
  MojVektor& operator=(MojVektor&&);
  ~MojVektor();
  MojVektor& push_back(const T&);
  MojVektor& push_front(const T&);
  MojVektor& push_back(T&&);
  MojVektor& push_front(T&&);
  size_t size() const;
  T& at(size_t) const;
  T& operator[](size_t) const;
  void clear();
  void resize(size_t newSize, const T& difference_value);
  MojVektor& pop_back();
  MojVektor& pop_front();
  T& back() const;
  T& front() const;
  bool empty() const;
  size_t capacity() const;
  bool operator==(const MojVektor&) const;
  bool operator!=(const MojVektor&) const;
  bool full() const;
  MojVektor subvector(Iterator begin, Iterator end);
  Iterator begin() const { return Iterator(arr_);}
  Iterator end() const { return Iterator(arr_+size_);}
  Iterator find(const T& value) const {
    if(empty())
      return end();
    for(auto it = begin(); it!=end();++it) {
      if(*it==value)
        return Iterator(it);
    }
    return end();
  }
  Iterator erase(Iterator pos) {
   if(pos!=end()){
      for(MojVektor<T>::Iterator it = pos;it != end()-1;++it) {
        *it=*(it+1);
      } 
      --size_;
    }
    return Iterator(pos);
  } 
  Iterator insert(Iterator pos,const T& value) {
    if(pos==end())
      throw std::out_of_range("Nevalidna operacija");
    size_t n = pos - begin();
    if(full())
       realoc();
    for(size_t i = size();i>n;--i)
      arr_[i]=arr_[i-1];
    arr_[n]=value;
    ++size_;
    return Iterator(begin()+n);
  }
  Iterator insert(Iterator pos, T&& value){
     if(pos==end())
      throw std::out_of_range("Nevalidna operacija");
    size_t n = pos - begin();
    if(full())
       realoc();
    for(size_t i = size();i>n;--i)
      arr_[i]=arr_[i-1];
    arr_[n]=std::move(value);
    ++size_;
    return  Iterator(begin() + n);
  }
  Iterator rbegin() const {
    return Iterator(end()-1);
  }
  Iterator rend() const {
    return Iterator(begin()-1);
  }
  Iterator erase(Iterator beginIt, Iterator endIt) {
    size_t n = endIt-beginIt;
    for(MojVektor<T>::Iterator it = endIt;it!=end();++it)
      *(it-n)=*it;
    size_-=n;
    return Iterator(beginIt);
  }
  void rotate();
  void rotate(Iterator beginIt, Iterator endIt);

  T* data();

  private:
  void realoc();
  size_t capacity_;
  size_t size_;
  T* arr_;
};

template<typename T>
std::ostream& operator<<(std::ostream&, const MojVektor<T>&);

template<typename T>
MojVektor<T>::MojVektor() : capacity_{10}, size_{0}, arr_{new T[capacity_]} {}

template<typename T>
MojVektor<T>::MojVektor(const std::initializer_list<T>& lista) : capacity_{lista.size()}, size_{capacity_} {
  arr_ = new T[capacity_];
  std::copy(lista.begin(), lista.end(), arr_);
}

template<typename T>
MojVektor<T>::MojVektor(const MojVektor& other) : capacity_{other.capacity_}, size_{other.size_}, arr_{new T[capacity_]} {
  std::copy(other.arr_, other.arr_ + other.size_, arr_);
}

template<typename T>
MojVektor<T>& MojVektor<T>::operator=(const MojVektor& other) {
  if(this!=&other){
    delete [] arr_;
    capacity_=other.capacity_;
    size_=other.size_;
    arr_=new T[capacity_];
    std::copy(other.arr_, other.arr_ + size_, arr_);
  }
  return *this;
}

template<typename T>
MojVektor<T>::MojVektor(MojVektor&& other) : capacity_{other.capacity_}, size_{other.size_}, arr_{other.arr_} {
  other.capacity_ = 0; 
  other.size_ = 0;
  other.arr_ = nullptr;
}

template<typename T>
MojVektor<T>& MojVektor<T>::operator=(MojVektor&& other) {
  if(this!=&other){
    delete [] arr_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    arr_ = other.arr_;
    other.capacity_ = 0; 
    other.size_ = 0;
    other.arr_ = nullptr;
  }
  return *this;
}

template<typename T>
MojVektor<T>::~MojVektor() {
  capacity_= 0;
  size_= 0;
  delete [] arr_;
}

template<typename T>
MojVektor<T>& MojVektor<T>::push_back(const T& element) {
  if(full())
    realoc();
  arr_[size_++]=element;
  return *this;
}

template<typename T>
MojVektor<T>& MojVektor<T>::push_front(const T& element) {
  T* arr = new T[capacity_];
  if(full())
    arr=new T[capacity_*=2];
  std::copy(arr_,arr_+size_, arr+1);
  delete [] arr_;
  arr_=arr;
  arr_[0]=element;
  ++size_;
  return *this;
}

template<typename T>
MojVektor<T>& MojVektor<T>::push_back(T&& element) {
  if(size_==capacity_)
    realoc();
  arr_[size_++]=std::move(element);
  return *this;
}

template<typename T>
MojVektor<T>& MojVektor<T>::push_front(T&& element) {
  T* arr = new T[capacity_];
  if(full())
    arr=new T[capacity_*=2];
  std::copy(arr_,arr_+size_, arr+1);
  delete [] arr_;
  arr_=arr;
  arr_[0]=std::move(element);
  ++size_;
  return *this;
}


template<typename T>
size_t MojVektor<T>::size() const {return size_;}

template<typename T>
T& MojVektor<T>::at(size_t index) const {
  if(index>=size_)
    throw std::out_of_range("Indeks izvan  granica!");
  return arr_[index];
}

template<typename T>
T& MojVektor<T>::operator[](size_t index) const { return arr_[index];}

template<typename T>
void MojVektor<T>::clear() {
  delete [] arr_;
  arr_=nullptr;
  size_=capacity_=0;
}

template <typename T>
void MojVektor<T>::resize(size_t newSize, const T& difference_value) {
  if(newSize<size_) {
    for(int i = newSize; i<size_;++i)
      pop_back();
    size_=newSize;
  }
  else if(newSize>size_ && newSize<capacity_) {
    for(int i = size_;i<newSize;++i)
      push_back(difference_value);
    size_=newSize;
  } 
  else if(newSize>capacity_) {
    T* temp = new T[newSize];
    std::copy(arr_, arr_+size_,temp);
    delete [] arr_;
    arr_=temp;
    for(size_t i = size_;i<newSize;++i)
      arr_[i]=difference_value;
    capacity_=size_=newSize;
  }
}

template<typename T>
MojVektor<T>& MojVektor<T>::pop_back() {
  if(empty())
    throw std::out_of_range("Prazan kontejner!");
  auto temp = std::move(back());
  --size_;
  return *this;
}

template<typename T>
MojVektor<T>& MojVektor<T>::pop_front() {
  if(empty())
    throw std::out_of_range("Prazan kontejner!");
  T* arr=new T[capacity_];
  std::copy(arr_+1, arr_+size_,arr);
  delete []arr_;
  arr_=arr;
  --size_;
  return *this;
}

template<typename T>
T& MojVektor<T>::back() const{
  if(empty())
    throw std::out_of_range("Vektor je prazan!");
  return arr_[size_ - 1];
}

template<typename T>
T& MojVektor<T>::front() const{
  if(empty())
    throw std::out_of_range("Vektor je prazan!");
  return arr_[0];
}

template<typename T>
bool MojVektor<T>::empty() const {return size_==0;}

template<typename T>
size_t MojVektor<T>::capacity() const {return capacity_;}

template<typename T>
bool MojVektor<T>::operator==(const MojVektor& other) const{
  if(size_!=other.size_)
    return false;
  else { 
    for(size_t i = 0;i<size_;++i) { 
      if (arr_[i]!=other.arr_[i]) 
        return false;
    }
  return true;
  }
}

template<typename T>
bool MojVektor<T>::full() const {
  if(size_==capacity_)
    return true;
  return false;
}

template<typename T>
MojVektor<T> MojVektor<T>::subvector(Iterator begin, Iterator end) {
  MojVektor v;
  for(MojVektor<T>::Iterator it=begin;it!=end;++it)
    v.push_back(*it);
  v.size_=end-begin;
  return v;
}

template<typename T>
void MojVektor<T>::rotate() {
  if(!empty()){
    for(size_t i = 0, j = size_-1;i<j;++i,--j)
      std::swap(arr_[i],arr_[j]);
  }
}

template<typename T>
void MojVektor<T>::rotate(Iterator beginIt, Iterator endIt) {
  if(!empty()){
    for(MojVektor<T>::Iterator it1=beginIt, it2=endIt-1;it1<it2;++it1,--it2)
    std::swap(*it1,*it2); 
  }
}

template<typename T>
T* MojVektor<T>::data() {return arr_;}

template<typename T>
std::ostream& operator<<(std::ostream& out, const MojVektor<T>& vec) {
  out<<"{";
  if(!vec.empty()) {
    for(size_t i = 0;i<vec.size()-1;++i)
      out<<vec[i]<<", ";
    out<<vec[vec.size()-1];
  } 
  out<<"}";
  return out;
}

template<typename T>
void MojVektor<T>::realoc() {
  auto temp=new T[capacity_ * 2];
  for(auto i = 0ul; i<size_;i++)
    temp[i]=std::move(arr_[i]);
  delete [] arr_;
  arr_ = temp;
  capacity_*=2;
}


template<typename T>
MojVektor<T>::Iterator::Iterator() : ptr_{nullptr} {}

template<typename T>
MojVektor<T>::Iterator::Iterator(T* ptr) : ptr_{ptr} {}

template<typename T>
MojVektor<T>::Iterator::Iterator(const Iterator& other) : ptr_{other.ptr_} {
}

template<typename T>
MojVektor<T>::Iterator::Iterator(Iterator&& other) : ptr_{other.ptr_} {
  other.ptr_=nullptr;
}

template<typename T>
T* MojVektor<T>::Iterator::operator->() {return ptr_;}

template<typename T>
T& MojVektor<T>::Iterator::operator*() {return *ptr_;}

template<typename T>
bool MojVektor<T>::Iterator::operator==(const Iterator& other) {
  return ptr_==other.ptr_;
}

template<typename T>
bool MojVektor<T>::Iterator::operator!=(const Iterator& other) {
 return ptr_!=other.ptr_;
}

template <typename T>
size_t MojVektor<T>::Iterator::operator-(const Iterator& other) {
  return ptr_-other.ptr_;
}

template<typename T>
T* MojVektor<T>::Iterator::operator[](size_t n) { return ptr_+n;}

template<typename T>
bool MojVektor<T>::Iterator::operator<(const Iterator& other) {return ptr_<other.ptr_;}
