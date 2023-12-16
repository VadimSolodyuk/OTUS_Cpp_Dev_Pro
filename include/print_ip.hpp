#pragma once

#include <bits/utility.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <list>
#include <memory>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <vector>

using namespace std;

template <typename T> union Some_integer_to_bytes {
  T some_int;

  void print_bytes() {
    size_t index{0};
    for_each(bytes.crbegin(), bytes.crend(), [&index](const auto &iter) {
      if (index == 0)
        cout << static_cast<int>(iter);
      else
        cout << "." << static_cast<int>(iter);
      index++;
    });
    cout << endl;
  }

private:
  array<unsigned char, sizeof(T)> bytes;
};

template <typename T> enable_if_t<is_integral<T>::value> print_ip(T var) {
  Some_integer_to_bytes<T> u;
  u.some_int = var;
  u.print_bytes();
}

template <typename T, typename = typename T::iterator> void print_ip(T var) {
  for (auto it = var.cbegin(); it != var.cend(); ++it) {
    if (it == var.cbegin())
      cout << *it;
    else
      cout << "." << *it;
  }
  cout << endl;
}

template <> inline void print_ip<string>(string var) { cout << var << endl; }

template <typename Head, typename... Tail> struct is_equal_type {
  static const bool value = (is_same<Head, Tail>::value && ...); // NOLINT
};

template <typename Head, typename... Tail> struct equal_type_tuple {};

template <typename Head, typename... Tail>
struct equal_type_tuple<tuple<Head, Tail...>> : is_equal_type<Head, Tail...> {};

template <typename tupleT, size_t... index>
enable_if_t<equal_type_tuple<tupleT>::value>
print_tuple(tupleT tup, index_sequence<index...>) {

  auto print_element = [](const auto &element_tuple, size_t ind) {
    if (ind == 0)
      cout << element_tuple;
    else
      cout << "." << element_tuple;
  };

  (print_element(get<index>(tup), index), ...); // NOLINT
  cout << endl;
}

template <typename tupleT, size_t tupleSize = tuple_size<tupleT>::value>
void print_ip(tupleT tup) {
  print_tuple(tup, make_index_sequence<tupleSize>{});
}