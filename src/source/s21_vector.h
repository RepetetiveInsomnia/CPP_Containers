#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#pragma once

#include <initializer_list>
#include <iterator>
#include <memory>
#include <stdexcept>

namespace s21 {

namespace details {

template <typename T, typename Alloc>
class vector_base {
 private:
  using this_type = vector_base<T, Alloc>;

  using allocator_type = Alloc;
  using allocator_traits = std::allocator_traits<allocator_type>;

 protected:
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;

 protected:
  vector_base() : alloc_(), begin_(nullptr), end_(nullptr), cap_(nullptr) {}
  explicit vector_base(size_type n, const_reference val = value_type());
  vector_base(const this_type& o);
  vector_base(this_type&& o) noexcept;
  this_type& operator=(const this_type& o);
  this_type& operator=(this_type&& o) noexcept;
  ~vector_base() { clear(); }

  pointer allocate(size_type n) {
    return allocator_traits::allocate(alloc_, n);
  }
  void deallocate(pointer p, size_type n) {
    allocator_traits::deallocate(alloc_, p, n);
  }

  template <class... Args>
  void construct(pointer p, Args&&... args) {
    allocator_traits::construct(alloc_, p, std::forward<Args>(args)...);
  }
  void destroy(pointer p) { allocator_traits::destroy(alloc_, p); }
  void destroy(pointer begin, pointer end);

 protected:
  static constexpr size_type invalid_pos_ = size_type(0) - 1;
  static constexpr size_type max_size_ = size_type(0) - 2;

  allocator_type alloc_;
  pointer begin_;
  pointer end_;
  pointer cap_;

 private:
  void clear();
};

template <typename T, typename Alloc>
vector_base<T, Alloc>::vector_base(size_type n, const_reference val)
    : alloc_() {
#ifdef DEBUG
  if (n > max_size_) {
    throw std::invalid_argument("s21::details::vector_base(). size too big.");
  }
#endif

  auto deleter = [this, n](pointer ptr) -> void {
    deallocate(ptr, n);
    begin_ = end_ = cap_ = nullptr;
  };
  std::unique_ptr<value_type, decltype(deleter)> ubegin(allocate(n), deleter);

  end_ = cap_ = ubegin.get() + n;
  std::uninitialized_fill(ubegin.get(), end_, val);
  begin_ = ubegin.release();
}

template <typename T, typename Alloc>
vector_base<T, Alloc>::vector_base(const this_type& o) : alloc_(o.alloc_) {
  auto deleter = [this, &o](pointer ptr) -> void {
    deallocate(ptr, o.cap_ - o.begin_);
    begin_ = end_ = cap_ = nullptr;
  };
  std::unique_ptr<value_type, decltype(deleter)> ubegin(
      allocate(o.cap_ - o.begin_), deleter);

  end_ = std::uninitialized_copy(o.begin_, o.end_, ubegin.get());
  begin_ = ubegin.release();
  cap_ = begin_ + (o.cap_ - o.begin_);
}

template <typename T, typename Alloc>
vector_base<T, Alloc>::vector_base(this_type&& o) noexcept
    : alloc_(std::move(o.alloc_)) {
  begin_ = std::move(o.begin_);
  end_ = std::move(o.end_);
  cap_ = std::move(o.cap_);

  o.begin_ = o.end_ = o.cap_ = nullptr;
}

template <typename T, typename Alloc>
typename vector_base<T, Alloc>::this_type& vector_base<T, Alloc>::operator=(
    const this_type& o) {
  if (&o != this) {
    this_type res(o);
    *this = std::move(res);
  }

  return *this;
}

template <typename T, typename Alloc>
typename vector_base<T, Alloc>::this_type& vector_base<T, Alloc>::operator=(
    this_type&& o) noexcept {
  if (&o != this) {
    clear();

    // mb add check if allocator can be moved or copied using
    // allocator_traits::propagate_on_container_move_assignment::value
    alloc_ = std::move(o.alloc_);
    begin_ = std::move(o.begin_);
    end_ = std::move(o.end_);
    cap_ = std::move(o.cap_);

    o.begin_ = o.end_ = o.cap_ = nullptr;
  }

  return *this;
}

template <typename T, typename Alloc>
void vector_base<T, Alloc>::destroy(pointer begin, pointer end) {
  for (pointer i = begin; i != end; ++i) {
    destroy(i);
  }
}

template <typename T, typename Alloc>
void vector_base<T, Alloc>::clear() {
  destroy(begin_, end_);
  deallocate(begin_, cap_ - begin_);
  begin_ = end_ = cap_ = nullptr;
}

}  // namespace details

template <typename T, typename Alloc = std::allocator<T>>
class vector : public details::vector_base<T, Alloc> {
 private:
  using base_type = details::vector_base<T, Alloc>;
  using this_type = vector<T, Alloc>;

