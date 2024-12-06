#include <iostream>
#include <type_traits>

/// x.将value设置为false
struct false_type { static const bool value{false}; };

/// x.将value设置为true
struct true_type { static const bool value{true}; };

/// 2.通过继承false_type能够简化代码，方便快捷，无须每个类都写一遍成员的赋值语句。
template <typename T>
struct my_is_integral : false_type {};

/// 3.将模板特化为int类型，这样value的值就为true。
/// 通过穷举所有类型的特化模板，就能实现类型判断。
template <>
struct my_is_integral<int> : true_type {};

/// 4.创建变量的模板，相当于一个快捷方式，不需要使用类名作为限定名
template <typename T>
constexpr bool my_is_integral_v{my_is_integral<T>::value};

/// 5.为了解决const或volatile修饰的类型无法获得正确结果，
/// 因此引入了std::remove_cv去除修饰符。由此需要对代码进行修改
/// 这里引入了一个新的工具类my_is_integral_helper。
template <typename T>
struct my_is_integral_helper : false_type {};

/// 5.特化int类型模板
template <>
struct my_is_integral_helper<int> : true_type {};

/// 6.这里为了展示效果重新构建了一个类my_is_integral_cv，
/// 实际上这个类完全可以是my_is_integral。
/// 这里的typename std::remove_cv<T>::type的含义是，使用std::remove_cv
/// 去除const修饰符之后的类型名称。
template <typename T>
struct my_is_integral_cv :
my_is_integral_helper<typename std::remove_cv<T>::type> {};

/// 7.创建变量的模板，即快捷方式
template <typename T>
constexpr bool my_is_integral_cv_v{my_is_integral_cv<T>::value};

int main()
{
    // 3.判断对应的类型
    std::cout << std::boolalpha; // 输出布尔类型字符串
    std::cout << my_is_integral<int>::value << std::endl;
    std::cout << my_is_integral<float>::value << std::endl;

    // 4.通过快捷名称调用
    std::cout << my_is_integral_v<int> << std::endl;
    std::cout << my_is_integral_v<float> << std::endl;

    // 4.对于有const或volatile修饰的类型仍然不能获得正确结果
    std::cout << my_is_integral_v<const int> << std::endl;
    std::cout << my_is_integral_v<volatile int> << std::endl;

    // 8.判断const或volatile修饰的类型
    std::cout << my_is_integral_cv_v<const int> << std::endl;
    std::cout << my_is_integral_cv_v<volatile float> << std::endl;
    return 0;
}