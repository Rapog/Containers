#ifndef S21_LIST_H
#define S21_LIST_H

// rossartt добавил
#include <cstddef> 
#include <utility>
#include <limits> 

namespace s21{
template <class T>
class list {
 public:
  class ListIterator;
  class ListConstIterator;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  list();
  list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l);
  ~list();
  void operator=(list&& l);

  const_reference front() const;
  const_reference back() const;

  iterator begin();
  iterator end();

  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse();
  void unique();
  void sort();

  template <class... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <class... Args>
  void insert_many_back(Args&&... args);
  template <class... Args>
  void insert_many_front(Args&&... args);

  // helper
  // void Print();
  // helper

 private:
  typedef struct Node {
    Node* ptrPrev;
    Node* ptrNext;
    value_type value;
  } Node;
  Node* head_;
  Node* tail_;
  size_type size_;
  void zeroingList(list& other);
  void partSorting(iterator it_begin, iterator it_end);

 public:
  class ListIterator {
    friend class list<T>;

   public:
    ListIterator();
    ListIterator(Node* node);
    reference operator*();
    iterator& operator++();
    iterator& operator--();
    bool operator==(const iterator& it) const;
    bool operator!=(const iterator& it) const;

   protected:
    Node* cur_;
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator(){};
    ListConstIterator(Node* node);
    const_iterator& operator=(const iterator& it);
    const_reference operator*() const;
  };
};

#include "s21_list.tpp"
}

#endif
