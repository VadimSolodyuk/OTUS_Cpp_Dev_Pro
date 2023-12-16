#include "../include/print_ip.hpp"

int main() {

  print_ip(int8_t{-1});                   // print: 255
  print_ip(int16_t{0});                   // print: 0.0
  print_ip(int32_t{2130706433});          // print: 127.0.0.1
  print_ip(int64_t{8875824491850138409}); // print: 123.45.67.89.101.112.131.41

  print_ip(string{"Hello, World!"});         // print: Hello, World!
  print_ip(vector<int>{100, 200, 300, 400}); // print: 100.200.300.400
  print_ip(list<short>{400, 300, 200, 100}); // print: 400.300.200.100

  print_ip(std::make_tuple(123, 456, 789, 0)); // print: 123.456.789.0
}