#pragma once
#include "traits.hpp"
#include <iterator>
#include <string>
#include <utility>
#include <vector>

template<typename T> requires has_string_repr<T>
constexpr inline std::string as_string(T&& t){
    return std::to_string(t);
}

template<typename T> requires has_string_method<T>
constexpr inline std::string as_string(T &&t){
    return t.to_string();
}

template<typename T> requires has_string_init<T>
constexpr inline std::string as_string(T&&t){
    return std::string{t};
}

template<typename ... Args> requires all_string_repr<Args...>
std::vector<std::string> as_string_vector(Args&&...args){
    return {as_string(args)...};
}


template<typename T> requires is_string_repr<T>
std::string join(std::vector<T>& vector, char sep = ' '){
    std::string res= "";
    for(auto&e: vector){
        res += as_string(e) + sep;
    }    
    return res;
}


