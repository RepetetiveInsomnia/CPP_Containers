#ifndef S21_LIST_H_
#define S21_LIST_H_

#pragma once

#include <initializer_list>
#include <iterator>
#include <memory>
#include <stdexcept>

namespace s21 {

namespace details {

class list_node_base {
 private:
  using this_type = list_node_base;

 public:
  list_node_base() noexcept : next_(this), prev_(this) {}

  void insert(this_type* const next) noexcept;
  void erase() noexcept;
  void splice(this_type* const first, this_type* const last) noexcept;
  void reverse() noexcept;
  template <typename Compare>
  void merge(this_type* const o, Compare cmp) noexcept;

  static void swap(this_type* const lhs, this_type* const rhs) noexcept;

 public:
  this_type* next_;
  this_type* prev_;
};

void list_node_base::insert(this_type* const next) noexcept {
  next_ = next;
  prev_ = next->prev_;
  next->prev_->next_ = this;
  next->prev_ = this;
}

void list_node_base::erase() noexcept {
  next_->prev_ = prev_;
  prev_->next_ = next_;
}

void list_node_base::splice(this_type* const first,
                            this_type* const last) noexcept {
  last->prev_->next_ = this;
  first->prev_->next_ = last;
  prev_->next_ = first;

  this_type* const tmp = prev_;
  prev_ = last->prev_;
  last->prev_ = first->prev_;
  first->prev_ = tmp;
}

void list_node_base::reverse() noexcept {
  this_type* tmp = this;

  do {
    std::swap(tmp->next_, tmp->prev_);
    tmp = tmp->prev_;
  } while (tmp != this);
}

template <typename Compare>
void list_node_base::merge(this_type* const o, Compare cmp) noexcept {
  this_type* lfirst = next_;
  this_type* const llast = this;
  this_type* rfirst = o->next_;
  this_type* const rlast = o;

  while (lfirst != llast && rfirst != rlast) {
    if (cmp(rfirst, lfirst)) {
      this_type* rnext = rfirst->next_;
      lfirst->splice(rfirst, rnext);
      rfirst = rnext;
    } else {
      lfirst = lfirst->next_;
    }
  }

  if (rfirst != rlast) {
    splice(rfirst, rlast);
  }
}

void list_node_base::swap(this_type* const lhs, this_type* const rhs) noexcept {
  std::swap(lhs->next_, rhs->next_);
  std::swap(lhs->prev_, rhs->prev_);

  if (lhs->next_ == rhs) {
    lhs->next_ = lhs->prev_ = lhs;
  } else {
    lhs->next_->prev_ = lhs->prev_->next_ = lhs;
  }

  if (rhs->next_ == lhs) {
    rhs->next_ = rhs->prev_ = rhs;
  } else {
    rhs->next_->prev_ = rhs->prev_->next_ = rhs;
  }
}

template <typename T>
class list_node : public list_node_base {
 private:
  using this_type = list_node<T>;
  using base_type = list_node_base;

 public:
  using value_type = T;

 public:
  list_node() : val_() {}
  list_node(const value_type& val) : val_(val) {}
  list_node(value_type&& val) noexcept : val_(std::move(val)) {}

 public:
  value_type val_;
};

template <typename T, typename Pointer, typename Reference>
class list_iterator {
 private:
  using this_type = list_iterator<T, Pointer, Reference>;
  using node_base_type = list_node_base;
  using node_type = list_node<T>;

  using iterator = list_iterator<T, T*, T&>;
  using const_iterator = list_iterator<T, const T*, const T&>;

 public:
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = Pointer;
  using reference = Reference;

 public:
  list_iterator(const node_base_type* node_base) noexcept
      : node_base_(const_cast<node_base_type*>(node_base)) {}
  list_iterator(const iterator& o) noexcept
      : node_base_(const_cast<node_base_type*>(o.node_base_)) {}
  list_iterator(const const_iterator& o) noexcept
      : node_base_(const_cast<node_base_type*>(o.node_base_)) {}
  this_type& operator=(const iterator& o) noexcept {
    return node_base_ = const_cast<node_base_type*>(o.node_base_), *this;
  }
  this_type& operator=(const const_iterator& o) noexcept {
    return node_base_ = const_cast<node_base_type*>(o.node_base_), *this;
  }

  reference operator*() const noexcept {
    return static_cast<node_type*>(node_base_)->val_;
  }
  pointer operator->() const noexcept {
    return &static_cast<node_type*>(node_base_)->val_;
  }

