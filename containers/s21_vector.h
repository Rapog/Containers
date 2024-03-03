#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <iostream>
#include <memory>
#include <algorithm>
#include <cstring>
// #include <array>
#include <cmath>
#include <type_traits>


namespace s21{

  // template <typename T>
  //   struct vector{
      
  // };

  template <typename T>
  class vector{
  public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = T*;
    using const_iterator = const T*;
    using size_type = size_t;


  vector(): arr_(nullptr), size_(0), capacity_(0) {
    // std::cout << "nice"<<std::endl;
  }

  vector(size_type n): arr_(new value_type[n]), size_(n), capacity_(n){
    // std::cout << "niceeee n"<<std::endl;
  } 

  // vector(std::initializer_list<value_type> const &items)//: vector(items.size())
  // {
  //   size_t sz = items.size();
  //   size_ = sz;
  //   capacity_ = sz;
  //   arr_ = new value_type[capacity_];
  //   auto it = items.begin();
  //   for(size_t i = 0; i < sz; ++i, ++it){
  //     arr_[i]= *it;
  //     // arr_[i] = std::move(*(items.begin() + i));
  //   };
  //   // size_ = sz;
  //   // capacity_ = sz;
  //   std::cout << "niceeee il"<<std::endl;
  // }

  vector(std::initializer_list<value_type> const &items) {
      size_t sz = items.size();
      size_ = sz;
      capacity_ = sz;
      arr_ = new value_type[capacity_];
      auto it = items.begin();
      for(size_t i = 0; i < sz; ++i, ++it){
        new (arr_ + i) value_type(*it);
      }
      // std::cout << "niceeee il"<<std::endl;
    }

  // vector(const vector &other): arr_(new value_type[other.size()]),size_(other.size()), capacity_(other.capacity()){
  //   // arr_= new value_type(const other.size())
  //   std::memcpy(arr_, other.arr_, sizeof(T) * size_);
  //   std::cout << "niceeee &oth"<<std::endl;
  // }

  vector(const vector &other): arr_(new value_type[other.size()]), size_(other.size()), capacity_(other.capacity()) {
      for (size_t i = 0; i < size_; ++i) {
        new (arr_ + i) value_type(other.arr_[i]);
      }
      // std::cout << "niceeee &oth"<<std::endl;
    }

  vector(vector &&other):vector(){
    std::swap(other.arr_, arr_);
    std::swap(other.size_, size_);
    std::swap(other.capacity_, capacity_);
  }

  ~vector(){
    // if (arr_) {delete[](arr_);}
    // for(size_t i = size_-1; i >= 0; --i){
    //     if(arr_)
    //      {
    //       arr_[i].~value_type();
    //       }
    //   }
      if (arr_) {delete[](arr_);}
      // delete[] arr_;
    size_ = 0;
    capacity_ = 0;
    // std::cout << "so nice dest"<<std::endl;
  }

  vector operator=(vector &&other){
    if (&other == this) return *this;
    std::swap(other.arr_, arr_);
    std::swap(other.size_, size_);
    std::swap(other.capacity_, capacity_);
    // if(other.arr_) {
      delete[](other.arr_);
      // }
    other.arr_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
    return *this;
  }

  reference operator[](size_type n){
    return *(arr_ + n);
  }

  reference at(size_type n){
    if (n >= size_ ) {
      throw std::out_of_range("Sega mega drive");
    }
    return *(arr_ + n);
  }

  const reference front() {
    return *(arr_);
  }

  const reference back() {
    return *(arr_ + size_ - 1);
  }

