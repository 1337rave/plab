#include <iostream>
#include <string>

// Клас винятку для випадку переповнення типу int
class OverflowException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Overflow exception: Value is out of range of int type.";
    }
};

int parseInt(const std::string& str) {
    int result = 0;
    bool negative = false;
    size_t i = 0;

    // Обробка можливого знака мінус перед числом
    if (str[i] == '-') {
        negative = true;
        ++i;
    }

    // Обчислення значення числа з рядка символів
    for (; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            throw std::invalid_argument("Invalid input: Non-numeric character encountered.");
        }

        int digit = str[i] - '0';

        // Перевірка на переповнення
        if (negative) {
            // Перевірка на переповнення у випадку від'ємного числа
            if (result < (INT_MIN + digit) / 10) {
                throw OverflowException();
            }
        }
        else {
            // Перевірка на переповнення у випадку додатного числа
            if (result > (INT_MAX - digit) / 10) {
                throw OverflowException();
            }
        }

        result = result * 10 + digit;
    }

    // Зміна знаку, якщо число від'ємне
    if (negative) {
        result = -result;
    }

    return result;
}

int main() {
    try {
        std::string input;
        std::cout << "Enter a number: ";
        std::cin >> input;

        int number = parseInt(input);
        std::cout << "Parsed integer: " << number << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }

    return 0;
}
