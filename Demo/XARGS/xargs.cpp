#include <iostream>
#include "XARGS/xargs.hpp"

#include <iomanip>

int main(int argc, char* argv[]) {

    xargs(argc, argv);
    //g++ -o xargs_exec Demo/XARGS/xargs.cpp -IUtils
    //echo "/" | ./xargs_exec ls -l
    return 0;
}
