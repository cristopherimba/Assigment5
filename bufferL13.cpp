#include <iostream>
#include <algorithm>
#include <chrono>

class Buffer {
private:
    int* data;
    size_t size;

public:
    Buffer(size_t s) : size(s), data(new int[s]) {
        std::cout << "Constructor called\n";
    }

    ~Buffer() {
        delete[] data;
        std::cout << "Destroyer called\n";
    }

    Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
        std::copy(other.data, other.data + other.size, data);
        std::cout << "Copy constructor called\n";
    }

    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            std::copy(other.data, other.data + size, data);
            std::cout << "Copy assignment called\n";
        }
        return *this;
    }

    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "Movement constructor called\n";
    }

    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;

            other.data = nullptr;
            other.size = 0;
            std::cout << "Move assignment called\n";
        }
        return *this;
    }
};

int main() {
    Buffer b1(100);
    Buffer b2 = b1;            
    Buffer b3 = std::move(b1); 

    Buffer b4(50);
    b4 = b2;                   
    b4 = std::move(b2);       

    const size_t large_size = 10000000;

    auto start_copy = std::chrono::high_resolution_clock::now();
    Buffer buf1(large_size);
    Buffer buf2 = buf1;
    auto end_copy = std::chrono::high_resolution_clock::now();

    auto start_move = std::chrono::high_resolution_clock::now();
    Buffer buf3 = std::move(buf1); 
    auto end_move = std::chrono::high_resolution_clock::now();

    std::cout << "Duration Copy time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end_copy - start_copy).count()
              << " ms\n";

    std::cout << "Duration Movement time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end_move - start_move).count()
              << " ms\n";
    return 0;
}

/*
• What constructors and assignments are called and when? 
Buffer b1(100); -> Constructor
Buffer b2 = b1; -> Copy constructor
Buffer b3 = std::move(b1); -> Move constructor
Buffer b4(50); ->Constructor
b4 = b2; -> Copy assignment
b4 = std::move(b2);-> Move assignment
• What happens to the source object after a move? 
The source object, b1 or b2 after the move, is left in 
a valid but unspecified state. Its resources have been 
transferred to the new object.
• What would happen if you didn’t define the move constructor/assignment?
The compiler would generate default versions that make 
copies, which could be inefficient or even incorrect if 
the class manages dynamic resources.

• What did you learn about move semantics?
I learned that move semantics allow C++ to transfer ownership of 
resources (like dynamically allocated memory) instead of copying them. 
This is especially useful for improving performance when working with 
large objects, because it avoids expensive deep copies. Move constructors 
and move assignment operators enable efficient object transfers using 
std::move, which casts an object to an rvalue reference.
• In what kinds of projects do you think this would matter?
Move semantics are crucial in performance-sensitive projects such as:
Game development, large.scale data processing, high-performance libraries
basically any project where efficiency and resource control are important.
• What are some risks of using std::move incorrectly?
After moving, the object is in a valid but unspecified state. Accessing 
its contents can lead to bugs or undefined behavior. Also, if the object 
is const, it can't be moved (because move constructors require non-const 
rvalue references), so it will fall back to copy, which may be unexpected.
*/



