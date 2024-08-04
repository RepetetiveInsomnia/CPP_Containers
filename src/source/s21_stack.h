#ifndef S21_STACK_H_
#define S21_STACK_H_

#pragma once

#include <initializer_list>
#include <memory>
#include <stdexcept>

#include "s21_list.h"

namespace s21 {

template <typename T, class Container = s21::list<T>>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  using this_type = stack<T, Container>;

 public:
  stack() noexcept;
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack() noexcept;

  this_type &operator=(const stack &s);
  this_type &operator=(stack &&s);

  bool empty() noexcept;
  size_type size() noexcept;

  const_reference top();
  void push(const_reference value);
  void pop();
  void swap(stack &other);

  template <class... Args>
  void insert_many_back(Args &&...args);

 private:
  Container container_;
};

template <typename T, class Container>
stack<T, Container>::stack() noexcept {}

template <typename T, class Container>
stack<T, Container>::stack(std::initializer_list<value_type> const &items) {
  for (const auto value : items) {
    container_.push_back(value);
  }
}

template <typename T, class Container>
stack<T, Container>::stack(const stack &s) {
  container_ = s.container_;
}

template <typename T, class Container>
stack<T, Container>::stack(stack &&s) {
  container_ = std::move(s.container_);
}

template <typename T, class Container>
stack<T, Container>::~stack() noexcept {
  container_.clear();
}

template <typename T, class Container>
stack<T, Container> &stack<T, Container>::operator=(const stack &s) {
  container_.clear();
  container_ = s.container_;
  return *this;
}

template <typename T, class Container>
stack<T, Container> &stack<T, Container>::operator=(stack &&s) {
  container_.clear();
  container_ = std::move(s.container_);
  return *this;
}

template <typename T, class Container>
bool stack<T, Container>::empty() noexcept {
  return container_.empty();
}

template <typename T, class Container>
size_t stack<T, Container>::size() noexcept {
  return container_.size();
}

template <typename T, class Container>
void stack<T, Container>::push(const_reference value) {
  container_.push_back(value);
}

template <typename T, class Container>
void stack<T, Container>::pop() {
  container_.pop_back();
}

template <typename T, class Container>
void stack<T, Container>::swap(stack &other) {
  return container_.swap(other.container_);
}

template <typename T, class Container>
const T &stack<T, Container>::top() {
  return container_.back();
}

template <typename T, class Container>
template <class... Args>
void stack<T, Container>::insert_many_back(Args &&...args) {
  container_.insert_many_back(args...);
}

}  // namespace s21

#endif  // S21_STACK_H_
