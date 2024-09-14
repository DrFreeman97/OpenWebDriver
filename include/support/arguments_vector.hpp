#pragma once
#include "support/functionals.hpp"
#include "traits.hpp"
#include <string>
#include <vector>

struct Argument {
  std::string flag;
  std::vector<std::string> values{};
  bool multi_flag = true;

  std::string to_string() const { return to_string(' '); }
  std::string to_string(char argsep) const;
};

struct ArgumentVector {
private:
  std::vector<Argument> arguments{};

public:
  ArgumentVector &add_argument(std::string flag, bool multi_flag,
                               std::vector<std::string> values);
  template <typename... Args>
    requires all_string_repr<std::string, Args...>
  ArgumentVector &add_argument(std::string flag, bool multi_flag,
                               Args... args);
  template <typename... Args>
    requires all_string_repr<std::string, Args...>
  ArgumentVector &add_argument(std::string flag, Args... args);
  
  std::vector<std::string> argv();
};

template <typename... Args>
  requires all_string_repr<std::string, Args...>
inline ArgumentVector &ArgumentVector::add_argument(std::string flag,
                                                    bool multi_flag,
                                                    Args... args) {
  return add_argument(flag, multi_flag, as_string_vector(args...));
}

template<typename...Args>
 requires all_string_repr<std::string, Args...>
inline ArgumentVector &ArgumentVector::add_argument(std::string flag, Args... args) {
    return add_argument(flag,false,args...);
}

