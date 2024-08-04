#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_
#pragma once

#include <cstddef>
#include <cstdio>
#include <iostream>
#include <limits>

#include "s21_list.h"

namespace s21 {

template <typename T, typename queue_list = s21::list<T>>
class queue {
 public:
  using value_type = typename queue_list::value_type;
  using reference = typename queue_list::reference;
  using const_reference = typename queue_list::const_reference;
  using size_type = typename queue_list::size_type;

  queue() : data_() {}
  queue(std::initializer_list<value_type> const &items) : data_(items) {}
  queue(const queue &que) : data_(que.data_) {}
  queue(queue &&que) : data_(std::move(que.data_)) {}
  queue &operator=(queue &que) {
    data_ = que.data_;
    return *this;
  }
  queue &operator=(queue &&que) {
    data_ = std::move(que.data_);
    return *this;
  }
  ~queue() { data_.clear(); }
  const_reference front() { return data_.front(); }
  const_reference back() { return data_.back(); }

  bool empty() { return data_.empty(); }
  size_type size() { return data_.size(); }

  void push(const_reference value) { data_.push_back(value); }
  void pop() { data_.pop_front(); }
  void swap(queue &other) { data_.swap(other.data_); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (..., push(std::forward<Args>(args)));
  }

 private:
  queue_list data_;
};

}  // namespace s21

#endif  // S21_QUEUE_H_