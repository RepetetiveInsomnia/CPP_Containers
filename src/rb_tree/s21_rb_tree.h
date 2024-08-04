#ifndef S21_RB_TREE_H_
#define S21_RB_TREE_H_

#pragma once

#include <algorithm>
#include <cstdint>
#include <initializer_list>
#include <memory>
#include <stdexcept>

#include "../source/s21_vector.h"

namespace s21 {

namespace details {

class rb_tree_node_base {
 private:
  using this_type = rb_tree_node_base;

 public:
  enum class insertion_side : std::uint8_t {
    left,
    right,
  };

  enum class node_color : std::uint8_t {
    red,
    black,
  };

  using size_type = std::size_t;

 public:
  rb_tree_node_base()
      : left_(this),
        right_(this),
        parent_(nullptr),
        color_(node_color::black) {}

  this_type* increment() const noexcept;
  this_type* decrement() const noexcept;

  this_type* leftmost() const noexcept;
  this_type* rightmost() const noexcept;

  this_type* insert(this_type* const anchor, this_type* const parent,
                    const insertion_side side) noexcept;
  this_type* erase(this_type* const anchor) noexcept;

  static size_type black_amount(const this_type* const top,
                                const this_type* const bottom) noexcept;

 private:
  this_type* rotate_left(this_type* const node) const noexcept;
  this_type* rotate_right(this_type* const node) const noexcept;

