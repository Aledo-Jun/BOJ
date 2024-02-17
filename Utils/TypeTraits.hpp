//
// Created by june0 on 2024-01-18.
//

#ifndef BOJ_TYPETRAITS_HPP
#define BOJ_TYPETRAITS_HPP

#include <type_traits>
namespace Utils::TypeTraits
{
    template<typename T>
    using is_signed_int =
            typename std::conditional_t<std::is_integral_v<T> && std::is_signed_v<T>,
                    std::true_type,
                    std::false_type>;

    template<typename T>
    using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;

    template<typename T>
    using is_unsigned_int =
            typename std::conditional_t<std::is_integral_v<T> && std::is_unsigned_v<T>,
                    std::true_type,
                    std::false_type>;

    template<typename T>
    using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;

    template<typename...> struct to_void { using type = void; };
    template<typename... Ts> using void_t = typename to_void<Ts...>::type;

    template<typename T, typename = void>
    struct supports_arithmetic : public std::false_type { };

    template<typename T>
    struct supports_arithmetic<T,
            void_t<decltype(std::declval<T>() + std::declval<T>()),
                   decltype(std::declval<T>() - std::declval<T>()),
                   decltype(std::declval<T>() * std::declval<T>()),
                   decltype(std::declval<T>() / std::declval<T>())>>
    : public std::true_type { };

    template<typename T>
    using supports_arithmetic_v = typename supports_arithmetic<T>::value;
}
#endif //BOJ_TYPETRAITS_HPP
