#ifndef S21_STACK_H
#define S21_STACK_H

#include "s21_vector.h"

namespace s21{
  template<class T, class Container = s21::vector<T>>
    class stack{
      using container_type = Container;
      using value_type = typename Container::value_type;
      using reference = typename Container::reference;
      using const_reference = typename Container::const_reference;
      using size_type = typename Container::size_type;

     public:
      stack() : head_(){}

      stack(std::initializer_list<value_type> const &items) : head_(items){}

      stack(const stack &s) : head_(s.head_){}

      stack(stack &&s) : head_(std::move(s.head_)){}
      
      ~stack(){}

      stack operator=(stack &s){
        head_ = s.head_;
        return *this;
      }

      stack operator=(stack &&s){
        head_ = s.head_;
        return *this;
      }

      const_reference top(){
        return head_.back();
      }

      bool empty() const noexcept{
        return head_.empty();
      }

      size_type size() const noexcept{
        return head_.size();
      }

      void push(const_reference value){
        head_.push_back(value);
      }

      void pop(){
        head_.pop_back();
      }

      void swap(stack& other){
        head_.swap(other.head_);
      }
      
      template <class... Args>
      void insert_many_front(Args&&... args){
        head_.insert_many_back(args...);
      }

     private:
      container_type head_;
    };  
}

#endif  //S21_STACK_H