 public:
  this_type* left_;
  this_type* right_;
  this_type* parent_;
  node_color color_;
};

rb_tree_node_base::this_type* rb_tree_node_base::increment() const noexcept {
  const this_type* node = this;

  if (!node->parent_) {
    return const_cast<this_type*>(node);
  }

  if (node->right_) {
    node = node->right_;

    while (node->left_) {
      node = node->left_;
    }
  } else {
    const this_type* tmp = node->parent_;

    while (node == tmp->right_) {
      node = tmp;
      tmp = tmp->parent_;
    }

    if (node->right_ != tmp) {
      node = tmp;
    }
  }

  return const_cast<this_type*>(node);
}

rb_tree_node_base::this_type* rb_tree_node_base::decrement() const noexcept {
  const this_type* node = this;

  if (!node->parent_) {
    return const_cast<this_type*>(node);
  }

  if ((node->parent_->parent_ == node) && (node->color_ == node_color::red)) {
    return node->right_;
  } else if (node->left_) {
    const this_type* tmp = node->left_;

    while (tmp->right_) {
      tmp = tmp->right_;
    }

    return const_cast<this_type*>(tmp);
  }

  const this_type* tmp = node->parent_;

  while (node == tmp->left_) {
    node = tmp;
    tmp = tmp->parent_;
  }

  return const_cast<this_type*>(tmp);
}

rb_tree_node_base::this_type* rb_tree_node_base::leftmost() const noexcept {
  const this_type* node = this;

  while (node->left_) {
    node = node->left_;
  }

  return const_cast<this_type*>(node);
}

rb_tree_node_base::this_type* rb_tree_node_base::rightmost() const noexcept {
  const this_type* node = this;

  while (node->right_) {
    node = node->right_;
  }

  return const_cast<this_type*>(node);
}

rb_tree_node_base::this_type* rb_tree_node_base::insert(
    this_type* const anchor, this_type* const parent,
    const insertion_side side) noexcept {
  this_type* node = this;
  this_type*& root = anchor->parent_;

  node->parent_ = parent;
  node->right_ = nullptr;
  node->left_ = nullptr;
  node->color_ = node_color::red;

  if (side == insertion_side::left) {
    parent->left_ = node;

    if (parent == anchor) {
      anchor->parent_ = node;
      anchor->right_ = node;
    } else if (parent == anchor->left_) {
      anchor->left_ = node;
    }
  } else {
    parent->right_ = node;

    if (parent == anchor->right_) {
      anchor->right_ = node;
    }
  }

  while ((node != root) && (node->parent_->color_ == node_color::red)) {
    this_type* const parent_parent = node->parent_->parent_;

    if (node->parent_ == parent_parent->left_) {
      this_type* const tmp = parent_parent->right_;

      if (tmp && (tmp->color_ == node_color::red)) {
        node->parent_->color_ = node_color::black;
        tmp->color_ = node_color::black;
        parent_parent->color_ = node_color::red;
        node = parent_parent;
      } else {
        if (node->parent_ && node == node->parent_->right_) {
          node = node->parent_;
          root = root->rotate_left(node);
        }

        node->parent_->color_ = node_color::black;
        parent_parent->color_ = node_color::red;
        root = root->rotate_right(parent_parent);
      }
    } else {
      this_type* const tmp = parent_parent->left_;

      if (tmp && (tmp->color_ == node_color::red)) {
        node->parent_->color_ = node_color::black;
        tmp->color_ = node_color::black;
        parent_parent->color_ = node_color::red;
        node = parent_parent;
      } else {
        if (node == node->parent_->left_) {
          node = node->parent_;
          root = root->rotate_right(node);
        }

        node->parent_->color_ = node_color::black;
        parent_parent->color_ = node_color::red;
        root = root->rotate_left(parent_parent);
      }
    }
  }
  root->color_ = node_color::black;

  return anchor;
}

rb_tree_node_base::this_type* rb_tree_node_base::erase(
    this_type* const anchor) noexcept {
  this_type* node = this;
  this_type*& root = anchor->parent_;
  this_type*& leftmost = anchor->left_;
  this_type*& rightmost = anchor->right_;
  this_type* successor = node;
  this_type* child = nullptr;
  this_type* child_parent = nullptr;

  if (!successor->left_) {
    child = successor->right_;
  } else if (!successor->right_) {
    child = successor->left_;
  } else {
    successor = successor->right_;

    while (successor->left_) {
      successor = successor->left_;
    }

    child = successor->right_;
  }

  if (successor == node) {
    child_parent = successor->parent_;

    if (child) {
      child->parent_ = successor->parent_;
    }

    if (node == root) {
      root = child;
    } else {
      if (node == node->parent_->left_) {
        node->parent_->left_ = child;
      } else {
        node->parent_->right_ = child;
      }
    }

    if (node == leftmost) {
      if (node->right_ && child) {
        leftmost = child->leftmost();
      } else {
        leftmost = node->parent_;
      }
    }

    if (node == rightmost) {
      if (node->left_ && child) {
        rightmost = child->rightmost();
      } else {
        rightmost = node->parent_;
      }
    }
  } else {
    node->left_->parent_ = successor;
    successor->left_ = node->left_;

    if (successor == node->right_) {
      child_parent = successor;
    } else {
      child_parent = successor->parent_;

      if (child) {
        child->parent_ = child_parent;
      }

      child_parent->left_ = child;

      successor->right_ = node->right_;
      node->right_->parent_ = successor;
    }

    if (node == root) {
      root = successor;
    } else if (node == node->parent_->left_) {
      node->parent_->left_ = successor;
    } else {
      node->parent_->right_ = successor;
    }

    successor->parent_ = node->parent_;
    std::swap(successor->color_, node->color_);
  }

  if (node->color_ == node_color::black) {
    while ((child != root) &&
           ((!child) || (child->color_ == node_color::black))) {
      if (child == child_parent->left_) {
        this_type* tmp = child_parent->right_;

        if (tmp->color_ == node_color::red) {
          tmp->color_ = node_color::black;
          child_parent->color_ = node_color::red;
          root = root->rotate_left(child_parent);
          tmp = child_parent->right_;
        }

        if (((!tmp->left_) || (tmp->left_->color_ == node_color::black)) &&
            ((!tmp->right_) || (tmp->right_->color_ == node_color::black))) {
          tmp->color_ = node_color::red;
          child = child_parent;
          child_parent = child_parent->parent_;
        } else {
          if ((!tmp->right_) || (tmp->right_->color_ == node_color::black)) {
            tmp->left_->color_ = node_color::black;
            tmp->color_ = node_color::red;
            root = root->rotate_right(tmp);
            tmp = child_parent->right_;
          }

          tmp->color_ = child_parent->color_;
          child_parent->color_ = node_color::black;

          if (tmp->right_) {
            tmp->right_->color_ = node_color::black;
          }

          root = root->rotate_left(child_parent);
          break;
        }
      } else {
        this_type* tmp = child_parent->left_;

        if (tmp->color_ == node_color::red) {
          tmp->color_ = node_color::black;
          child_parent->color_ = node_color::red;

          root = root->rotate_right(child_parent);
          tmp = child_parent->left_;
        }

        if (((!tmp->right_) || (tmp->right_->color_ == node_color::black)) &&
            ((!tmp->left_) || (tmp->left_->color_ == node_color::black))) {
          tmp->color_ = node_color::red;
          child = child_parent;
          child_parent = child_parent->parent_;
        } else {
          if ((!tmp->left_) || (tmp->left_->color_ == node_color::black)) {
            tmp->right_->color_ = node_color::black;
            tmp->color_ = node_color::red;

            root = root->rotate_left(tmp);
            tmp = child_parent->left_;
          }

          tmp->color_ = child_parent->color_;
          child_parent->color_ = node_color::black;

          if (tmp->left_) {
            tmp->left_->color_ = node_color::black;
          }

          root = root->rotate_right(child_parent);
          break;
        }
      }
    }

    if (child) {
      child->color_ = node_color::black;
    }
  }

  return anchor;
}

rb_tree_node_base::size_type rb_tree_node_base::black_amount(
    const this_type* top, const this_type* bottom) noexcept {
  size_type n = 0;

  for (const this_type* i = bottom; i; i = i->parent_) {
    if (i->color_ == node_color::black) {
      ++n;
    }

    if (i == top) {
      break;
    }
  }

  return n;
}

rb_tree_node_base::this_type* rb_tree_node_base::rotate_left(
    this_type* const node) const noexcept {
  const this_type* root = this;
  this_type* tmp = node->right_;

  node->right_ = tmp->left_;

  if (tmp->left_) {
    tmp->left_->parent_ = node;
  }
  tmp->parent_ = node->parent_;

  if (node == root) {
    root = tmp;
  } else if (node == node->parent_->left_) {
    node->parent_->left_ = tmp;
  } else {
    node->parent_->right_ = tmp;
  }

  tmp->left_ = node;
  node->parent_ = tmp;

  return const_cast<this_type*>(root);
}

rb_tree_node_base::this_type* rb_tree_node_base::rotate_right(
    this_type* const node) const noexcept {
  const this_type* root = this;
  this_type* const tmp = node->left_;

  node->left_ = tmp->right_;

  if (tmp->right_) {
    tmp->right_->parent_ = node;
  }
  tmp->parent_ = node->parent_;

  if (node == root) {
    root = tmp;
  } else if (node == node->parent_->right_) {
    node->parent_->right_ = tmp;
  } else {
    node->parent_->left_ = tmp;
  }

  tmp->right_ = node;
  node->parent_ = tmp;

  return const_cast<this_type*>(root);
}

template <typename T>
class rb_tree_node : public rb_tree_node_base {
 private:
  using this_type = rb_tree_node<T>;
  using base_type = rb_tree_node_base;

