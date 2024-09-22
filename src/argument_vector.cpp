#include "support/functionals.hpp"
#include <algorithm>
#include <support/arguments_vector.hpp>
#include <vector>

std::vector<std::string> ArgumentVector::argv() {
  std::vector<std::string> argv{};
  for (auto const &argument : arguments) {
    if (!argument.multi_flag) {
      argv.push_back(argument.flag);
    }
    for (auto val : argument.values) {
      if (argument.multi_flag) {
        argv.push_back(argument.flag);
      }
      argv.push_back(val);
    }
  }
  return argv;
}

std::string Argument::to_string(char argsep) const {
  std::string res = "";
  if (!this->multi_flag) {
    res += flag + " ";
    for (auto &e : values) {
      res += e + argsep;
    }
  } else {
    for (auto &e : values) {
      res += flag + " " + e + " ";
    }
  }
  return res;
}

ArgumentVector &ArgumentVector::add_argument(std::string flag,
                                             bool one_flag_only,
                                             std::vector<std::string> values) {
  if (!std::any_of(arguments.begin(), arguments.end(),
                   [&flag](const Argument &arg) { return arg.flag == flag; })) {
    arguments.push_back(Argument{flag, values, one_flag_only});
  }
  return *this;
}
