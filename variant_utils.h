#ifndef VARIANT_UTILS_H_
#define VARIANT_UTILS_H_

#include <variant>

namespace common {

template<class T> struct always_false : std::false_type {};

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

#define BEGIN_VARIANT(element) \
std::visit([&](const auto &element) { \
using ElementType = std::decay_t<decltype(element)>;

#define END_VARIANT(variants) \
else { \
    static_assert(always_false<ElementType>::value, "non-exhaustive visitor!"); \
} \
}, variants);

}

#endif // VARIANT_UTILS_H_