  using base_type::alloc_;
  using base_type::allocate;
  using base_type::begin_;
  using base_type::cap_;
  using base_type::construct;
  using base_type::deallocate;
  using base_type::destroy;
  using base_type::end_;
  using base_type::invalid_pos_;
  using base_type::max_size_;

 public:
  using typename base_type::const_pointer;
  using typename base_type::const_reference;
  using typename base_type::difference_type;
  using typename base_type::pointer;
  using typename base_type::reference;
  using typename base_type::size_type;
  using typename base_type::value_type;
  using iterator = T*;
  using const_iterator = const T*;

  static constexpr double growth_factor_ = 2.0;

 public:
  vector() : base_type() {}
  explicit vector(size_type n, const_reference val = value_type())
      : base_type(n, val) {}
  vector(const std::initializer_list<value_type>& items);
  vector(const this_type& o) : base_type(o) {}
  vector(this_type&& o) noexcept : base_type(std::move(o)) {}
  this_type& operator=(const this_type& o) {
    return base_type::operator=(o), *this;
  }
  this_type& operator=(this_type&& o) noexcept {
    return base_type::operator=(std::move(o)), *this;
  }
  ~vector() {}

  reference operator[](size_type pos) noexcept { return begin_[pos]; }
  const_reference operator[](size_type pos) const noexcept {
    return begin_[pos];
  }
  reference at(size_type pos);
  const_reference at(size_type pos) const {
    return const_cast<this_type*>(this)->at(pos);
  }

  reference front();
  const_reference front() const {
    return const_cast<this_type*>(this)->front();
  }
  reference back();
  const_reference back() const { return const_cast<this_type*>(this)->back(); }
  pointer data() noexcept { return begin_; }
  const_pointer data() const noexcept { return begin_; }

  iterator begin() noexcept { return begin_; }
  const_iterator begin() const noexcept { return begin_; }
  iterator end() noexcept { return end_; }
  const_iterator end() const noexcept { return end_; }

  bool empty() const noexcept { return end_ <= begin_; }
  size_type size() const noexcept { return end_ - begin_; }
  constexpr size_type max_size() const noexcept { return max_size_; }
  void reserve(size_type size);
  size_type capacity() const noexcept { return cap_ - begin_; }
  void shrink_to_fit();

