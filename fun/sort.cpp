#ifndef DEPENDENCIES
#define DEPENDENCIES

#define LENGTH_THRESHOLD 24
#define BLOLCKSIZE 64
#define CACHE_SIZE 64
#define MOVE(x) std::move(x)

#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>
#endif

namespace sort_algo {
// Insertion sort(begin, end, comp_fn); in-place sorting
template <class Iter, class Compare>
inline void insertion_sort(Iter begin, Iter end, Compare comp) {
  typedef typename std::iterator_traits<Iter>::value_type T;
  if (begin == end)
    return;
  for (Iter current = begin + 1; current != end; ++current) {
    Iter c1 = current;
    Iter c0 = current - 1;

    if (comp(*c1, *c0)) {
      T tmp = MOVE(*c1);
      do {
        *c1 = MOVE(*c0);
        --c1;
        --c0;
      } while (c1 != begin && comp(tmp, *c0));
      *c1 = MOVE(tmp);
    }
  }
}

template <class Iter, class Compare>
inline void merge(Iter begin, Compare comp, size_t left, size_t middle,
                  size_t right) {
  typedef typename std::iterator_traits<Iter>::value_type T;
  std::vector<T> vec;
  vec.reserve(left + right);
  Iter p1 = begin + left, p2 = begin + middle, p1_end = begin + middle,
       p2_end = begin + right;
  do {
    if (comp(*p1, *p2)) {
      vec.push_back(*p1);
      ++p1;
    } else {
      vec.push_back(*p2);
      ++p2;
    }
  } while (p1 != p1_end && p2 != p2_end);

  if (p1 != p1_end) {
    do {
      vec.push_back(*p1);
      ++p1;
    } while (p1 != p1_end);
  } else if (p2 != p2_end) {
    do {
      vec.push_back(*p2);
      ++p2;
    } while (p2 != p2_end);
  }

  Iter cur = begin + left;
  for (auto val : vec)
    *cur++ = MOVE(val);
}

template <class Iter, class Compare>
void merge_sort(Iter begin, Compare comp, size_t left, size_t right) {
  auto len = right - left;

  if (len <= 0)
    return;
  else if (len <= LENGTH_THRESHOLD)
    insertion_sort(begin + left, begin + right, comp);
  else {
    size_t middle = (left + right) / 2;
    merge_sort(begin, comp, left, middle);
    merge_sort(begin, comp, middle, right);
    merge(begin, comp, left, middle, right);
  }
}
template <class Iter, class Compare>
inline int partition(Iter begin, Compare comp, int low, int high) {
  typedef typename std::iterator_traits<Iter>::value_type T;
  T pivot_elem = *(begin + high - 1);
  int i = low;

  Iter p1 = begin + low;
  Iter p2 = begin + low;
  Iter p1_end = begin + high - 1;

  for (; p1 != p1_end; ++p1) {
    if (comp(*p1, pivot_elem)) {
      if (p1 != p2) {
        T tmp = MOVE(*p2);
        *p2 = MOVE(*p1);
        *p1 = MOVE(tmp);
      }
      ++i;
      ++p2;
    }
  }

  T tmp = MOVE(*p2);
  *p2 = MOVE(*p1_end);
  *p1 = MOVE(tmp);

  return i;
}

template <class Iter, class Compare>
void quick_sort(Iter begin, Compare comp, int low, int high) {
  auto len = high - low;
  if (len <= 0)
    return;
  else if (len <= LENGTH_THRESHOLD)
    insertion_sort(begin + low, begin + high, comp);
  else {
    auto pivot = partition(begin, comp, low, high);
    quick_sort(begin, comp, low, pivot);
    quick_sort(begin, comp, pivot + 1, high);
  }
}

template <class T> struct node {
  T data;
  node *next;
  node *tail;
};

template <class T> struct NodeIterator {
  using iterator_category = std::forward_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = node<T>;
  using pointer = node<T> *;
  using reference = node<T> &;

  NodeIterator<T>(pointer ptr) : m_ptr(ptr) {}

  reference operator*() const { return *m_ptr; }
  pointer operator->() { return m_ptr; }

  NodeIterator<T> operator++() {
    m_ptr = m_ptr->next;
    return *this;
  }
  NodeIterator<T> operator++(int) {
    NodeIterator<T> tmp = *this;
    m_ptr = m_ptr->next;
    return tmp;
  }
  friend bool operator==(const NodeIterator<T> &a, const NodeIterator<T> &b) {
    return a.m_ptr == b.m_ptr;
  }
  friend bool operator!=(const NodeIterator<T> &a, const NodeIterator<T> &b) {
    return a.m_ptr != b.m_ptr;
  }

private:
  pointer m_ptr;
};

template <class Iter, class Compare>
inline typename std::iterator_traits<Iter>::value_type
find_max(Iter begin, Iter end, Compare comp) {
  typedef typename std::iterator_traits<Iter>::value_type T;
  T max_val = *begin;
  for (auto ite = begin + 1; ite != end; ++ite) {
    if (comp(max_val, *ite))
      max_val = *ite;
  }
  return max_val;
}

template <class Iter, class Compare>
inline void radix_sort(Iter begin, Iter end, Compare comp) {
  typedef typename std::iterator_traits<Iter>::value_type T;
  size_t size = std::distance(begin, end);
  T buffer[size];

  T max_val = find_max(begin, end, comp);
  for (int exp = 1; max_val / exp >= 1; exp *= 10) {
    unsigned int counts[10] = {0};
    for (auto ite = begin; ite != end; ++ite) {
      int idx = static_cast<int>(std::floor((*ite / exp) % 10));
      ++counts[idx];
    }
    for (int i = 1; i < 10; ++i)
      counts[i] += counts[i - 1];

    // auto ite = end-1;
    // for (auto [i, ite] = std::tuple{size - 1, end - 1}; i >= 0; --i, --ite) {
    // for (int i = size - 1; i >= 0; --i, --ite) {
    for (auto ite = end - 1; ite != begin - 1; --ite) {
      int idx = static_cast<int>(std::floor((*ite / exp) % 10));
      buffer[counts[idx] - 1] = MOVE(*ite);
      --counts[idx];
    }

    for (auto [ite, k] = std::tuple{begin, 0}; ite != end; ++ite, ++k)
      *ite = MOVE(buffer[k]);
  }
}

// template <class Iter, class Compare>
// inline void radix_sort_old(Iter begin, Iter end, Compare comp) {
// Iter o_begin = begin, o_end = end;
//
// typedef typename std::iterator_traits<Iter>::value_type T;
// node<T> *arr1[10] = {nullptr}, *arr2[10] = {nullptr};
// node<T> **a1 = arr1, **a2 = arr2;
//
// auto max = find_max(begin, end, comp);
// int num_loops = std::floor(std::log10(max));
//
// for (int i = 0; i <= num_loops; ++i) {
// for (auto ite = begin; ite != end; ++ite) {
// T val = std::floor((*ite / std::floor(std::pow(10, i))) % 10);
// int idx = dynamic_cast<int>(val);
// if (a1[idx] != nullptr) {
// auto n = a1[idx];
// node new_node = {*ite, nullptr, nullptr};
// n.tail->next = &new_node;
// n.tail = &new_node;
// } else {
// node new_node = {*ite, nullptr, nullptr};
// a1[idx] = new_node;
// a1[idx].tail = &new_node;
// }
// }
// for (int j = 0, k=0; j < 9; ++j, k+=1) {
// a1[j].tail->next = &a1[j + 1];
// a2[k] = nullptr;
// a2[k+1] = nullptr;
// }
//
// begin = NodeIterator<T>(&a1[0]);
// end = nullptr;
//
// auto tmp = a1;
// a1 = a2;
// a2 = tmp;
// }
//
// for (auto ite = o_begin; ite != o_end; ++ite)
// {
// *ite = *begin;
// ++begin;
// }
// }
//

template <class Iter>
inline void print_first_10_elem(Iter begin, int size, int MAX_SIZE = 10) {
  int n = size >= MAX_SIZE ? MAX_SIZE : size;
  for (int i = 0; i < n; ++i) {
    std::cout << *(begin + i) << (i == n - 1 ? "\n" : ",");
  }
}

int main() {
  int n = 1000000;
  std::vector<int> vec;
  vec.reserve(n);
  for (int i = 0; i < n; ++i){
    vec.push_back(i);
  }

  std::cout << "before: \n";
  print_first_10_elem(vec.begin(), n, 100);
  // insertion_sort(vec.begin(), vec.end(), std::less<int>());
  // merge_sort(vec.begin(), std::less<int>(), 0, vec.size());
  std::random_shuffle(vec.begin(), vec.end());
  quick_sort(vec.begin(), std::less<int>(), 0, vec.size());
  // radix_sort(vec.begin(), vec.end(), std::less<int>());
  std::cout << "after: \n";
  print_first_10_elem(vec.begin(), n, 100);

  return 0;
}
} // namespace sort_algo
// } // namespace sort_algo
//
int main() { sort_algo::main(); }
//
