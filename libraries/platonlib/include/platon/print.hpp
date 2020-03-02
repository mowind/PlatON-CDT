#pragma once

#include <stdio.h>
#include <string>

namespace std {
string to_string(uint128_t value) {
  const char* charmap = "0123456789";
  string result;
  result.reserve(40);  // max. 40 digits possible ( uint64_t has 20)
  uint128_t helper = value;
  do {
    result += charmap[helper % 10];
    helper /= 10;
  } while (helper);
  reverse(result.begin(), result.end());
  return result;
}
}  // namespace std
namespace platon {

std::string all_info;

inline void print(const char* ptr) { all_info += ptr; }

inline void print(std::string info) { all_info += info; }

template <typename T,
          class = typename std::enable_if<
              std::numeric_limits<std::decay_t<T>>::is_integer ||
              std::numeric_limits<std::decay_t<T>>::is_iec559>::type>
inline void print(const T num) {
  if constexpr (std::is_same<T, char>::value) {
    all_info += num;
  } else if constexpr (std::is_same<T, bool>::value) {
    all_info += num ? "true" : "false";
  } else if constexpr (std::is_floating_point<T>::value) {
    double double_data = static_cast<double>(num);
    char temp_info[100] = {};
    sprintf(temp_info, "%lf", double_data);
    all_info += std::string(temp_info);
  } else {
    all_info += std::to_string(num);
  }
}

template <typename Arg, typename... Args>
void print(Arg&& a, Args&&... args) {
  print(std::forward<Arg>(a));
  print(" ");
  print(std::forward<Args>(args)...);
}

template <typename Arg, typename... Args>
void println(Arg&& a, Args&&... args) {
  all_info = "";
  print(std::forward<Arg>(a), std::forward<Args>(args)...);
  printf("%s\t\n", all_info.c_str());
}

#ifdef NDEBUG

  #define DEBUG(...) ((void)0)

#else

  #define DEBUG(...)                                                      \
    platon::println("line", __LINE__, "file", __FILE__, "func", __func__, \
                    ##__VA_ARGS__);

#endif

}  // namespace platon