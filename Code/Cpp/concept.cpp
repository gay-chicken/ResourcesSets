#include <type_traits>

// concept 是 bool 类型的编译期常量。

template <typename T>
constexpr bool UniversalType = sizeof(T) != sizeof(int);

template <typename T>
requires std::is_trivial_v<T>
void f(T t) {}

template <typename T>
requires UniversalType<T>
void f(T t) {}

template <typename T>
requires requires {
    std::is_trivial_v<T>;
    UniversalType<T>;
}
void f(T t) {}

template <typename T>
concept SpecifyType = requires {
    std::is_trivial_v<T>;
    UniversalType<T>;
};

template <typename T>
requires SpecifyType<T>
void f(T t) {}

template <typename T>
concept OnlyType = requires {
    SpecifyType<T>;
    UniversalType<T>;
};