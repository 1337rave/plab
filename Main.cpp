#include <iostream>
#include <string>

// ���� ������� ��� ������� ������������ ���� int
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

    // ������� ��������� ����� ���� ����� ������
    if (str[i] == '-') {
        negative = true;
        ++i;
    }

    // ���������� �������� ����� � ����� �������
    for (; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            throw std::invalid_argument("Invalid input: Non-numeric character encountered.");
        }

        int digit = str[i] - '0';

        // �������� �� ������������
        if (negative) {
            // �������� �� ������������ � ������� ��'������ �����
            if (result < (INT_MIN + digit) / 10) {
                throw OverflowException();
            }
        }
        else {
            // �������� �� ������������ � ������� ��������� �����
            if (result > (INT_MAX - digit) / 10) {
                throw OverflowException();
            }
        }

        result = result * 10 + digit;
    }

    // ���� �����, ���� ����� ��'����
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
