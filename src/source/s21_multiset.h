#ifndef S21_MULTISET_H_
#define S21_MULTISET_H_

#pragma once

#include "../rb_tree/s21_rb_tree.h"
#include "s21_set.h"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<Key>>
class multiset : public details::rb_tree<Key, Key, details::use_self<Key>,
                                         Compare, Alloc, false> {
 private:
  using base_type =
      details::rb_tree<Key, Key, details::use_self<Key>, Compare, Alloc, false>;
  using this_type = multiset<Key, Compare, Alloc>;

 public:
  using key_type = Key;
  using value_type = Key;
  using size_type = size_t;
  using typename base_type::const_iterator;
  using typename base_type::const_reference;
  using typename base_type::difference_type;
  using typename base_type::iterator;
  using typename base_type::reference;

  multiset() {}
  explicit multiset(std::initializer_list<value_type> const &items)
      : base_type() {
    for (const auto &item : items) base_type::insert(item);
  }
  multiset(const this_type &s) : base_type(s) {}
  multiset(this_type &&s) noexcept : base_type(std::move(s)) {}
  ~multiset() {}
  std::pair<iterator, bool> insert(const value_type &value) {
    return base_type::insert(value);
  }
  void merge(multiset &other) {
    for (const auto &item : other) base_type::insert(item);
    other.clear();
  }
  multiset &operator=(multiset &&s) & noexcept {
    return base_type::operator=(std::move(s)), *this;
  }
  multiset &operator=(const multiset &s) & {
    return base_type::operator=(s), *this;
  }
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> results;
    (results.emplace_back(insert(std::forward<Args>(args))), ...);
    return results;
  }
};
}  // namespace s21

#endif  // S21_MULTISET_H_