  T* data(){
    if (size_ == 0) {
      throw std::logic_error("There is no memory");
    }
    return arr_;
  }
  
iterator begin(){
  return arr_;
}

iterator end(){
  return arr_ + size_;
}

bool empty() const noexcept{
  return size_? false: true;
}

size_type size() const noexcept{
  return size_;
}

size_type max_size() noexcept{
  // size_t p = 0;
  // if (sizeof(void*) == 8) { // && !std::is_same_v<T, char>) {
    // p = std::pow(2,64)/(sizeof(T)*2);
  // }
  // else if (sizeof(void*) == 8 && std::is_same_v<T, char>){
  //   p = std::pow(2,64)/(sizeof(T)*2);
  // }
  // else if (sizeof(void*) == 4) {
  //   p = std::pow(2,32)/sizeof(T);
  // }
  return static_cast<size_t>(std::pow(2,64)/(sizeof(T)*2)) - 1;
}

// void reserve(size_type size){
//   value_type* new_arr = new value_type[size];
//   std::memcpy(new_arr, arr_, sizeof(T) * size_);
//   // value_type* tmp = arr_;
//   delete[](arr_);
//   arr_ = new_arr;
//   // delete[](tmp);
//   capacity_ = size;
// }

void reserve(size_type size) {
      value_type* new_arr = new value_type[size];
      for (size_t i = 0; i < size_; ++i) {
        new (new_arr + i) value_type(std::move(arr_[i]));
        arr_[i].~value_type();
      }
      delete[] arr_;
      arr_ = new_arr;
      capacity_ = size;
    }

size_type capacity() const noexcept{
  return capacity_;
}

// void shrink_to_fit(){
//   if (capacity_ > size_) {
//     value_type* new_arr = new value_type[size_];
//     std::memcpy(new_arr, arr_, sizeof(T) * size_);
//     delete[](arr_);
//     arr_ = new_arr;
//     capacity_ = size_;
//   }
// }

// void clear(){
//   size_ = 0;
// }

void shrink_to_fit() {
  if (capacity_ > size_) {
    value_type* new_arr = new value_type[size_];
    for (size_t i = 0; i < size_; ++i) {
      new (new_arr + i) value_type(std::move(arr_[i]));
      arr_[i].~value_type();
    }
    delete[] arr_;
    arr_ = new_arr;
    capacity_ = size_;
  }
}

void clear() {
  for (size_t i = 0; i < size_; ++i) {
    arr_[i].~value_type();
  }
  size_ = 0;
}

// iterator insert(iterator pos, const_reference value){
//   // size_t new_capacity = capacity_;
//   // std::cout << capacity_ << " cap"<<"\n";
//   if (size_ + 1 > capacity_) {
//     capacity_ *= 2;
//   }
//   // std::cout << capacity_ << " cap"<<"\n";
//   value_type* new_arr = new value_type[capacity_];
//   size_t p = pos - arr_;
//   std::memcpy(new_arr, arr_, sizeof(T) * (p));
//   new_arr[p] = value;
//   // std::cout << new_arr[p] << " funk"<<"\n";
//   std::memcpy((new_arr + p + 1), (arr_+ p), sizeof(T) *(size_ - p));
//   delete[](arr_);
//   arr_ = new_arr;
//   size_+=1;
  
//   return (arr_ + p);
// }

iterator insert(iterator pos, const_reference value) {
  size_t p = pos - arr_;
  if (p > size_) {
    std::logic_error("Hoocked from vector");
  }
  if (size_ + 1 > capacity_) {
    reserve(capacity_ * 2);
  }
  for (size_t i = size_; i > p; --i) {
    new (arr_ + i) value_type(std::move(arr_[i - 1]));
    arr_[i - 1].~value_type();
  }
  new (arr_ + p) value_type(value);
  ++size_;
  return (arr_ + p);
}

template <class... Args>
iterator insert_many(const_iterator pos, Args&&... args){
  size_t p = pos - arr_;
  // auto it = args.begin();
  // for(size_type i = 0; i < args.size(); ++i, ++it){
    (insert(const_cast<T*>(pos), args), ...);
  // }
  return (arr_ + p);
}

template <class... Args>
void insert_many_back(Args&&... args){
  // auto it = args.begin();
  // for(size_type i = 0; i < args.size(); ++i, ++it){
    // insert(end(), *it);
    (insert(end(), args), ...);
  // }
}

// void erase(iterator pos){
//   // value_type* new_arr = new value_type[size_];
//   // std::copy(arr_, arr_ + size_, new_arr);
//   arr_[arr_ - pos].~T();
//   std::memcpy(pos, pos + 1, sizeof(T) * (size_ - 1));
//   pop_back();
  
  void erase(iterator pos) {
      size_t p = pos - arr_;
      arr_[p].~value_type();
      for (size_t i = p; i < size_ - 1; ++i) {
        new (arr_ + i) value_type(std::move(arr_[i + 1]));
        // if (i + 1 < size_){
        arr_[i + 1].~value_type();
        // }
      }
      --size_;
    }

  // delete[] new_arr;
  // std::cout << *pos << " funk"<<"\n";
// }

void push_back(const_reference value){
  if (size_ + 1 > capacity_) {
    reserve(capacity_ *= 2);
  }
  *end() = value;
  size_+=1;
}

void pop_back(){
  size_ -=1;
  // arr_[size_].~value_type();
  // (arr_ + size_).~value_type();
  // size_ -=1
}

void swap(vector& other){
    std::swap(other.arr_, arr_);
    std::swap(other.size_, size_);
    std::swap(other.capacity_, capacity_);
}

// void del_constr(){
//   for(size_t i = 0; i)
// }


  private:
    value_type* arr_;
    size_type size_;
    size_type capacity_;
  };
};
#endif //S21_VECTOR_H

// 3 sizev3
// 67 second el v3
// 3 capv3
// 0 blabla
// werqd
// 34 2 3

// 2 sizev3
// 67 second el v3
// 3 capv3
// werqd
// 35 67

// 4 sizev3
// 67 second el v3
// 6 capv3
// werqd
// 35 67 128 333

// 2 sizev3
// 128 second el v3
// 3 capv3
// werqd
// 35 128 %    

// 4 sizev3
// 45 second el v3
// 6 capv3
// werqd
// 35 45 67 67