  void clear() noexcept;
  iterator insert(const_iterator pos, value_type&& val);
  iterator insert(const_iterator pos, const_reference val) {
    return insert(pos, value_type(val));
  }
  iterator erase(const_iterator pos);
  void push_back(value_type&& val) { insert(end_, std::move(val)); }
  void push_back(const_reference val) { insert(end_, val); }
  void pop_back() { erase(end_ - 1); }
  void swap(this_type& o) noexcept { std::swap(*this, o); }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
};

template <typename T, typename Alloc>
vector<T, Alloc>::vector(const std::initializer_list<value_type>& items)
    : base_type() {
  reserve(items.size());
  std::copy(items.begin(), items.end(), std::back_inserter(*this));
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type pos) {
  if (empty()) {
    throw std::out_of_range("s21::vector::at(). vector is empty.");
  }

  if (pos == invalid_pos_ || pos >= size()) {
    throw std::out_of_range("s21::vector::at(). invalid pos.");
  }

  return begin_[pos];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::front() {
#ifdef DEBUG
  if (empty()) {
    throw std::out_of_range("s21::vector::front(). vector is empty.");
  }
#endif

  return *begin_;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::back() {
#ifdef DEBUG
  if (empty()) {
    throw std::out_of_range("s21::vector::back(). vector is empty.");
  }
#endif

  return *(end_ - 1);
}

template <typename T, typename Alloc>
void vector<T, Alloc>::reserve(size_type size) {
#ifdef DEBUG
  if (size >= max_size()) {
    throw std::invalid_argument("s21::vector::reserve(). size too big.");
  }
#endif

  if (size > capacity()) {
    auto deleter = [this, size](pointer ptr) -> void { deallocate(ptr, size); };
    std::unique_ptr<value_type, decltype(deleter)> res_begin(allocate(size),
                                                             deleter);
    auto res_end = std::uninitialized_move(begin_, end_, res_begin.get());
    auto res_cap = res_begin.get() + size;

    deallocate(begin_, capacity());

    begin_ = res_begin.release();
    end_ = res_end;
    cap_ = res_cap;
  }
}

template <typename T, typename Alloc>
void vector<T, Alloc>::shrink_to_fit() {
  auto deleter = [this, size = size()](pointer ptr) -> void {
    deallocate(ptr, size);
  };
  std::unique_ptr<value_type, decltype(deleter)> res_begin(allocate(size()),
                                                           deleter);
  auto res_end = std::uninitialized_move(begin_, end_, res_begin.get());
  auto res_cap = res_begin.get() + size();

  deallocate(begin_, capacity());

  begin_ = res_begin.release();
  end_ = res_end;
  cap_ = res_cap;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::clear() noexcept {
  destroy(begin_, end_);
  end_ = begin_;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator pos,
                                                             value_type&& val) {
#ifdef DEBUG
  if (size() == max_size()) {
    throw std::invalid_argument("s21::vector::insert(). size too big.");
  }

  if (pos < begin_ || pos > end_) {
    throw std::out_of_range("s21::vector::insert(). pos is illegal.");
  }
#endif

  const difference_type diff = pos - begin_;

  if (end_ == cap_) {
    reserve(size_type(growth_factor_ * std::max(capacity(), size_type(1))));
  }
  pos = begin_ + diff;

  if (end_ != pos) {
    construct(end_, std::move(*(end_ - 1)));

    std::move_backward(const_cast<iterator>(pos), end_ - 1, end_);

    *const_cast<iterator>(pos) = std::move(val);
  } else {
    construct(end_, std::move(val));
  }
  ++end_;

  return const_cast<iterator>(pos);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(
    const_iterator pos) {
#ifdef DEBUG
  if (empty()) {
    throw std::out_of_range("s21::vector::erase(). vector is empty.");
  }

  if (pos < begin_ || pos >= end_) {
    throw std::out_of_range("s21::vector::erase(). pos is illegal.");
  }
#endif

  const difference_type diff = pos - begin_;

  if (pos + 1 < end_) {
    std::move(const_cast<iterator>(pos + 1), end_, const_cast<iterator>(pos));
  }
  destroy(--end_);

  return begin_ + diff;
}

template <typename T, typename Alloc>
template <typename... Args>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert_many(
    const_iterator pos, Args&&... args) {
  difference_type diff = pos - begin_;

  for (auto elem : {std::forward<Args>(args)...}) {
    insert(begin_ + diff++, elem);
  }

  return begin_ + --diff;
}

template <typename T, typename Alloc>
template <typename... Args>
void vector<T, Alloc>::insert_many_back(Args&&... args) {
  insert_many(end_, std::forward<Args>(args)...);
}

}  // namespace s21

#endif  // S21_VECTOR_H_
