#ifndef S21_MAP_H_
#define S21_MAP_H_

#pragma once

#include "../rb_tree/s21_rb_tree.h"
#include "s21_vector.h"

namespace s21 {

namespace details {

template <typename Pair>
class extract_first {
 public:
  auto operator()(const Pair& arg) -> decltype((arg.first)) {
    return arg.first;
  }
};

}  // namespace details

template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<std::pair<const Key, T>>>
class map
    : public details::rb_tree<Key, std::pair<const Key, T>,
                              details::extract_first<std::pair<const Key, T>>,
                              Compare, Alloc, true> {
 private:
  using base_type =
      details::rb_tree<Key, std::pair<const Key, T>,
                       details::extract_first<std::pair<const Key, T>>, Compare,
                       Alloc, true>;
  using this_type = map<Key, T, Compare, Alloc>;

 public:
  using typename base_type::key_type;
  using mapped_type = T;
  using typename base_type::const_iterator;
  using typename base_type::const_reference;
  using typename base_type::difference_type;
  using typename base_type::iterator;
  using typename base_type::reference;
  using typename base_type::size_type;
  using typename base_type::value_type;

 public:
  map() {}
  map(const std::initializer_list<value_type>& items) : base_type(items) {}
  map(const this_type& o) : base_type(o) {}
  map(this_type&& o) noexcept : base_type(std::move(o)) {}
  this_type& operator=(const this_type& o) {
    return base_type::operator=(o), *this;
  }
  this_type& operator=(this_type&& o) noexcept {
    return base_type::operator=(std::move(o)), *this;
  }
  ~map() {}

  mapped_type& operator[](const Key& key) {
    return base_type::insert(value_type(key, mapped_type())).first->second;
  }
  mapped_type& at(const Key& key);
  const mapped_type& at(const Key& key) const {
    return const_cast<map*>(this)->at(key);
  }

  using base_type::insert;
  template <typename K, typename M>
  std::pair<iterator, bool> insert(K&& key, M&& obj) {
    return base_type::insert(
        value_type(std::forward<K>(key), std::forward<M>(obj)));
  }
  template <typename K, typename M>
  std::pair<iterator, bool> insert_or_assign(K&& key, M&& obj);
};

template <typename Key, typename T, typename Compare, typename Alloc>
typename map<Key, T, Compare, Alloc>::mapped_type&
map<Key, T, Compare, Alloc>::at(const Key& key) {
  if (auto it = base_type::find(key); it != base_type::end()) {
    return it->second;
  } else {
    throw std::out_of_range("s21::map::at(). invalid key.");
  }
}

template <typename Key, typename T, typename Compare, typename Alloc>
template <typename K, typename M>
std::pair<typename map<Key, T, Compare, Alloc>::iterator, bool>
map<Key, T, Compare, Alloc>::insert_or_assign(K&& key, M&& obj) {
  if (auto it = base_type::find(key); it != base_type::end()) {
    it->second = std::forward<M>(obj);
    return std::make_pair(it, false);
  } else {
    return insert(key, obj);
  }
}

}  // namespace s21

#endif  // S21_MAP_H_
