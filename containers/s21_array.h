#ifndef S21_ARRAY_H
#define S21_ARRAY_H

namespace s21{
  template<typename T, std::size_t  N>
  class array{
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = T*;
    using const_iterator = const T*;
    using size_type = size_t;

   public:
    array() : arr_(new value_type[N]), size_(N), capacity_(N){}

    array(std::initializer_list<value_type> const &items) : size_(N), capacity_(N){
    //   size_t sz = items.size();
      if (N < items.size()){
        throw std::logic_error("Too many initializer values");
      }
      // size_ = items.size();
      // capacity_ = N;
      arr_ = new value_type[capacity_];
      auto it = items.begin();
      for(size_type i = 0; i < size_; ++i, ++it){
        new(arr_ + i) value_type(*it);
      }
    }

    array(const array &a) : arr_(new value_type[a.size()]), size_(a.size()), capacity_(a.capacity_){
      // if (a.arr_){
        for (size_t i = 0; i < size_; ++i) {
          new (arr_ + i) value_type(a.arr_[i]);
        }
      // }
    }

    array(const array &&a) : arr_(new value_type[a.size()]), size_(a.size()), capacity_(a.capacity_){
      // if (a.arr_){
        for (size_t i = 0; i < size_; ++i) {
          new (arr_ + i) value_type(a.arr_[i]);
        }
      // }
    }
    // array(array &&a) : arr_(nullptr), size_(0){
    //   // std::swap(a.arr_, arr_);
    //   // std::swap(a.size_, size_);
    //   // delete[](a.arr_);
    // }

    ~array(){
      if(arr_!=nullptr){delete[](arr_);}
    }

    array operator=(array &a){
      if (&a == this) return *this;
      array other(a);
      std::swap(other.arr_, arr_);
      std::swap(other.size_, size_);
      std::swap(other.capacity_, capacity_);
      // other.~;
      return *this;
    }


    array operator=(array &&a){
    //   if (&a == this) return *this;
    //   std::swap(a.arr_, arr_);
    //   std::swap(a.size_, size_);
    // // if(other.arr_) {
    //   delete[](a.arr_);
    //   // }
    //   a.arr_ = nullptr;
    //   a.size_ = 0;
    //   return *this;
      if (&a == this) return *this;
      array other(a);
      std::swap(other.arr_, arr_);
      std::swap(other.size_, size_);
      std::swap(other.capacity_, capacity_);
      // other.~;
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
      return *(arr_ + size_);
    }

    iterator* data(){
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

    size_type max_size() noexcept {
      // size_t p = 0;
      // if (sizeof(void*) == 8 && !std::is_same_v<T, char>
      // ){
      //   p = std::pow(2,64)/sizeof(T);
      // }
      // else if (sizeof(void*) == 8 && std::is_same_v<T, char>){
      //   p = std::pow(2,64)/(sizeof(T)*2);
      // }
      // else if (sizeof(void*) == 4){
      //   p = std::pow(2,32)/sizeof(T);
      // }
      // return p - 1;
      return capacity_;
    }

    void swap(array& other){
      std::swap(other.arr_, arr_);
      std::swap(other.size_, size_);
      std::swap(other.capacity_, capacity_);
    }

    void fill (const_reference value){
      for(size_type i = 0; i < size_; ++i){
        new (arr_ + i) value_type(value);
      }
    }

   private:
    value_type* arr_;
    size_type size_;
    size_type capacity_;
  };
}

#endif //S21_ARRAY_H