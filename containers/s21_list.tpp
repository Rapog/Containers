template <class T>
list<T>::list() : size_(0) {
  Node* ptr = new Node;
  ptr->ptrNext = ptr->ptrPrev = head_ = tail_ = ptr;
  ptr->value = value_type();
}

template <class T>
list<T>::list(size_type n) : list() {
  for (size_type i = 0; i < n; i++) push_back(value_type());
}

template <class T>
list<T>::list(std::initializer_list<value_type> const& items) : list() {
  for (auto i = items.begin(); i != items.end(); i++) push_back(*i);
}

template <class T>
list<T>::list(const list& l) : list() {
  Node* ptr = l.tail_;
  for (size_type i = 0; i < l.size_; ++i) {
    ptr = ptr->ptrNext;
    push_back(ptr->value);
  }
}

template <class T>
list<T>::list(list&& l) {
  size_ = l.size_;
  head_ = l.head_;
  tail_ = l.tail_;
  l.size_ = 0;
  l.head_ = nullptr;
  l.tail_ = nullptr;
}

template <class T>
list<T>::~list() {
  clear();
  delete tail_;
}

template <class T>
void list<T>::operator=(list&& l) {
  clear();
  delete tail_;
  size_ = l.size_;
  head_ = l.head_;
  tail_ = l.tail_;
  l.size_ = 0;
  l.head_ = nullptr;
  l.tail_ = nullptr;
}

template <class T>
typename list<T>::const_reference list<T>::front() const {
  return head_->value;
}

template <class T>
typename list<T>::const_reference list<T>::back() const {
  return tail_->ptrPrev->value;
}

template <class T>
typename list<T>::iterator list<T>::begin() {
  return iterator(head_);
}

template <class T>
typename list<T>::iterator list<T>::end() {
  return iterator(tail_);
}

template <class T>
typename list<T>::const_iterator list<T>::cbegin() const {
  return const_iterator(head_);
}

template <class T>
typename list<T>::const_iterator list<T>::cend() const {
  return const_iterator(tail_);
}

template <class T>
bool list<T>::empty() const {
  return size_ == 0;
}

template <class T>
typename list<T>::size_type list<T>::size() const {
  return size_;
}

template <class T>
typename list<T>::size_type list<T>::max_size() const {
  return std::numeric_limits<list<T>::size_type>::max() /
         sizeof(list<T>::Node) / 2;
}

template <class T>
void list<T>::clear() {
  while (size_ != 0) pop_front();
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node* ptr = new Node;
  ptr->value = value;
  ptr->ptrNext = pos.cur_;
  ptr->ptrPrev = pos.cur_->ptrPrev;
  if (pos.cur_ == head_) head_ = ptr;
  ptr->ptrNext->ptrPrev = ptr;
  ptr->ptrPrev->ptrNext = ptr;
  ++size_;
  return ptr;
}

template <class T>
void list<T>::erase(iterator pos) {
  if (pos.cur_ == head_) head_ = head_->ptrNext;
  pos.cur_->ptrPrev->ptrNext = pos.cur_->ptrNext;
  pos.cur_->ptrNext->ptrPrev = pos.cur_->ptrPrev;
  delete pos.cur_;
  --size_;
}

template <class T>
void list<T>::push_back(const_reference value) {
  Node* ptr = new Node;
  ptr->value = value;
  ptr->ptrNext = tail_;
  ptr->ptrPrev = tail_->ptrPrev;
  Node* tmp = tail_->ptrPrev;
  tmp->ptrNext = ptr;
  tail_->ptrPrev = ptr;
  head_ = tail_->ptrNext;
  ++size_;
}

template <class T>
void list<T>::pop_back() {
  if (size_) {
    Node* ptr = tail_->ptrPrev;
    Node* tmp = ptr->ptrPrev;
    tmp->ptrNext = tail_;
    tail_->ptrPrev = tmp;
    delete ptr;
    --size_;
  }
}

template <class T>
void list<T>::push_front(const_reference value) {
  Node* ptr = new Node;
  ptr->value = value;
  ptr->ptrNext = head_;
  ptr->ptrPrev = tail_;
  head_->ptrPrev = ptr;
  tail_->ptrNext = ptr;
  head_ = ptr;
  ++size_;
}

template <class T>
void list<T>::pop_front() {
  if (size_) {
    Node* ptr = head_;
    head_ = ptr->ptrNext;
    head_->ptrPrev = tail_;
    tail_->ptrNext = head_;
    delete ptr;
    --size_;
  }
}

