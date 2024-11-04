#include <iostream>
#include <string>

#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"

void do_magic();

int main()
{
    do_magic();
    std::string s;
    std::cin >> s;
    std::cout << BLUE << s << RESET;
}