  this_type& operator++() noexcept {
    return node_base_ = node_base_->next_, *this;
  }
  this_type operator++(int) noexcept;

  this_type& operator--() noexcept {
    return node_base_ = node_base_->prev_, *this;
  }
  this_type operator--(int) noexcept;

  this_type next() const noexcept { return this_type(node_base_->next_); }
  this_type prev() const noexcept { return this_type(node_base_->prev_); }

 public:
  node_base_type* node_base_;
};

template <typename T, typename Pointer, typename Reference>
typename list_iterator<T, Pointer, Reference>::this_type
list_iterator<T, Pointer, Reference>::operator++(int) noexcept {
  this_type tmp(node_base_);
  node_base_ = node_base_->next_;

  return tmp;
}

template <typename T, typename Pointer, typename Reference>
typename list_iterator<T, Pointer, Reference>::this_type
list_iterator<T, Pointer, Reference>::operator--(int) noexcept {
  this_type tmp(node_base_);
  node_base_ = node_base_->prev_;

  return tmp;
}

template <typename T, typename LPointer, typename LReference, typename RPointer,
          typename RReference>
inline bool operator==(
    const list_iterator<T, LPointer, LReference>& lhs,
    const list_iterator<T, RPointer, RReference>& rhs) noexcept {
  return lhs.node_base_ == rhs.node_base_;
}

template <typename T, typename LPointer, typename LReference, typename RPointer,
          typename RReference>
inline bool operator!=(
    const list_iterator<T, LPointer, LReference>& lhs,
    const list_iterator<T, RPointer, RReference>& rhs) noexcept {
  return lhs.node_base_ != rhs.node_base_;
}

template <typename T, typename Alloc>
class list_base {
 private:
  using this_type = list_base<T, Alloc>;

  using t_allocator_type = Alloc;
  using t_allocator_traits = std::allocator_traits<t_allocator_type>;
  using node_allocator_type =
      typename t_allocator_traits::template rebind_alloc<list_node<T>>;
  using node_allocator_traits = std::allocator_traits<node_allocator_type>;

 protected:
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using base_node_type = list_node_base;
  using node_type = list_node<T>;

 protected:
  list_base() : node_alloc_(), node_base_(), size_() {}
  explicit list_base(size_type n, const value_type& val = value_type());
  list_base(const this_type& o);
  list_base(this_type&& o) noexcept;
  this_type& operator=(const this_type& o);
  this_type& operator=(this_type&& o) noexcept;
  ~list_base() { clear(); }

  base_node_type* allocate() {
    return node_allocator_traits::allocate(node_alloc_, 1);
  }
  void deallocate(base_node_type* p) {
    node_allocator_traits::deallocate(node_alloc_, static_cast<node_type*>(p),
                                      1);
  }

  template <class... Args>
  void construct(base_node_type* p, Args&&... args) {
    node_allocator_traits::construct(node_alloc_, static_cast<node_type*>(p),
                                     std::forward<Args>(args)...);
  }
  void destroy(base_node_type* p) {
    node_allocator_traits::destroy(node_alloc_, static_cast<node_type*>(p));
  }

  void clear();

 protected:
  static constexpr size_type max_size_ = size_type(0) - 2;