template <class T>
void list<T>::swap(list& other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <class T>
void list<T>::merge(list& other) {
  if (this->head_ != other.head_ && !other.empty()) {
    iterator it_this = begin();
    iterator it_end = end();
    iterator it_other = other.begin();
    while (it_other.cur_ != other.tail_) {
      if (it_this.cur_ == tail_ || *it_this > *it_other) {
        it_end.cur_->ptrNext = it_other.cur_;
        it_other.cur_->ptrPrev = it_end.cur_;
        ++it_other;
        ++it_end;
        ++size_;
      } else {
        it_end.cur_->ptrNext = it_this.cur_;
        it_this.cur_->ptrPrev = it_end.cur_;
        ++it_this;
        ++it_end;
      }
    }
    if (it_this.cur_ != tail_) {
      it_end.cur_->ptrNext = it_this.cur_;
      it_this.cur_->ptrPrev = it_end.cur_;
    } else {
      it_end.cur_->ptrNext = tail_;
      tail_->ptrPrev = it_end.cur_;
    }
    head_ = tail_->ptrNext;
    zeroingList(other);
  }
}

template <class T>
void list<T>::splice(const_iterator pos, list& other) {
  if (other.size_) {
    if (head_ == pos.cur_) head_ = other.head_;
    pos.cur_->ptrPrev->ptrNext = other.head_;
    other.head_->ptrPrev = pos.cur_->ptrPrev;
    pos.cur_->ptrPrev = other.tail_->ptrPrev;
    other.tail_->ptrPrev->ptrNext = pos.cur_;
    size_ += other.size_;
    zeroingList(other);
  }
}

template <class T>
void list<T>::reverse() {
  if (size_ > 1) {
    iterator it = end();
    do {
      std::swap(it.cur_->ptrNext, it.cur_->ptrPrev);
      ++it;
    } while (it != end());
  }
  head_ = tail_->ptrNext;
}

template <class T>
void list<T>::unique() {
  iterator curPos = begin();
  iterator nextPos = begin();
  ++nextPos;
  iterator endPos = end();
  while (nextPos != endPos) {
    if (*curPos == *nextPos) {
      iterator tmp = nextPos;
      ++nextPos;
      erase(tmp);
    } else {
      ++curPos;
      ++nextPos;
    }
  }
}

template <class T>
void list<T>::sort() {
  partSorting(begin(), --end());
  head_ = tail_->ptrNext;
}

template <class T>
template <class... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  auto res = const_iterator(pos.cur_->ptrPrev);
  (insert(pos, args), ...);
  return res;
}

template <class T>
template <class... Args>
void list<T>::insert_many_back(Args&&... args) {
  (push_back(args), ...);
}

template <class T>
template <class... Args>
void list<T>::insert_many_front(Args&&... args) {
  (push_front(args), ...);
}

template <class T>
void list<T>::zeroingList(list& other) {
  other.tail_->ptrNext = other.tail_;
  other.tail_->ptrPrev = other.tail_;
  other.head_ = other.tail_;
  other.size_ = 0;
}

template <class T>
void list<T>::partSorting(iterator it_begin, iterator it_end) {
  iterator start = it_begin.cur_->ptrPrev;
  iterator finish = it_end.cur_->ptrNext;
  while (it_begin != it_end) {
    ++it_begin;
    if (it_begin.cur_->ptrPrev->value >= *it_end) {
      it_end.cur_->ptrNext->ptrPrev = it_begin.cur_->ptrPrev;
      it_begin.cur_->ptrPrev->ptrNext = it_end.cur_->ptrNext;
      it_begin.cur_->ptrPrev->ptrPrev->ptrNext = it_begin.cur_;
      it_end.cur_->ptrNext = it_begin.cur_->ptrPrev;
      it_begin.cur_->ptrPrev = it_begin.cur_->ptrPrev->ptrPrev;
      it_end.cur_->ptrNext->ptrPrev = it_end.cur_;
    }
  }
  if (it_end.cur_->ptrPrev != start.cur_ &&
      it_end.cur_->ptrPrev->ptrPrev != start.cur_)
    partSorting(start.cur_->ptrNext, it_end.cur_->ptrPrev);
  if (it_end.cur_->ptrNext != finish.cur_ &&
      it_end.cur_->ptrNext->ptrNext != finish.cur_)
    partSorting(it_end.cur_->ptrNext, finish.cur_->ptrPrev);
}

template <class T>
list<T>::ListIterator::ListIterator() {}

template <class T>
list<T>::ListIterator::ListIterator(Node* node) {
  cur_ = node;
}

template <class T>
typename list<T>::reference list<T>::ListIterator::operator*() {
  return cur_->value;
}

template <class T>
typename list<T>::iterator& list<T>::ListIterator::operator++() {
  cur_ = cur_->ptrNext;
  return *this;
}

template <class T>
typename list<T>::iterator& list<T>::ListIterator::operator--() {
  cur_ = cur_->ptrPrev;
  return *this;
}

template <class T>
bool list<T>::ListIterator::operator==(const iterator& it) const {
  return cur_ == it.cur_;
}

template <class T>
bool list<T>::ListIterator::operator!=(const iterator& it) const {
  return cur_ != it.cur_;
}

template <class T>
list<T>::ListConstIterator::ListConstIterator(Node* node)
    : ListIterator(node) {}

template <class T>
typename list<T>::const_iterator& list<T>::ListConstIterator::operator=(
    const iterator& it) {
  this->cur_ = it.cur_;
  return *this;
}

template <class T>
typename list<T>::const_reference list<T>::ListConstIterator::operator*()
    const {
  return this->cur_->value;
}

// helper
// template <class T>
// void list<T>::Print() {
//   Node* ptr = head_;
//   size_type tmpSize = size_;
//   while (tmpSize) {
//     std::cout << ptr->value << std::endl;
//     ptr = ptr->ptrNext;
//     --tmpSize;
//   }
// }
// helper
