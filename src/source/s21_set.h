#ifndef S21_SET_H_
#define S21_SET_H_

#pragma once

#include "../rb_tree/s21_rb_tree.h"

namespace s21 {

namespace details {

template <typename T>
struct use_self {
  typedef T result_type;

  const T &operator()(const T &x) const { return x; }
};

}  // namespace details
template <typename Key, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<Key>>
class set : public details::rb_tree<Key, Key, details::use_self<Key>, Compare,
                                    Alloc, true> {
 private:
  using base_type =
      details::rb_tree<Key, Key, details::use_self<Key>, Compare, Alloc, true>;
  using this_type = set<Key, Compare, Alloc>;

 public:
  using key_type = Key;
  using value_type = Key;
  using size_type = size_t;
  using typename base_type::const_iterator;
  using typename base_type::const_reference;
  using typename base_type::difference_type;
  using typename base_type::iterator;
  using typename base_type::reference;
  set() {}
  explicit set(std::initializer_list<value_type> const &items)
      : base_type(items) {}
  set(const this_type &s) : base_type(s) {}
  set(this_type &&s) noexcept : base_type(std::move(s)) {}
  ~set() {}
  std::pair<iterator, bool> insert(const value_type &value) {
    return base_type::insert(value);
  }
  set &operator=(set &&s) & noexcept {
    return base_type::operator=(std::move(s)), *this;
  }
  set &operator=(const set &s) & { return base_type::operator=(s), *this; }
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> results;
    (results.emplace_back(insert(std::forward<Args>(args))), ...);
    return results;
  }
};
}  // namespace s21

#endif  // S21_SET_H_