  node_allocator_type node_alloc_;
  base_node_type node_base_;
  size_type size_;
};

template <typename T, typename Alloc>
list_base<T, Alloc>::list_base(size_type n, const value_type& val)
    : list_base() {
#ifdef DEBUG
  if (n > max_size_) {
    throw std::invalid_argument("s21::details::list_base(). size too big.");
  }
#endif

  for (size_ = n; n > 0; --n) {
    auto deleter = [this](base_node_type* ptr) -> void {
      deallocate(ptr), clear();
    };
    std::unique_ptr<base_node_type, decltype(deleter)> tmp(allocate(), deleter);
    construct(tmp.get(), val);

    tmp->insert(&node_base_);
    tmp.release();
  }
}

template <typename T, typename Alloc>
list_base<T, Alloc>::list_base(const this_type& o)
    : node_alloc_(o.node_alloc_), node_base_(), size_(o.size_) {
  list_iterator<T, T*, T&> it = o.node_base_.next_;

  for (size_type n = size_; n > 0; --n, ++it) {
    auto deleter = [this](base_node_type* ptr) -> void {
      deallocate(ptr), clear();
    };
    std::unique_ptr<base_node_type, decltype(deleter)> tmp(allocate(), deleter);
    construct(tmp.get(), *it);

    tmp->insert(&node_base_);
    tmp.release();
  }
}

template <typename T, typename Alloc>
list_base<T, Alloc>::list_base(this_type&& o) noexcept
    : node_alloc_(std::move(o.node_alloc_)),
      node_base_(),
      size_(std::move(o.size_)) {
  base_node_type::swap(&node_base_, &o.node_base_);
  o.size_ = 0;
}

template <typename T, typename Alloc>
typename list_base<T, Alloc>::this_type& list_base<T, Alloc>::operator=(
    const this_type& o) {
  if (&o != this) {
    this_type res(o);
    *this = std::move(res);
  }

  return *this;
}

template <typename T, typename Alloc>
typename list_base<T, Alloc>::this_type& list_base<T, Alloc>::operator=(
    this_type&& o) noexcept {
  if (&o != this) {
    clear();

    // mb add check if allocator can be moved or copied using
    // allocator_traits::propagate_on_container_move_assignment::value
    node_alloc_ = std::move(o.node_alloc_);
    base_node_type::swap(&node_base_, &o.node_base_);
    size_ = std::move(o.size_);

    o.size_ = 0;
  }

  return *this;
}

template <typename T, typename Alloc>
void list_base<T, Alloc>::clear() {
  base_node_type* i = node_base_.next_;

  while (i != &node_base_) {
    base_node_type* tmp = i;
    i = i->next_;
    destroy(tmp);
    deallocate(tmp);
  }
  node_base_.next_ = node_base_.prev_ = &node_base_;
  size_ = 0;
}

}  // namespace details

template <typename T, typename Alloc = std::allocator<T>>
class list : public details::list_base<T, Alloc> {
 private:
  using base_type = details::list_base<T, Alloc>;
  using this_type = list<T, Alloc>;

  using typename base_type::base_node_type;
  using typename base_type::node_type;

  using base_type::allocate;
  using base_type::clear;
  using base_type::construct;
  using base_type::deallocate;
  using base_type::destroy;
  using base_type::max_size_;
  using base_type::node_alloc_;
  using base_type::node_base_;
  using base_type::size_;

 public:
  using typename base_type::const_reference;
  using typename base_type::difference_type;
  using typename base_type::reference;
  using typename base_type::size_type;
  using typename base_type::value_type;
  using iterator = details::list_iterator<T, T*, T&>;
  using const_iterator = details::list_iterator<T, const T*, const T&>;

 public:
  list() {}
  explicit list(size_type n, const_reference val = value_type())
      : base_type(n, val) {}
  list(const std::initializer_list<value_type>& items) : base_type() {
    std::copy(items.begin(), items.end(), std::back_inserter(*this));
  }
  list(const this_type& o) : base_type(o) {}
  list(this_type&& o) noexcept : base_type(std::move(o)) {}
  this_type& operator=(const this_type& o) {
    return base_type::operator=(o), *this;
  }
  this_type& operator=(this_type&& o) noexcept {
    return base_type::operator=(std::move(o)), *this;
  }
  ~list() {}

  reference front();
  const_reference front() const {
    return const_cast<this_type*>(this)->front();
  }
  reference back();
  const_reference back() const { return const_cast<this_type*>(this)->back(); }

  iterator begin() noexcept { return iterator(node_base_.next_); }
  const_iterator begin() const noexcept {
    return const_iterator(node_base_.next_);
  }
  iterator end() noexcept { return iterator(&node_base_); }
  const_iterator end() const noexcept { return const_iterator(&node_base_); }

  bool empty() const noexcept { return size_ == 0 && begin() == end(); }
  size_type size() const noexcept { return size_; }
  constexpr size_type max_size() const noexcept { return max_size_; }

