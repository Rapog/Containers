#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "s21_list.h"

namespace s21{
  template<class T, class Container = s21::list<T>>
    class queue{
      using container_type = Container;
      using value_type = typename Container::value_type;
      using reference = typename Container::reference;
      using const_reference = typename Container::const_reference;
      using size_type = typename Container::size_type;

     public:
      queue() : head_() {}
      
      queue(std::initializer_list<value_type> const& items) : head_(items){}
      
      queue(const queue &q) : head_(q.head_){}
      
      queue(queue &&q): head_(std::move(q.head_)){}
      
      ~queue(){}

      queue operator=(queue &q) {
        head_ = q.head_;
        return *this;
      }

      queue operator=(queue &&q) {
        head_ = q.head_;
        return *this;
      }

      const_reference front() const noexcept{
        return head_.front();
      }

      const_reference back() const noexcept{
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
        head_.pop_front();
      }

      void swap(queue& other){
        head_.swap(other.head_);
      }
    // template <class... Args>
    //   void insert_many_front(Args&&... args){
    //     head_.insert_many_back(args...);
    //   }

    template <class... Args>
      void insert_many_back(Args&&... args){
        head_.insert_many_back(args...);
      }
    
     private:
     container_type head_;
    };


}


#endif //S21_QUEUE_H