#pragma once 
#include <concepts>
#include <string>

template<typename T>
concept has_string_repr = requires(T a){
    {std::to_string(a)};
};

template<typename T>
concept has_string_method = requires(T a){
    {a.to_string()} -> std::convertible_to<std::string>;
};

template<typename T>
concept has_string_init = requires(T a){
    {std::string(a)};
};

template<typename T>
concept is_string_repr = has_string_repr<T> || has_string_method<T> || has_string_init<T>;

template<typename ... Args>
constexpr bool _is_all_string_repr = (is_string_repr<Args> && ...);

template<typename ... Args>
concept all_string_repr = _is_all_string_repr<Args...>;

template<typename Dest, typename ... Args>
constexpr bool all_convertible = (std::convertible_to<Dest, Args> && ...);


template<typename Dest,typename ...Args>
concept is_all_convertible = all_convertible<Dest, Args...>;