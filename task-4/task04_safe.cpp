#include <iostream>

int main()
{
    int a{7};
    int b{2};
    double c{static_cast<double>(a) / static_cast<double>(b)};
    double d{static_cast<double>(a) / static_cast<double>(b)};
    std::cout << c << ' ' << d << '\n';

    char ch{static_cast<char>('A' + 2)};
    std::cout << ch << ' ' << static_cast<int>(ch + 1) << '\n';

    bool flag{5 != 0};
    std::cout << flag << ' ' << std::boolalpha << flag << '\n';

    unsigned int u{1};
    long long s{-1};
    std::cout << (s < static_cast<long long>(u) ? "s < u" : "s >= u") << '\n';

    return 0;
}
