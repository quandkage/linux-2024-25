#include <fcntl.h>
#include <iostream>
#include <ostream>
#include <unistd.h>

void do_magic() {

    int f = open("Tests/new_pts.txt", O_RDONLY);
    if (f == -1) {
        std::cerr << "Error opening file" << std::endl;
    }

    if(dup2(f,STDIN_FILENO) == -1) {
        std::cerr << "Duplicating failed" << std::endl;
        close(f);
    }

    close(f);
}