 public:
  using value_type = T;

 public:
  rb_tree_node() : val_() {}
  rb_tree_node(const value_type& val) : val_(val) {}
  rb_tree_node(value_type&& val) noexcept : val_(std::move(val)) {}

 public:
  value_type val_;
};

template <typename T, typename Pointer, typename Reference>
class rb_tree_iterator {
 private:
  using this_type = rb_tree_iterator<T, Pointer, Reference>;
  using node_base_type = rb_tree_node_base;
  using node_type = rb_tree_node<T>;

  using iterator = rb_tree_iterator<T, T*, T&>;
  using const_iterator = rb_tree_iterator<T, const T*, const T&>;

 public:
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = Pointer;
  using reference = Reference;
  using iterator_category = std::bidirectional_iterator_tag;

 public:
  rb_tree_iterator(const node_base_type* node_base) noexcept
      : node_base_(const_cast<node_base_type*>(node_base)) {}
  rb_tree_iterator(const iterator& o) noexcept : node_base_(o.node_base_) {}
  rb_tree_iterator(const const_iterator& o) noexcept
      : node_base_(const_cast<node_base_type*>(o.node_base_)) {}
  this_type& operator=(const iterator& o) noexcept {
    return node_base_ = o.node_base_, *this;
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
    return node_base_ = node_base_->increment(), *this;
  }
  this_type operator++(int) noexcept;