  void clear() noexcept { base_type::clear(); }
  iterator insert(const_iterator pos, value_type&& val);
  iterator insert(const_iterator pos, const_reference val) {
    return insert(pos, value_type(val));
  }
  iterator erase(const_iterator pos);
  void push_back(value_type&& val) { insert(end(), std::move(val)); }
  void push_back(const_reference val) { insert(end(), val); }
  void pop_back() { erase(--end()); }
  void push_front(value_type&& val) { insert(begin(), std::move(val)); }
  void push_front(const_reference val) { insert(begin(), val); }
  void pop_front() { erase(begin()); }
  void swap(this_type& o) noexcept { std::swap(*this, o); }
  void merge(this_type&& o);
  void merge(this_type& o) { merge(std::move(o)); }
  void splice(const_iterator pos, this_type&& o);
  void splice(const_iterator pos, this_type& o) { splice(pos, std::move(o)); }
  void reverse() noexcept { node_base_.reverse(); }
  void unique() noexcept;
  void sort() noexcept;

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
  template <typename... Args>
  void insert_many_front(Args&&... args);
};

template <typename T, typename Alloc>
typename list<T, Alloc>::reference list<T, Alloc>::front() {
#ifdef DEBUG
  if (empty()) {
    throw std::out_of_range("s21::list::front(). list is empty.");
  }
#endif

  return *iterator(node_base_.next_);
}

template <typename T, typename Alloc>
typename list<T, Alloc>::reference list<T, Alloc>::back() {
#ifdef DEBUG
  if (empty()) {
    throw std::out_of_range("s21::list::back(). list is empty.");
  }
#endif

  return *iterator(node_base_.prev_);
}

template <typename T, typename Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::insert(const_iterator pos,
                                                         value_type&& val) {
#ifdef DEBUG
  if (size_ == max_size()) {
    throw std::invalid_argument("s21::list::insert(). size too big.");
  }
#endif

  auto deleter = [this](base_node_type* ptr) -> void { deallocate(ptr); };
  std::unique_ptr<base_node_type, decltype(deleter)> tmp(allocate(), deleter);
  construct(tmp.get(), std::move(val));

  tmp->insert(pos.node_base_);
  ++size_;

  return iterator(tmp.release());
}

template <typename T, typename Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::erase(const_iterator pos) {
#ifdef DEBUG
  if (empty()) {
    throw std::out_of_range("s21::list::erase(). list is empty.");
  }

  if (pos == end()) {
    throw std::out_of_range("s21::list::erase(). pos is illegal.");
  }
#endif

  ++pos;
  base_node_type* tmp = pos.node_base_->prev_;

  tmp->erase();
  destroy(tmp);
  deallocate(tmp);
  --size_;

  return iterator(pos);
}

template <typename T, typename Alloc>
void list<T, Alloc>::merge(this_type&& o) {
  if (this != &o && !o.empty()) {
#ifdef DEBUG
    if (node_alloc_ != o.node_alloc_) {
      throw std::runtime_error(
          "s21::list::merge(). cant merge list with different allocator.");
    }
#endif

    auto cmp = [](const value_type& lhs, const value_type& rhs) -> bool {
      return lhs < rhs;
    };

    auto icmp = [cmp](base_node_type* lhs, base_node_type* rhs) -> bool {
      return cmp(static_cast<node_type*>(lhs)->val_,
                 static_cast<node_type*>(rhs)->val_);
    };

    node_base_.merge(&o.node_base_, icmp);
    size_ += o.size_;
    o.size_ = 0;
  }
}

template <typename T, typename Alloc>
void list<T, Alloc>::splice(const_iterator pos, this_type&& o) {
  if (this != &o && !o.empty()) {
#ifdef DEBUG
    if (node_alloc_ != o.node_alloc_) {
      throw std::runtime_error(
          "s21::list::splice(). cant splice list with different allocator.");
    }
#endif

    pos.node_base_->splice(o.begin().node_base_, o.end().node_base_);
    size_ += o.size_;
    o.size_ = 0;
  }
}

template <typename T, typename Alloc>
void list<T, Alloc>::unique() noexcept {
  if (!empty()) {
    iterator first = begin();
    iterator last = end();

    for (iterator next = first; ++next != last;) {
      if (*first == *next) {
        erase(next);
      } else {
        first = next;
      }
      next = first;
    }
  }
}

template <typename T, typename Alloc>
void list<T, Alloc>::sort() noexcept {
  if (size() > 1) {
    for (auto i = begin(); i != end().prev(); ++i) {
      for (auto j = begin(); j != end().prev(); ++j) {
        if (*(j.next()) < *j) {
          std::swap(*(j.next()), *j);
        }
      }
    }
  }
}

template <typename T, typename Alloc>
template <typename... Args>
typename list<T, Alloc>::iterator list<T, Alloc>::insert_many(
    const_iterator pos, Args&&... args) {
  for (auto elem : {std::forward<Args>(args)...}) {
    insert(pos, elem);
  }

  return --pos;
}

template <typename T, typename Alloc>
template <typename... Args>
void list<T, Alloc>::insert_many_back(Args&&... args) {
  insert_many(end(), std::forward<Args>(args)...);
}

template <typename T, typename Alloc>
template <typename... Args>
void list<T, Alloc>::insert_many_front(Args&&... args) {
  insert_many(begin(), std::forward<Args>(args)...);
}

}  // namespace s21

#endif  // S21_LIST_H_