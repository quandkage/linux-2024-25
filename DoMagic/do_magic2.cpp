#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

#define Blue "\x1B[32m"
#define RESET  "\x1B[0m"

int main() {
    int fd1 = open("Tests/exclusive_file.log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd1 == -1) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    const char* lines[] = {
        "What is LOVE?\n",
        "Oh, baby, don't hurt me\n",
        "Don't hurt me, no more\n"
    };

    for (const char* line : lines) {
        if (write(fd1, line, strlen(line)) == -1) {
            std::cerr << "Error writing to file" << std::endl;
            close(fd1);
            return 1;
        }
    }

    std::cout << Blue << "Writen successfully !" << RESET << std::endl;

    close(fd1);

    return 0;
}
