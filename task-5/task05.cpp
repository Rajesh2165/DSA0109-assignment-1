#include <iostream>

bool isPeakExpression(int hour) {
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}

bool isPeakTable(int hour) {
    if (hour < 0 || hour >= 24) {
        return false;
    }
    const bool peak[24] = {
        false, false, false, false, false, false, false, false,
        true,  true,  false, false, false, false, false, false,
        false, true,  true,  true,  false, false, false, false
    };
    return peak[hour];
}

int main()
{
    int x = 5, y = 3;
    std::cout << x + y * 2 << ' ' << (x + y) * 2 << '\n';

    int z = x++ + ++y;
    std::cout << z << ' ' << x << ' ' << y << '\n';

    std::cout << (x > y ? x : y) << ' ' << x % 4 * 2 << '\n';

    std::cout << 10 / 3 << ' ' << 10 % 3 << ' ' << -10 / 3 << ' ' << -10 % 3 << '\n';

    int k = 0;
    for (int i = 0; i < 10; i += 3) k += i;
    std::cout << k << '\n';

    std::cout << "\nMetro Peak Hour Validation (Hour 9 and Hour 14):\n";
    std::cout << "Hour 9 (Expression): " << isPeakExpression(9) << ", (Table): " << isPeakTable(9) << '\n';
    std::cout << "Hour 14 (Expression): " << isPeakExpression(14) << ", (Table): " << isPeakTable(14) << '\n';

    return 0;
}