  this_type& operator--() noexcept {
    return node_base_ = node_base_->decrement(), *this;
  }
  this_type operator--(int) noexcept;

 public:
  node_base_type* node_base_;
};

template <typename T, typename Pointer, typename Reference>
typename rb_tree_iterator<T, Pointer, Reference>::this_type
rb_tree_iterator<T, Pointer, Reference>::operator++(int) noexcept {
  this_type tmp(node_base_);
  node_base_ = node_base_->increment();

  return tmp;
}

template <typename T, typename Pointer, typename Reference>
typename rb_tree_iterator<T, Pointer, Reference>::this_type
rb_tree_iterator<T, Pointer, Reference>::operator--(int) noexcept {
  this_type tmp(node_base_);
  node_base_ = node_base_->decrement();

  return tmp;
}

template <typename T, typename LPointer, typename LReference, typename RPointer,
          typename RReference>
inline bool operator==(
    const rb_tree_iterator<T, LPointer, LReference>& lhs,
    const rb_tree_iterator<T, RPointer, RReference>& rhs) noexcept {
  return lhs.node_base_ == rhs.node_base_;
}

template <typename T, typename LPointer, typename LReference, typename RPointer,
          typename RReference>
inline bool operator!=(
    const rb_tree_iterator<T, LPointer, LReference>& lhs,
    const rb_tree_iterator<T, RPointer, RReference>& rhs) noexcept {
  return lhs.node_base_ != rhs.node_base_;
}

template <typename T, typename Alloc>
class rb_tree_base {
 private:
  using this_type = rb_tree_base<T, Alloc>;

  using t_allocator_type = Alloc;
  using t_allocator_traits = std::allocator_traits<t_allocator_type>;
  using node_allocator_type =
      typename t_allocator_traits::template rebind_alloc<rb_tree_node<T>>;
  using node_allocator_traits = std::allocator_traits<node_allocator_type>;

 protected:
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using base_node_type = rb_tree_node_base;
  using node_type = rb_tree_node<T>;
  using insertion_side = typename base_node_type::insertion_side;

 protected:
  rb_tree_base() : node_alloc_(), node_base_(), size_() {}
  rb_tree_base(const this_type& o);
  rb_tree_base(this_type&& o) noexcept;
  this_type& operator=(const this_type& o);
  this_type& operator=(this_type&& o) noexcept;
  ~rb_tree_base() { clear(); }

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

 private:
  void copy(base_node_type* parent, const base_node_type* cp,
            const insertion_side side);
  void remove(base_node_type* del);
  void swap(base_node_type& node_base_other) noexcept;

 protected:
  static constexpr size_type max_size_ = size_type(0) - 2;

