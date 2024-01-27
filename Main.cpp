#include <iostream>
#include <stdexcept>

template <typename T>
class Stack {
private:
    T* data;
    int capacity;
    int top;

public:
    Stack(int initialCapacity = 10) : capacity(initialCapacity), top(-1) {
        data = new T[capacity];
    }

    ~Stack() {
        delete[] data;
    }

    void push(const T& value) {
        if (top == capacity - 1) {
            throw std::overflow_error("Stack overflow: Unable to push element onto full stack.");
        }
        data[++top] = value;
    }

    void pop() {
        if (top == -1) {
            throw std::underflow_error("Stack underflow: Unable to pop element from empty stack.");
        }
        --top;
    }

    T& peek() {
        if (top == -1) {
            throw std::underflow_error("Stack underflow: Unable to peek at element from empty stack.");
        }
        return data[top];
    }
};

int main() {
    try {
        Stack<int> stack(5);
        stack.push(1);
        stack.push(2);
        stack.push(3);
        stack.push(4);
        stack.push(5);

        std::cout << "Top element: " << stack.peek() << std::endl;

        stack.pop();
        stack.pop();
        stack.pop();
        stack.pop();
        stack.pop(); // Генерує виняток underflow_error
    }
    catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }

    return 0;
}