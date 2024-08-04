#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

#pragma once

#include <initializer_list>
#include <memory>
#include <stdexcept>

namespace s21 {

template <typename T, std::size_t N>
class array {
 private:
  using this_type = array<T, N>;

 public:
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;
  using iterator = T*;
  using const_iterator = const T*;

 public:
  constexpr reference operator[](size_type pos) noexcept { return data_[pos]; }
  constexpr const_reference operator[](size_type pos) const noexcept {
    return data_[pos];
  }
  constexpr reference at(size_type pos);
  constexpr const_reference at(size_type pos) const {
    return const_cast<this_type*>(this)->at(pos);
  }

  constexpr reference front() noexcept { return data_[0]; }
  constexpr const_reference front() const noexcept { return data_[0]; }
  constexpr reference back() noexcept { return data_[N - 1]; }
  constexpr const_reference back() const noexcept { return data_[N - 1]; }
  constexpr pointer data() noexcept { return data_; }
  constexpr const_pointer data() const noexcept { return data_; }

  constexpr iterator begin() noexcept { return data_; }
  constexpr const_iterator begin() const noexcept { return data_; }
  constexpr iterator end() noexcept { return data_ + N; }
  constexpr const_iterator end() const noexcept { return data_ + N; }

  constexpr bool empty() const noexcept { return false; }
  constexpr size_type size() const noexcept { return N; }
  constexpr size_type max_size() const noexcept { return N; }

  constexpr void swap(this_type& o) noexcept { std::swap(*this, o); }
  constexpr void fill(const_reference val) noexcept {
    std::fill(data_, data_ + N, val);
  }

 public:
  value_type data_[N];
};

template <typename T, std::size_t N>
constexpr typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("s21::array::at(). pos is illegal.");
  }

  return data_[pos];
}

template <typename T>
class array<T, 0> {
 private:
  using this_type = array<T, 0>;

 public:
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;
  using iterator = T*;
  using const_iterator = const T*;

 public:
  constexpr reference operator[](size_type) noexcept { return nullptr; };
  constexpr const_reference operator[](size_type) const noexcept {
    return nullptr;
  }
  constexpr reference at(size_type) {
    throw std::out_of_range("s21::array::at(). array is empty.");
  }
  constexpr const_reference at(size_type pos) const {
    return const_cast<this_type*>(this)->at(pos);
  }

  constexpr reference front() noexcept { return *data(); }
  constexpr const_reference front() const noexcept { return *data(); }
  constexpr reference back() noexcept { return *data(); }
  constexpr const_reference back() const noexcept { return *data(); }
  constexpr pointer data() noexcept { return nullptr; }
  constexpr const_pointer data() const noexcept { return nullptr; }

  constexpr iterator begin() noexcept { return nullptr; }
  constexpr const_iterator begin() const noexcept { return nullptr; }
  constexpr iterator end() noexcept { return nullptr; }
  constexpr const_iterator end() const noexcept { return nullptr; }

  constexpr bool empty() const noexcept { return true; }
  constexpr size_type size() const noexcept { return 0; }
  constexpr size_type max_size() const noexcept { return 0; }

  void swap(this_type&) noexcept {}
  void fill(const_reference) noexcept {}
};

}  // namespace s21

#endif  // S21_ARRAY_H