  node_allocator_type node_alloc_;
  base_node_type node_base_;
  size_type size_;
};

template <typename T, typename Alloc>
rb_tree_base<T, Alloc>::rb_tree_base(const this_type& o)
    : node_alloc_(o.node_alloc_), node_base_(), size_(o.size_) {
  if (size_ > 0) {
    copy(&node_base_, o.node_base_.parent_, insertion_side::left);
    node_base_.left_ = node_base_.parent_->leftmost();
    node_base_.right_ = node_base_.parent_->rightmost();
  }
}

template <typename T, typename Alloc>
rb_tree_base<T, Alloc>::rb_tree_base(this_type&& o) noexcept
    : node_alloc_(std::move(o.node_alloc_)),
      node_base_(),
      size_(std::move(o.size_)) {
  swap(o.node_base_);
  o.size_ = 0;
}

template <typename T, typename Alloc>
typename rb_tree_base<T, Alloc>::this_type& rb_tree_base<T, Alloc>::operator=(
    const this_type& o) {
  if (&o != this) {
    this_type res(o);
    *this = std::move(res);
  }

  return *this;
}

template <typename T, typename Alloc>
typename rb_tree_base<T, Alloc>::this_type& rb_tree_base<T, Alloc>::operator=(
    this_type&& o) noexcept {
  if (&o != this) {
    clear();

    // mb add check if allocator can be moved or copied using
    // allocator_traits::propagate_on_container_move_assignment::value
    node_alloc_ = std::move(o.node_alloc_);
    swap(o.node_base_);
    size_ = std::move(o.size_);

    o.size_ = 0;
  }

  return *this;
}

template <typename T, typename Alloc>
void rb_tree_base<T, Alloc>::clear() {
  remove(node_base_.parent_);

  node_base_.left_ = node_base_.right_ = &node_base_;
  node_base_.parent_ = nullptr;
  node_base_.color_ = base_node_type::node_color::black;
  size_ = 0;
}

template <typename T, typename Alloc>
void rb_tree_base<T, Alloc>::copy(base_node_type* parent,
                                  const base_node_type* cp,
                                  const insertion_side side) {
  if (cp) {
    auto deleter = [this](base_node_type* ptr) -> void {
      deallocate(ptr), clear();
    };
    std::unique_ptr<base_node_type, decltype(deleter)> utmp(allocate(),
                                                            deleter);
    construct(utmp.get(), static_cast<const node_type*>(cp)->val_);

    base_node_type* tmp = utmp.release();

    tmp->left_ = tmp->right_ = nullptr;
    tmp->parent_ = parent;
    tmp->color_ = cp->color_;

    if (!parent->parent_) {
      parent->parent_ = tmp;
    } else {
      if (side == insertion_side::left) {
        parent->left_ = tmp;
      } else {
        parent->right_ = tmp;
      }
    }

    copy(tmp, cp->left_, insertion_side::left);
    copy(tmp, cp->right_, insertion_side::right);
  }
}

template <typename T, typename Alloc>
void rb_tree_base<T, Alloc>::remove(base_node_type* del) {
  if (del) {
    remove(del->left_);
    remove(del->right_);

    destroy(del);
    deallocate(del);
  }
}

template <typename T, typename Alloc>
void rb_tree_base<T, Alloc>::swap(base_node_type& node_base_other) noexcept {
  if (node_base_.parent_ && node_base_other.parent_) {
    std::swap(node_base_.right_, node_base_other.right_);
    std::swap(node_base_.left_, node_base_other.left_);
    std::swap(node_base_.parent_, node_base_other.parent_);

    node_base_.parent_->parent_ = &node_base_;
    node_base_other.parent_->parent_ = &node_base_other;
  } else if (node_base_.parent_) {
    node_base_other.right_ = node_base_.right_;
    node_base_other.left_ = node_base_.left_;
    node_base_other.parent_ = node_base_.parent_;
    node_base_other.parent_->parent_ = &node_base_other;

    node_base_.right_ = &node_base_;
    node_base_.left_ = &node_base_;
    node_base_.parent_ = nullptr;
  } else if (node_base_other.parent_) {
    node_base_.right_ = node_base_other.right_;
    node_base_.left_ = node_base_other.left_;
    node_base_.parent_ = node_base_other.parent_;
    node_base_.parent_->parent_ = &node_base_;

    node_base_other.right_ = &node_base_other;
    node_base_other.left_ = &node_base_other;
    node_base_other.parent_ = nullptr;
  }
}

template <typename Key, typename T, typename ExtractKey, typename CompareKey,
          typename Alloc, bool UniqueKey>
class rb_tree : public details::rb_tree_base<T, Alloc> {
 private:
  using base_type = details::rb_tree_base<T, Alloc>;
  using this_type = rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>;

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

  using typename base_type::insertion_side;

 public:
  using typename base_type::difference_type;
  using typename base_type::size_type;
  using key_type = Key;
  using typename base_type::const_reference;
  using typename base_type::reference;
  using typename base_type::value_type;
  using iterator = details::rb_tree_iterator<T, T*, T&>;
  using const_iterator = details::rb_tree_iterator<T, const T*, const T&>;

