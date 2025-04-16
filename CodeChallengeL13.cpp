#include <iostream>
#include <vector>

int main() {
    std::vector<int> v1 = {1, 2, 3, 4};
    std::vector<int> v2 = v1;        // Copy
    std::vector<int> v3 = std::move(v1); // Move

    std::cout << "v1 size: " << v1.size() << std::endl;
    std::cout << "v2 size: " << v2.size() << std::endl;
    std::cout << "v3 size: " << v3.size() << std::endl;

    return 0;
}

/*  What is the output of this program?
v1 size 0
v2 size 4
v3 size 4

• Why does v1.size() return 0 after the move?
Since std::move is used to initialize v3 and the contents of v1 are moved to v3 then
the memory is transfering to v3 in consequence after the moving v1 is empty, therefore
v1's size is zero. 
• What does std::move do?
std::move converts its argument to an rvalue, causing resources to be moved 
rather than copied; it does not perform the move itself, it just enables the ability to move. 
• Why is v1 still in a valid but unspecified state?
c++ give guarantees that then of the movement of an object, this maintains in a valid state,
 it can be destroyed without errors, but its specific content isn't defined.
*/