 public:
  rb_tree() {}
  rb_tree(const std::initializer_list<value_type>& items) {
    std::for_each(items.begin(), items.end(),
                  [&](const auto& item) { insert(item); });
  }
  rb_tree(const this_type& o) : base_type(o) {}
  rb_tree(this_type&& o) noexcept : base_type(std::move(o)) {}
  this_type& operator=(const this_type& o) {
    return base_type::operator=(o), *this;
  }
  this_type& operator=(this_type&& o) noexcept {
    return base_type::operator=(std::move(o)), *this;
  }
  ~rb_tree() {}

  iterator begin() noexcept { return iterator(node_base_.left_); }
  const_iterator begin() const noexcept {
    return const_iterator(node_base_.left_);
  }
  iterator end() noexcept { return iterator(&node_base_); }
  const_iterator end() const noexcept { return const_iterator(&node_base_); }

  bool empty() const noexcept { return size_ == 0 && begin() == end(); }
  size_type size() const noexcept { return size_; }
  constexpr size_type max_size() const noexcept { return max_size_; }

  void clear() { base_type::clear(); }
  std::pair<iterator, bool> insert(value_type&& val);
  std::pair<iterator, bool> insert(const_reference val) {
    return insert(value_type(val));
  }
  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  iterator erase(const_iterator pos);
  size_type erase(const key_type& val) noexcept;
  void swap(this_type& o) noexcept { std::swap(*this, o); }
  template <typename OCompareKey, bool OUniqueKey>
  void merge(rb_tree<Key, T, ExtractKey, OCompareKey, Alloc, OUniqueKey>&& o);
  template <typename OCompareKey, bool OUniqueKey>
  void merge(rb_tree<Key, T, ExtractKey, OCompareKey, Alloc, OUniqueKey>& o) {
    merge(std::move(o));
  }

  size_type count(const key_type& val) const noexcept;
  iterator find(const key_type& val) noexcept;
  const_iterator find(const key_type& val) const noexcept {
    return const_cast<rb_tree*>(this)->find(val);
  }
  bool contains(const key_type& val) const noexcept {
    return find(val) != end();
  }
  std::pair<iterator, iterator> equal_range(const key_type& val) noexcept;
  std::pair<const_iterator, const_iterator> equal_range(
      const key_type& val) const noexcept {
    return const_cast<rb_tree*>(this)->equal_range(val);
  }
  iterator lower_bound(const key_type& val) noexcept;
  const_iterator lower_bound(const key_type& val) const noexcept {
    return const_cast<rb_tree*>(this)->lower_bound(val);
  }
  iterator upper_bound(const key_type& val) noexcept;
  const_iterator upper_bound(const key_type& val) const noexcept {
    return const_cast<rb_tree*>(this)->upper_bound(val);
  }

 private:
  auto extract_key(const_reference val) const noexcept {
    return ExtractKey()(val);
  }
  bool compare_key(const key_type& lhs, const key_type& rhs) const noexcept {
    return CompareKey()(lhs, rhs);
  }
  bool equal_key(const key_type& lhs, const key_type& rhs) const noexcept {
    return compare_key(lhs, rhs) == compare_key(rhs, lhs);
  }

  std::tuple<base_node_type*, base_node_type*, bool, bool> insert_pos(
      const key_type& val) noexcept;
};

template <typename Key, typename T, typename ExtractKey, typename CompareKey,
          typename Alloc, bool UniqueKey>
std::pair<typename rb_tree<Key, T, ExtractKey, CompareKey, Alloc,
                           UniqueKey>::iterator,
          bool>
rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::insert(
    value_type&& val) {
#ifdef DEBUG
  if (size_ == max_size()) {
    throw std::invalid_argument("s21::rb_tree::insert(). size too big.");
  }
#endif

  auto [cur, prev, can_insert, dir] = insert_pos(extract_key(val));

  if (!can_insert) {
    return std::make_pair(cur, can_insert);
  }

  auto deleter = [this](base_node_type* ptr) -> void { deallocate(ptr); };
  std::unique_ptr<base_node_type, decltype(deleter)> tmp(allocate(), deleter);
  construct(tmp.get(), std::move(val));

  node_base_ = *tmp->insert(&node_base_, prev,
                            dir ? insertion_side::left : insertion_side::right);
  ++size_;

  return std::make_pair(tmp.release(), can_insert);
}
/*
template <typename Key, typename T, typename ExtractKey, typename CompareKey,
typename Alloc, bool UniqueKey> template <typename... Args>
s21::vector<std::pair<typename rb_tree<Key, T, ExtractKey, CompareKey, Alloc,
UniqueKey>::iterator, bool>> rb_tree<Key, T, ExtractKey, CompareKey, Alloc,
UniqueKey>::insert_many(Args&&... args) { s21::vector<std::pair<iterator, bool>>
ret; for (auto elem : { std::forward<Args>(args)... }) {
        ret.push_back(insert(elem));
    }
    return ret;
}
*/
template <typename Key, typename T, typename ExtractKey, typename CompareKey,
          typename Alloc, bool UniqueKey>
template <typename... Args>
s21::vector<std::pair<typename rb_tree<Key, T, ExtractKey, CompareKey, Alloc,
                                       UniqueKey>::iterator,
                      bool>>
rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::insert_many(
    Args&&... args) {
  s21::vector<std::pair<iterator, bool>> ret;
  for (auto elem : {std::forward<Args>(args)...}) {
    ret.push_back(insert(elem));
  }
  return ret;
}
/*
template <typename Key, typename T, typename ExtractKey, typename CompareKey,
          typename Alloc, bool UniqueKey>
template <typename... Args>
s21::vector<std::pair<typename rb_tree<Key, T, ExtractKey, CompareKey, Alloc,
                                       UniqueKey>::iterator,
                      bool>>
rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::insert_many(
    Args&&... args) {
  s21::vector<std::pair<iterator, bool>> ret;
  for (auto elem : {std::forward<Args>(args)...}) {
    ret.push_back(insert(elem));
  }
  return ret;
}
*/
template <typename Key, typename T, typename ExtractKey, typename CompareKey,
          typename Alloc, bool UniqueKey>
typename rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::iterator
rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::erase(
    const_iterator pos) {
#ifdef DEBUG
  if (empty()) {
    throw std::out_of_range("s21::rb_tree::erase(). rb_tree is empty.");
  }

  if (pos == end()) {
    throw std::out_of_range("s21::rb_tree::erase(). pos is illegal.");
  }
#endif

  const iterator tmp = pos++;

  node_base_ = *tmp.node_base_->erase(&node_base_);
  destroy(tmp.node_base_);
  deallocate(tmp.node_base_);
  --size_;

  return pos;
}

template <typename Key, typename T, typename ExtractKey, typename CompareKey,
          typename Alloc, bool UniqueKey>
typename rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::size_type
rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::erase(
    const key_type& val) noexcept {
  size_type n = 0;

  for (auto [lower, upper] = equal_range(val); lower != upper;
       ++n, lower = erase(lower)) {
    ;
  }

  return n;
}

template <typename Key, typename T, typename ExtractKey, typename CompareKey,
          typename Alloc, bool UniqueKey>
typename rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::size_type
rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::count(
    const key_type& val) const noexcept {
  const auto [lower, upper] = equal_range(val);

  return std::distance(lower, upper);
}

template <typename Key, typename T, typename ExtractKey, typename CompareKey,
          typename Alloc, bool UniqueKey>
typename rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::iterator
rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::find(
    const key_type& val) noexcept {
  const base_node_type* cur = node_base_.parent_;
  const base_node_type* prev = &node_base_;

  while (cur) {
    if (!compare_key(extract_key(static_cast<const node_type*>(cur)->val_),
                     val)) {
      prev = cur;
      cur = cur->left_;
    } else {
      cur = cur->right_;
    }
  }

  return (prev != &node_base_ &&
          !compare_key(val,
                       extract_key(static_cast<const node_type*>(prev)->val_)))
             ? iterator(prev)
             : iterator(&node_base_);
}

template <typename Key, typename T, typename ExtractKey, typename CompareKey,
          typename Alloc, bool UniqueKey>
std::pair<typename rb_tree<Key, T, ExtractKey, CompareKey, Alloc,
                           UniqueKey>::iterator,
          typename rb_tree<Key, T, ExtractKey, CompareKey, Alloc,
                           UniqueKey>::iterator>
rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::equal_range(
    const key_type& val) noexcept {
  return std::make_pair(lower_bound(val), upper_bound(val));
}

template <typename Key, typename T, typename ExtractKey, typename CompareKey,
          typename Alloc, bool UniqueKey>
typename rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::iterator
rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::lower_bound(
    const key_type& val) noexcept {
  const base_node_type* cur = node_base_.parent_;
  const base_node_type* prev = &node_base_;

  while (cur) {
    if (!compare_key(extract_key(static_cast<const node_type*>(cur)->val_),
                     val)) {
      prev = cur;
      cur = cur->left_;
    } else {
      cur = cur->right_;
    }
  }

  return iterator(prev);
}

template <typename Key, typename T, typename ExtractKey, typename CompareKey,
          typename Alloc, bool UniqueKey>
typename rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::iterator
rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::upper_bound(
    const key_type& val) noexcept {
  const base_node_type* cur = node_base_.parent_;
  const base_node_type* prev = &node_base_;

  while (cur) {
    if (compare_key(val,
                    extract_key(static_cast<const node_type*>(cur)->val_))) {
      prev = cur;
      cur = cur->left_;
    } else {
      cur = cur->right_;
    }
  }

  return iterator(prev);
}

template <typename Key, typename T, typename ExtractKey, typename CompareKey,
          typename Alloc, bool UniqueKey>
template <typename OCompareKey, bool OUniqueKey>
void rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::merge(
    rb_tree<Key, T, ExtractKey, OCompareKey, Alloc, OUniqueKey>&& o) {
  if (this != &o && !o.empty()) {
#ifdef DEBUG
    if (node_alloc_ != o.node_alloc_) {
      throw std::runtime_error(
          "s21::rb_tree::merge(). cant merge tree with different allocator.");
    }
#endif

    for (auto it = o.begin(); it != o.end();) {
      auto [cur, prev, can_insert, dir] = insert_pos(extract_key(*it));

      base_node_type* node = (it++).node_base_;

      if (can_insert) {
        o.node_base_ = *node->erase(&o.node_base_);
        --o.size_;

        node_base_ =
            *node->insert(&node_base_, prev,
                          dir ? insertion_side::left : insertion_side::right);
        ++size_;
      }
    }
  }
}

template <typename Key, typename T, typename ExtractKey, typename CompareKey,
          typename Alloc, bool UniqueKey>
std::tuple<typename rb_tree<Key, T, ExtractKey, CompareKey, Alloc,
                            UniqueKey>::base_node_type*,
           typename rb_tree<Key, T, ExtractKey, CompareKey, Alloc,
                            UniqueKey>::base_node_type*,
           bool, bool>
rb_tree<Key, T, ExtractKey, CompareKey, Alloc, UniqueKey>::insert_pos(
    const key_type& val) noexcept {
  const base_node_type* cur = node_base_.parent_;
  const base_node_type* prev = &node_base_;

  bool comp = true;

  while (cur) {
    prev = cur;

    if constexpr (UniqueKey) {
      if (equal_key(val,
                    extract_key(static_cast<const node_type*>(cur)->val_))) {
        return std::make_tuple(const_cast<base_node_type*>(cur),
                               const_cast<base_node_type*>(cur->parent_), false,
                               false);
      }
    }

    comp =
        compare_key(val, extract_key(static_cast<const node_type*>(cur)->val_));
    cur = comp ? cur->left_ : cur->right_;
  }

  return std::make_tuple(const_cast<base_node_type*>(cur),
                         const_cast<base_node_type*>(prev), true, comp);
}

}  // namespace details

}  // namespace s21

#endif  // S21_RB_TREE_H_